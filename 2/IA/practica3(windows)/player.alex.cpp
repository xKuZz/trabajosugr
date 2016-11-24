#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

int SiguienteJugador(int jugador){
    if(jugador==1)
        return 2;
    return 1;
}

bool EsCasillaVerde(const Environment &estado,int fila,int columna){
    if(estado.See_Casilla(fila,columna)==1 || estado.See_Casilla(fila,columna)==4)
        return true;
    return false;
}

bool EsCasillaAzul(const Environment &estado,int fila,int columna){
    if(estado.See_Casilla(fila,columna)==2 || estado.See_Casilla(fila,columna)==5)
        return true;
    return false;
}

double CasillasContiguas(const Environment &estado,int fila, int columna){ // Cuenta las casillas de alrededor que son del mismo tipo
    double cuenta=0;
    int i_comienzo,i_final,j_comienzo,j_final;

    if(fila==0){
        i_comienzo=fila;
        i_final=fila+1;
    }
    else if(fila==6){
        i_comienzo=fila-1;
        i_final=fila;
    }
    else{
        i_comienzo=fila-1;
        i_final=fila+1;
    }

    if(columna==0){
        j_comienzo=columna;
        j_final=columna+1;
    }
    else if(columna==6){
        j_comienzo=columna-1;
        j_final=columna;
    }
    else{
        j_comienzo=columna-1;
        j_final=columna+1;
    }

        if(EsCasillaVerde(estado,fila,columna))
            for(int i=i_comienzo;i<=i_final;i++)
                for(int j=j_comienzo;j<=j_final;j++)
                    if(i!=fila || j!=columna) // Contamos las casillas de alrededor, no la propia casilla
                        if(EsCasillaVerde(estado,i,j))
                            cuenta+=0.5;

        if(EsCasillaAzul(estado,fila,columna))
            for(int i=i_comienzo;i<=i_final;i++)
                for(int j=j_comienzo;j<=j_final;j++)
                    if(i!=fila || j!=columna) // Contamos las casillas de alrededor, no la propia casilla
                        if(EsCasillaAzul(estado,i,j))
                            cuenta+=0.5;

    return cuenta;
}

double CalcularValorBomba(const Environment &estado,int fila,int columna){
    double valor=0;
    if(estado.See_Casilla(fila,columna)==4){ // Si es una bomba verde
        for(int i=0;i<6;i++){
            if(EsCasillaVerde(estado,fila,i)){
                valor+=1;
            }
        }
    }
    if(estado.See_Casilla(fila,columna)==5){  // Si es una bomba azul
        for(int i=0;i<6;i++){
            if(EsCasillaAzul(estado,fila,i)){
                valor+=1;
            }
        }
    }
    return valor;
}


// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
    if(estado.JuegoTerminado()){    // Si el tablero es una condicion de victoria, derrota o empate.
        int resultado=estado.RevisarTablero();
        if(resultado==jugador){
            return masinf;
        }
        else if(resultado==0){
            return 0;
        }
        else{
            return menosinf;
        }
    }
    else{  // En caso de que el tablero no este en una condición terminal, analizamos el mismo y le atribuimos una puntuación.
        double valor_heuristica=0;

        if(jugador=1){ // Si es el jugador 1 las casillas verdes juntas le perjudican y las azules juntas le benefician.
            for(int i=0;i<7;i++){
                for(int j=0;j<7;j++){
                   if(EsCasillaVerde(estado,i,j)){
                       valor_heuristica-=CasillasContiguas(estado,i,j);
                       //valor_heuristica+=CalcularValorBomba(estado,i,j);
                   }
                   if(EsCasillaAzul(estado,i,j)){
                       valor_heuristica+=CasillasContiguas(estado,i,j);
                      // valor_heuristica-=CalcularValorBomba(estado,i,j);
                   }
                }
            }
        }

        else{ // Si es el jugador 2, las casillas verdes juntas le benefician y las azules juntas le perjudican.
            for(int i=0;i<7;i++){
                for(int j=0;j<7;j++){
                    if(EsCasillaVerde(estado,i,j)){
                        valor_heuristica+=CasillasContiguas(estado,i,j);
                  //      valor_heuristica-=CalcularValorBomba(estado,i,j);
                    }
                    if(EsCasillaAzul(estado,i,j)){
                        valor_heuristica-=CasillasContiguas(estado,i,j);
                    //    valor_heuristica+=CalcularValorBomba(estado,i,j);
                    }
                }
            }
       }
       return valor_heuristica;
    }



}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}


double PodaAlfaBeta(const Environment &env,int player,const int profundidadMaxima,int profundidadActual,Environment::ActionType &accion,double alpha,double beta){
    // Si hemos llegado a un nodo terminal o hemos llegado a la profundidad maxima devolvemos el estado del juego.
    if(profundidadActual==profundidadMaxima || env.JuegoTerminado()){
        return Valoracion(env,player);
    }
    Environment hijos[8];
    int num_hijos;
    num_hijos=env.GenerateAllMoves(hijos);
    Environment env_mejor=hijos[0];
    double maximo=alpha;
    double minimo=beta;
    if(env.JugadorActivo()==player){ //MAX
        for(int i=0; i<num_hijos;i++){
            maximo=PodaAlfaBeta(hijos[i],player,profundidadMaxima,profundidadActual+1,accion,alpha,beta);
            if(maximo>alpha){
                alpha=maximo;
                env_mejor=hijos[i];
            }
            if(beta<=alpha)
                break;
        }
        accion=static_cast<Environment::ActionType>(env_mejor.Last_Action(player));
        return alpha;
    }

    else{ // MIN
        for(int i=0; i<num_hijos;i++){
            minimo=PodaAlfaBeta(hijos[i],player,profundidadMaxima,profundidadActual+1,accion,alpha,beta);
            if(minimo<beta){
                beta=minimo;
                env_mejor=hijos[i];
            }
            if(beta<=alpha)
                break;
        }
        accion=static_cast<Environment::ActionType>(env_mejor.Last_Action(player));
        return beta;
    }

}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci?n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha=menosinf, beta=masinf; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    /*//--------------------- COMENTAR Desde aqui
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }

    //--------------------- COMENTAR Hasta aqui */


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    valor=PodaAlfaBeta(actual_,jugador_,PROFUNDIDAD_ALFABETA,0,accion,alpha,beta);
    cout <<"Valor casillas pegadas: " << CasillasContiguas(actual_,2,0) << endl;
    cout <<"valor de la heuristica: " << valor << endl;
    cout <<"Accion Realizada: " << accion << endl;
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}

