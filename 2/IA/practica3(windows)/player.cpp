#include <iostream>
#include <cstdlib>
#include <limits>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=numeric_limits<double>::max(),
         menosinf=numeric_limits<double>::lowest();


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
    int ganador = estado.RevisarTablero2();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
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


// ------------------- Los tres metodos anteriores no se pueden modificar

int casillasAdyacentes(const Environment& estado, int fila, int columna) {
    int salida = 0;
    int jugadorActual = estado.See_Casilla(fila, columna);
    int jugadorBomba  = jugadorActual + 3;

    if (fila > 0 && (estado.See_Casilla(fila-1, columna) == jugadorActual
                  ||  estado.See_Casilla(fila-1, columna) == jugadorBomba))
        ++salida;

    if (fila < 6 && (estado.See_Casilla(fila+1, columna) == jugadorActual
                 ||  estado.See_Casilla(fila+1, columna) == jugadorBomba))
        ++salida;

    if (columna > 0 && (estado.See_Casilla(fila, columna-1) == jugadorActual
                     ||  estado.See_Casilla(fila, columna-1) == jugadorBomba))
        ++salida;

    if (columna < 6 && (estado.See_Casilla(fila, columna+1) == jugadorActual
                    ||  estado.See_Casilla(fila, columna+1) == jugadorBomba))
        ++salida;

    if (fila > 0 && columna > 0 && (estado.See_Casilla(fila-1, columna-1) == jugadorActual
                                ||  estado.See_Casilla(fila-1, columna-1) == jugadorBomba))
        ++salida;

    if (fila < 6 && columna < 6 && (estado.See_Casilla(fila+1, columna+1) == jugadorActual
                                ||  estado.See_Casilla(fila+1, columna+1) == jugadorBomba))
        ++salida;

    if (fila > 0 && columna < 6 && (estado.See_Casilla(fila-1, columna+1) == jugadorActual
                                ||  estado.See_Casilla(fila-1, columna+1) == jugadorBomba))
        ++salida;

    if (fila < 6 && columna > 0 && (estado.See_Casilla(fila+1, columna-1) == jugadorActual
                                ||  estado.See_Casilla(fila+1, columna-1) == jugadorBomba))
        ++salida;



    return salida;
}

double valorarBombas(const Environment& estado, int jugador, int enemigo) {
  int bombaJugador = -1; // bomba indica la fila en la que está la bomba
  int bombaEnemigo = -1; // -1 indica que no está en ninguna fila
  double salida = 0.5; // Si no hay bombas o se equilibran se queda en '5
  for (int i = 0; i < 7; ++i)
    for (int j = 0; j < 7; ++j)
      if (estado.See_Casilla(i,j) == jugador + 3)
        bombaJugador = i;
      else if (estado.See_Casilla(i,j) == enemigo + 3)
        bombaEnemigo = i;

  if (bombaJugador != -1) {
    salida += 0.01;
    for (int j = 0; j < 7; ++j)
      if (estado.See_Casilla(bombaJugador,j) == jugador)
        salida += 0.01;
  }

  if (bombaEnemigo != -1) {
      salida -= 0.01;
      for (int j = 0; j < 7; ++j)
        if (estado.See_Casilla(bombaEnemigo,j) == enemigo)
          salida -= 0.01;
  }

  return salida;
}

double nivelAdyacencia(const Environment& estado, int jugador) {
    double salida = 0;

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            if (estado.See_Casilla(i,j) == jugador ||
                estado.See_Casilla(i,j) == jugador + 3)
                salida += casillasAdyacentes(estado,i,j);

    return salida;

}


// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero2();

    if (ganador == jugador)
        return masinf; // Si ganamos
    else if (ganador != 0)
        return menosinf; // Si perdemos
    else if (estado.Get_Casillas_Libres() == 0)
        return 0; // Si se produce empate

    // Calculamos los "niveles de adyacencia" nuestros y del rival
    // tomando como negativo el nuestro y como positivo el enemigo
    int jugadorEnemigo = (jugador%2) + 1;
    double val = nivelAdyacencia(estado, jugadorEnemigo);
    val -= nivelAdyacencia(estado,jugador);
    // Valoramos la situacion de las bombas
    val += valorarBombas(estado, jugador, jugadorEnemigo);
    return val;
}









/** PODA ALFABETA **/
double podaAlfaBeta(const Environment& nodoEstado, Environment::ActionType& accion, int jugadorMax,
                    double alpha, double beta, int profundidad, int kMAXPROFUNDIDAD) {
  // Si estamos en un nodo terminal o en profundidad máxima devolvemos el valor heurístico
  if (nodoEstado.JuegoTerminado() || profundidad == kMAXPROFUNDIDAD)
    return Valoracion(nodoEstado, jugadorMax);


  // Generamos los sucesores del nodo actual

  Environment sucesores[8];
  int nSucesores = nodoEstado.GenerateAllMoves(sucesores);

  Environment mejorEstado = sucesores[0];
  double valorHijo;
  // Si el jugador activo es jugadorMax estamos en un nodo MAX
  if (nodoEstado.JugadorActivo() == jugadorMax) {
      for (int i = 0; i < nSucesores; ++i) { // Para cada sucesor comprobamos si es mejor que el mejor actual
          valorHijo = podaAlfaBeta(sucesores[i], accion, jugadorMax, alpha, beta, profundidad+1, kMAXPROFUNDIDAD);
          if (valorHijo > alpha) {
            alpha = valorHijo;
            mejorEstado = sucesores[i];
          }

          if (beta <= alpha) break;
      }
      accion = static_cast<Environment::ActionType>(mejorEstado.Last_Action(jugadorMax));
      return alpha;
  }
  else { // Si no estamos en un nodo min
     for (int i = 0; i < nSucesores; ++i) { // Para cada sucesor comprobamos si es mejor que el mejor actual
          valorHijo = podaAlfaBeta(sucesores[i], accion, jugadorMax, alpha, beta, profundidad+1, kMAXPROFUNDIDAD);
          if (valorHijo < beta) {
            beta = valorHijo;
            mejorEstado = sucesores[i];
          }

          if (beta <= alpha) break;
      }
      accion = static_cast<Environment::ActionType>(mejorEstado.Last_Action(jugadorMax));
      return beta;
  }


}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor=0.00; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha=menosinf,
           beta=masinf; // Cotas de la poda AlfaBeta

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


    //--------------------- COMENTAR Desde aqui
//    cout << "\n\t";
//    int n_opciones=0;
//    JuegoAleatorio(aplicables, opciones, n_opciones);

//    if (n_act==0){
//      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
//      cout << " No puede realizar ninguna accion!!!\n";
//      //accion = Environment::actIDLE;
//    }
//    else if (n_act==1){
//           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
//            cout << " Solo se puede realizar la accion "
//                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
//            accion = static_cast< Environment::ActionType > (opciones[0]);

//         }
//         else { // Hay que elegir entre varias posibles acciones
//            int aleatorio = rand()%n_opciones;
//            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
//            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
//         }

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    //valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    valor = podaAlfaBeta(actual_, accion, jugador_, alpha, beta, 0, PROFUNDIDAD_ALFABETA);
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    cout << "Accion determinada: " << actual_.ActionStr(accion) << endl;
    return accion;
}

