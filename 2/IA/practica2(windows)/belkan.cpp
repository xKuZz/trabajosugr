#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iterator>
#include <utility>
#include <cstring>
#include <sstream>
#include <queue>



using namespace std;
#define Y_ROBOT 0
#define X_ROBOT 1
#define Y_MAPA  2
#define X_MAPA  3
using PK = tuple<int, int, int, int>;

// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}

// -----------------------------------------------------------
void PasarVectoraMapaSolucion(int fila, int columna, char m[100][100], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
		x_ = y_ = 99;
		orientacion_= 0;
		estado = ESTADO::ORIENTARSE;
		precipicio[0] = precipicio[1] = precipicio[2] = precipicio[3] = -1;
		for (int i=0; i<200;++i)
          for (int j =0; j<200; ++j)
            mapa_entorno_[i][j] = mapa_objetos_[i][j] = '?';
	}

	bool colision = MENSAJE_.find("Menudo golpe contra el arbol.") != string::npos or
                    MENSAJE_.find("Caiste al agua.")               != string::npos or
                    MENSAJE_.find("Intentando atravesar un muro")  != string::npos or
         MENSAJE_.find("Intentando atravesar una puerta cerrada")  != string::npos or
         MENSAJE_.find("Has chocado con un obstaculo movil.")      != string::npos;

	switch(last_accion_){
	  case 0: //avanzar
      if(!colision)
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // este
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}

    cout << "Terreno: ";
    for (int i=0; i<10; i++)
        cout << VISTA_[i];
    cout << endl;

    cout << "Objetos: ";
    for (int i=0; i<10; i++)
        cout << SURFACE_[i];
    cout << endl;

    cout << "Reiniciado: ";
    if (REINICIADO_)
        cout << "Si\n";
    else
        cout << "No\n";
    cout << "En Uso: " << EN_USO_ << endl;

    cout << "Mochila: " << MOCHILLA_ << endl;

    cout << "Puntuacion: " << PUNTUACION_ << endl;
    cout << "Mensaje: " << MENSAJE_ << endl <<endl;

    int N = (estado == ESTADO::ORIENTARSE) ? 200 : 100;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (mapa_entorno_[i][j] == '?')
                recintoCerrado(i,j);
	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);
	if (estado != ESTADO::ORIENTARSE)
      PasarVectoraMapaSolucion(y_,x_,mapa_solucion_,VISTA_,orientacion_);
    else if (find(begin(VISTA_), end(VISTA_), 'P') != end(VISTA_))
        comprobarPrecipicios();

    cout << "Posicion: Y: " << y_ << " X: " << x_ << endl;
	env->ActualizarMatrizUsuario(mapa_entorno_);

}

/** MÉTODOS RELACIONADOS CON LA ORIENTACIÓN DEL AGENTE **/

bool Agent::pkUtil(int x, int y) {
    if (mis_pk.empty())
        return true;
    else {
        for (auto pk : mis_pk)
            if (get<X_ROBOT>(pk) == x && get<Y_ROBOT>(pk) == y)
                return false;

        return true;
    }
}

void Agent::comprobarPrecipicios() {
    cout << "[CHECK-P] Comprobando precipicios" << endl;
    if (precipicio[0] == -1) { // Precipicio Norte
        for (int y = y_-1; y >= 0; --y) {
            int cuentaprecipicios = count(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), 'P');
            int cuentaotros = count_if(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), [] (char c) {
                                                                        return c != 'P' && c != '?';});
            if (cuentaprecipicios > 0 && cuentaotros == 0) {
                precipicio[0] = y;
                break;
            }

            else if (count(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), '?')==200)
                break;
        }
    }
    if (precipicio[2] == -1) { // Precipicio Sur
        for (int y = y_+1; y < 200; ++y) {
            int cuentaprecipicios = count(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), 'P');
            int cuentaotros = count_if(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), [] (char c) {
                                                                        return c != 'P' && c != '?';});
            if (cuentaprecipicios > 0 && cuentaotros == 0) {
                precipicio[2] = y;
                break;
            }

            else if (count(begin(mapa_entorno_[y]), end(mapa_entorno_[y]), '?')==200)
                break;
        }
    }
    if (precipicio[1] == -1) { // Precipicio Este
        for (int x = x_ + 1; x < 200; ++x) {
            int cuentaprecipicios = 0, cuentaotros = 0, cuentadesc = 0;
            for (int y = 0; y < 200; ++y)
                if (mapa_entorno_[y][x] == 'P')
                    ++cuentaprecipicios;
                else if (mapa_entorno_[y][x] == '?')
                    ++cuentadesc;
                else
                    ++cuentaotros;
            if (cuentaprecipicios > 0 && cuentaotros == 0) {
                precipicio[1] = x;
                break;
            }
            else if (cuentadesc==200)
                break;
        }
    }
    if (precipicio[3] == -1) { // Precipicio Oeste
        for (int x = x_ - 1; x >= 0; --x) {
            int cuentaprecipicios = 0, cuentaotros = 0, cuentadesc = 0;
            for (int y = 0; y < 200; ++y)
                if (mapa_entorno_[y][x] == 'P')
                    ++cuentaprecipicios;
                else if (mapa_entorno_[y][x] == '?')
                    ++cuentadesc;
                else
                    ++cuentaotros;
            if (cuentaprecipicios > 0 && cuentaotros == 0) {
                precipicio[3] = x;
                break;
            }
            else if (cuentadesc==200)
                break;
        }
    }
    cout << "Precipicio Norte:" << precipicio[0] << endl;
    cout << "Precipicio Este:"  << precipicio[1] << endl;
    cout << "Precipicio Sur:"   << precipicio[2] << endl;
    cout << "Precipicio Oeste:" << precipicio[3] << endl;

    for (PK pk : mis_pk)
        if (estado != ESTADO::ORIENTARSE)
            break;
        else {
            GIRO giro = getGiroPrecipicio(pk);
            if (giro != GIRO::UNKNOWN)
                orientarse(giro, pk);
        }

}
Agent::GIRO Agent::getGiroPrecipicio(PK mi_pk) {
    if (get<Y_MAPA>(mi_pk) != get<X_MAPA>(mi_pk) &&
        97 - get<Y_MAPA>(mi_pk) != get<X_MAPA>(mi_pk) - 2 &&
        97 - get<X_MAPA>(mi_pk) != get<Y_MAPA>(mi_pk) - 2) {
        if (precipicio[0] != -1) {
            int dist_robot = get<Y_ROBOT>(mi_pk) - precipicio[0];
            int dist_mapa  = get<Y_MAPA>(mi_pk) - 2;

            cout << "[PRECIPICIO-NORTE]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-NORTE]:DIST MAPA: " << dist_mapa << endl;
            if (dist_robot == dist_mapa) {
                cout << "[PRECIPICIO-NORTE]: Determinado NO GIRAR" << endl;
                return GIRO::NO;
            }
            else if (dist_robot == 97 - dist_mapa - 2) {
                cout << "[PRECIPICIO-NORTE]: Determinado AL REVES" << endl;
                return GIRO::REVES;
            }
            if (precipicio[1] != -1) {
                int dist_robote = precipicio[1] - get<X_ROBOT>(mi_pk);
                if (dist_robote == dist_mapa) {
                    cout << "[PRECIPICIO-NORTE/ESTE]: Determinado GIRO IZQUIERDA" << endl;
                    return GIRO::IZQUIERDA;
                }
                else if (dist_robote == 97 - dist_mapa - 2) {
                    cout << "[PRECIPICIO-NORTE/ESTE]: Determinado GIRO DERECHA" << endl;
                    return GIRO::DERECHA;
                }
            }
            if (precipicio[3] != -1) {
                int dist_roboto = get<X_ROBOT>(mi_pk) - precipicio[3];
                if (dist_roboto == dist_mapa) {
                    cout << "[PRECIPICIO-NORTE/OESTE]: Determinado GIRO DERECHA" << endl;
                    return GIRO::DERECHA;
                }
                else if (dist_roboto == 97 - dist_mapa - 2) {
                    cout << "[PRECIPICIO-NORTE/OESTE]: Determinado GIRO IZQUIERDA" << endl;
                    return GIRO::IZQUIERDA;
                }
            }
        }
        if (precipicio[2] != -1) {
            int dist_robot = precipicio[2] - get<Y_ROBOT>(mi_pk);
            int dist_mapa  = 97 - get<Y_MAPA>(mi_pk);

            cout << "[PRECIPICIO-SUR]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-SUR]:DIST MAPA: " << dist_mapa << endl;
            if (dist_robot == dist_mapa) {
                cout << "[PRECIPICIO-SUR]: Determinado NO GIRAR" << endl;
                return GIRO::NO;
            }
            else if (dist_robot == 97 - dist_mapa - 2) {
                cout << "[PRECIPICIO-SUR]: Determinado AL REVES" << endl;
                return GIRO::REVES;
            }
            if (precipicio[1] != -1) {
                int dist_robote = precipicio[1] - get<X_ROBOT>(mi_pk);
                if (dist_robote == dist_mapa) {
                    cout << "[PRECIPICIO-SUR/ESTE]: Determinado GIRO DERECHA" << endl;
                    return GIRO::DERECHA;
                }
                else if (dist_robote == 97 - dist_mapa - 2) {
                    cout << "[PRECIPICIO-SUR/ESTE]: Determinado GIRO IZQUIERDA" << endl;
                    return GIRO::IZQUIERDA;
                }
            }
            if (precipicio[3] != -1) {
                int dist_roboto = get<X_ROBOT>(mi_pk) - precipicio[3];
                if (dist_roboto == dist_mapa) {
                    cout << "[PRECIPICIO-SUR/OESTE]: Determinado GIRO IZQUIERDA" << endl;
                    return GIRO::IZQUIERDA;
                }
                else if (dist_roboto == 97 - dist_mapa - 2) {
                    cout << "[PRECIPICIO-SUR/OESTE]: Determinado GIRO DERECHA" << endl;
                    return GIRO::DERECHA;
                }
            }
        }
        if (precipicio[1] != -1) {
            int dist_robot = precipicio[1] - get<X_ROBOT>(mi_pk);
            int dist_mapa  = 97 - get<X_MAPA>(mi_pk);

            cout << "[PRECIPICIO-ESTE]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-ESTE]:DIST MAPA: " << dist_mapa << endl;
            if (dist_robot == dist_mapa) {
                cout << "[PRECIPICIO-ESTE]: Determinado NO GIRAR" << endl;
                return GIRO::NO;
            }
            else if (dist_robot == 97 - dist_mapa - 2) {
                cout << "[PRECIPICIO-ESTE]: Determinado AL REVES" << endl;
                return GIRO::REVES;
            }
        }
        if (precipicio[3] != -1) {
            int dist_robot = get<X_ROBOT>(mi_pk) - precipicio[3];
            int dist_mapa  = get<X_MAPA>(mi_pk) - 2;

            cout << "[PRECIPICIO-OESTE]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-OESTE]:DIST MAPA: " << dist_mapa << endl;
            if (dist_robot == dist_mapa) {
                cout << "[PRECIPICIO-OESTE]: Determinado NO GIRAR" << endl;
                return GIRO::NO;
            }
            else if (dist_robot == 97 - dist_mapa - 2) {
                cout << "[PRECIPICIO-OESTE]: Determinado AL REVES" << endl;
                return GIRO::REVES;
            }
        }
    }
    else if (get<X_MAPA>(mi_pk) == get<Y_MAPA>(mi_pk)){ // Si fila == columna
        if (precipicio[0] != -1) {
            int dist_robot = get<Y_ROBOT>(mi_pk) - precipicio[0];
            int dist_mapa  = get<Y_MAPA>(mi_pk) - 2;
            cout << "[PRECIPICIO-NORTE]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-NORTE]:DIST MAPA: " << dist_mapa << endl;
            if (precipicio[1] != -1) {
                int dist_robote = precipicio[1] - get<X_ROBOT>(mi_pk);
                if (dist_robot == dist_mapa)
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-NORTE/ESTE]: Determinado GIRO IZQUIERDA" << endl;
                        return GIRO::IZQUIERDA;
                    }
                    else {
                        cout << "[PRECIPICIO-NORTE/ESTE]: Determinado NO GIRO" << endl;
                        return GIRO::NO;
                    }
                else
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-NORTE/ESTE]: Determinado GIRO DERECHA" << endl;
                        return GIRO::DERECHA;
                    }
                    else {
                        cout << "[PRECIPICIO-NORTE/ESTE]: Determinado AL REVES" << endl;
                        return GIRO::REVES;
                    }
            }
            else if (precipicio[3] != -1) {
                int dist_robote = get<X_ROBOT>(mi_pk) - precipicio[3];
                if (dist_robot == dist_mapa)
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-NORTE/OESTE]: Determinado NO GIRO" << endl;
                        return GIRO::NO;
                    }
                    else {
                        cout << "[PRECIPICIO-NORTE/OESTE]: Determinado GIRO IZQUIERDA" << endl;
                        return GIRO::IZQUIERDA;
                    }
                else
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-NORTE/OESTE]: Determinado AL REVES" << endl;
                        return GIRO::REVES;
                    }
                    else {
                        cout << "[PRECIPICIO-NORTE/OESTE]: Determinado GIRO DERECHA" << endl;
                        return GIRO::DERECHA;
                    }
            }
        }
        if(precipicio[2] != -1) {
            int dist_robot = precipicio[2] - get<Y_ROBOT>(mi_pk);
            int dist_mapa  = 97 - get<Y_MAPA>(mi_pk);
            cout << "[PRECIPICIO-SUR]:DIST ROBOT: " << dist_robot << endl;
            cout << "[PRECIPICIO-SUR]:DIST MAPA: " << dist_mapa << endl;
            if (precipicio[1] != -1) {
                int dist_robote = precipicio[1] - get<X_ROBOT>(mi_pk);
                if (dist_robot == dist_mapa)
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-SUR/ESTE]: Determinado NO GIRO" << endl;
                        return GIRO::NO;
                    }
                    else {
                        cout << "[PRECIPICIO-SUR/ESTE]: Determinado GIRO IZQUIERDA" << endl;
                        return GIRO::IZQUIERDA;
                    }
                else
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-SUR/ESTE]: Determinado AL REVES" << endl;
                        return GIRO::REVES;
                    }
                    else {
                        cout << "[PRECIPICIO-SUR/ESTE]: Determinado GIRO DERECHA" << endl;
                        return GIRO::DERECHA;
                    }
            }
            if (precipicio[3] != -1) {
                int dist_robote = get<X_ROBOT>(mi_pk) - precipicio[3];
                if (dist_robot == dist_mapa)
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-SUR/OESTE]: Determinado GIRO IZQUIERDA" << endl;
                        return GIRO::IZQUIERDA;
                    }
                    else {
                        cout << "[PRECIPICIO-SUR/OESTE]: Determinado NO GIRO" << endl;
                        return GIRO::NO;
                    }
                else
                    if (dist_robot == dist_robote) {
                        cout << "[PRECIPICIO-SUR/OESTE]: Determinado GIRO DERECHA" << endl;
                        return GIRO::DERECHA;
                    }
                    else {
                        cout << "[PRECIPICIO-SUR/OESTE]: Determinado AL REVES" << endl;
                        return GIRO::REVES;
                    }
            }
        }
    }
    return GIRO::UNKNOWN;
}
// Determina el giro en función de dos puntos de referencia válidos
Agent::GIRO Agent::getGiro(PK mi_pk1, PK mi_pk2) {
    int xf1 = get<X_ROBOT>(mi_pk1), xf2 = get<X_ROBOT>(mi_pk2),
        yf1 = get<Y_ROBOT>(mi_pk1), yf2 = get<Y_ROBOT>(mi_pk2),
        xr1 = get<X_MAPA> (mi_pk1), xr2 = get<X_MAPA> (mi_pk2),
        yr1 = get<Y_MAPA> (mi_pk1), yr2 = get<Y_MAPA> (mi_pk2);

      cout << "PUNTO 1:" << endl;
      cout << "ROBOT X:\t" << xf1 << "\tY:\t" << yf1 << endl;
      cout << "MAPA  X:\t"  << xr1 << "\tY:\t" << yr1 << endl;
      cout << "PUNTO 2:" << endl;
      cout << "ROBOT X:\t" << xf2 << "\tY:\t" << yf2 << endl;
      cout << "MAPA  X:\t"  << xr2 << "\tY:\t" << yr2 << endl;
    if(yf2 - yf1 == yr2 - yr1 && xf2 - xf1 == xr2 - xr1) {
        cout << "[GIRO-PK]: Determinado no girar" << endl;
        return Agent::GIRO::NO;
    }
    else if (yf1 - yf2 == xr2 - xr1 && yr2 - yr1 == xf2 - xf1) {
        cout << "[GIRO-PK]: Determinado girar a la derecha" << endl;
        return Agent::GIRO::DERECHA;
    }
    else if (yr2 - yr1 == xf1 - xf2 && yf2 - yf1 == xr2 - xr1) {
        cout << "[GIRO-PK]: Determinado girar a la izquierda" << endl;
        return Agent::GIRO::IZQUIERDA;
    }
    else if (yr2 - yr1 == yf1 - yf2 && xr2 - xr1 == xf1 - xf2) {
        cout << "[GIRO-PK]: Determinado girar doble (mundo al reves)" << endl;
        return Agent::GIRO::REVES;
    }
    else {
        cout << "[GIRO-PK]: No ha sido posible determinar giro\
                  Se determinó no girar como medida preventiva" << endl;
        return Agent::GIRO::NO;
    }


}
// Añade al conjunto las coordenadas del PK sobre el que nos encontramos (si procede).
void Agent::getCoordenadasPK(string mensaje) {
      cout << "[PK] - Tratando PK actual" << endl;
      int yr, xr, yf, xf;
      unsigned tam_prev = mis_pk.size();
      istringstream splitter(mensaje);
      string numero;
      splitter >> numero;
      splitter >> numero;
      splitter >> numero;
      yr = atoi (numero.c_str());
      splitter >> numero;
      splitter >> numero;
      xr = atoi(numero.c_str());
      xf = x_;
      yf = y_;
      cout << "[PK] Referencias previas disponibles:" << mis_pk.size() << endl;
      PK pk(yf,xf,yr,xr);
      mis_pk.insert(pk);
      cout << "[PK] Referencias actuales disponibles:" << mis_pk.size() << endl;
      // Comprobamos si tenemos un par de datos válidos para orientarse
      if (mis_pk.size() > tam_prev && mis_pk.size() > 1) {
        cout << "[PK] Dos referencias han sido seleccionadas para orientarse" << endl;
        for (auto it1 : mis_pk)
                if (get<X_MAPA>(it1) != get<X_MAPA>(pk) &&
                    get<Y_MAPA>(it1) != get<Y_MAPA>(pk)) {
                        GIRO giro = getGiro(it1, pk);
                        orientarse(giro, pk);
                        return;
                }
      }
      if (mis_pk.size() > tam_prev)
        comprobarPrecipicios();
}


void Agent::orientarse(GIRO giro, PK mi_pk) {
    int  xf2 = get<X_ROBOT>(mi_pk),
         yf2 = get<Y_ROBOT>(mi_pk),
         xr2 = get<X_MAPA> (mi_pk),
         yr2 = get<Y_MAPA> (mi_pk);
      char aux[200][200];
      char aux2[200][200];
      int aux3[200][200];
      int y = y_, x = x_;
      cout << "[ORIENTARSE] - Inicando proceso de rotacion/traslacion de datos de la vida actual" << endl;
      cout << "[] - Almacenando datos del entorno actual para el cambio" << endl;
      for (int i=0; i < 200; ++i)
        for (int j=0; j < 200; ++j) {
          aux[i][j] = mapa_entorno_[i][j];
          aux2[i][j] = mapa_objetos_[i][j];
          aux3[i][j] = movimientos[i][j];
        }

      cout << "[ADIOS] - Vaciando entorno actual" << endl;
        for (int i=0; i < 200; ++i)
          for (int j=0; j < 200; ++j)
            mapa_entorno_[i][j]='?';
      cout << "[ZOMBIE] - Recuperando datos de vidas pasadas" << endl;
        for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j)
                mapa_entorno_[i][j] = mapa_solucion_[i][j];


      cout << "[GIRO/TRASLACION] - INICIANDO..." << endl;
      switch (giro) {
        case GIRO::UNKNOWN:
            cout << "[GIRO]: GIRO NO DETERMINADO!! REALIZANDO NO GIRO" << endl;
        case GIRO::NO:
        for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j) {
              if (aux[i + yf2 - yr2][j + xf2 - xr2] != '?')
                mapa_entorno_[i][j] = mapa_solucion_[i][j] = aux[i + yf2 - yr2][j + xf2 - xr2];
              mapa_objetos_[i][j] = aux2[i + yf2 - yr2][j + xf2 - xr2];
              movimientos[i][j] = aux3[i + yf2 - yr2][j + xf2 - xr2];
              if (i + yf2 - yr2== y && j + xf2 - xr2== x)
              {
                  cout << "ENCONTRADO EN " << i << " " << j << endl;
                  y_ = i; x_ = j;
              }
            }
        break;
        case GIRO::DERECHA:
          for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j) {
              if (aux[yf2 + xr2 - j][i + xf2 - yr2] != '?')
                mapa_entorno_[i][j] = mapa_solucion_[i][j] = aux[yf2 + xr2 - j][i + xf2 - yr2];
              mapa_objetos_[i][j] = aux2[yf2 + xr2 - j][i + xf2 - yr2];
              movimientos[i][j] = aux3[yf2 + xr2 - j][i + xf2 - yr2];
              if (yf2 + xr2 - j== y && i + xf2 - yr2== x)
              {
                  cout << "ENCONTRADO EN " << i << " " << j << endl;
                  y_ = i; x_ = j;
              }
            }
          orientacion_ = (orientacion_+1)%4;
        break;
        case GIRO::IZQUIERDA:
          for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j) {
              if (aux[j + yf2 - xr2][xf2 + yr2 - i] != '?')
                mapa_entorno_[i][j] = mapa_solucion_[i][j] = aux[j + yf2 - xr2][xf2 + yr2 - i];
              mapa_objetos_[i][j] = aux2[j + yf2 - xr2][xf2 + yr2 - i];
              if (j + yf2 - xr2== y && xf2 + yr2 - i== x)
              {
                  cout << "ENCONTRADO EN " << i << " " << j << endl;
                  y_ = i; x_ = j;
              }
              movimientos[i][j] = aux3[j + yf2 - xr2][xf2 + yr2 - i];
            }
          orientacion_ = (orientacion_+3)%4;
          break;
        case GIRO::REVES:
        for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j) {
              if (aux[yf2 + yr2 - i][xf2 + xr2 - j] != '?')
                mapa_entorno_[i][j] = mapa_solucion_[i][j] = aux[yf2 + yr2 - i][xf2 + xr2 - j];
              mapa_objetos_[i][j] = aux2[yf2 + yr2 - i][xf2 + xr2 - j];
              movimientos[i][j] = aux3[yf2 + yr2 - i][xf2 + xr2 - j];
                if (yf2 + yr2 - i== y && xf2 + xr2 - j== x)
              {
                  cout << "ENCONTRADO EN " << i << " " << j << endl;
                  y_ = i; x_ = j;
              }
            }
        orientacion_ = (orientacion_+2)%4;
        break;
      }
      cout << "[WHERE] AGENTE EN Y: " << y_  << " X: " << x_ << endl;
      cout << "[GIRO/TRASLACION] - FINALIZADO" << endl;
      cout << "[SMART-FILL] - Rellenando precipicios" << endl;
      for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++)
              if (i<3 || j <3 || i>96 || j>96)
		      mapa_entorno_[i][j]=mapa_solucion_[i][j]='P';

      cout << "[PK] - Eliminado informacion de puntos de referencia" << endl;
      mis_pk.clear();
      cout << "[ORIENTARSE] - PROCESO DE ORIENTACION FINALIZADO" << endl;
      estado = ESTADO::EXPLORAR;
}



Agent::ActionType Agent::escogerMovimiento(int yi, int xi, int yd, int xd, int ya, int xa) {

    int izquierda = movimientos[yi][xi];
    int derecha   = movimientos[yd][xd];
    int avanzar   = movimientos[ya][xa];
    int valido = validez(yi, xi, yd, xd, ya, xa);
    if (valido <3)
        if (valido == 0)
            return actFORWARD;
        else if (valido == 1)
            return actTURN_L;
        else
            return actTURN_R;
    else if (valido == 3)
        if (!puedoExplorarSinObstaculos((orientacion_+3)%4) && puedoExplorarSinObstaculos((orientacion_+1)%4))
            return actTURN_R;
        else if (!puedoExplorarSinObstaculos((orientacion_+1)%4) && puedoExplorarSinObstaculos((orientacion_+3)%4))
            return actTURN_L;
        else if (puedoExplorarSinObstaculos((orientacion_+2)%4))
                return actTURN_L;
        else if (izquierda <= derecha)
            return actTURN_L;
        else
            return actTURN_R;
    else if (valido == 4)
        if (!puedoExplorarSinObstaculos(orientacion_) && puedoExplorarSinObstaculos((orientacion_+3)%4))
            return actTURN_L;
        else if (puedoExplorarSinObstaculos((orientacion_+2)%4))
            return actTURN_L;
        else if (avanzar <= izquierda)
            return actFORWARD;
        else
            return actTURN_L;
    else if (valido == 5)
        if (!puedoExplorarSinObstaculos(orientacion_) && puedoExplorarSinObstaculos((orientacion_+1)%4))
            return actTURN_R;
        else if (puedoExplorarSinObstaculos((orientacion_+2)%4))
            return actTURN_R;
        else if (puedoExplorarSinObstaculos((orientacion_+2)%4))
                return actTURN_L;
        else if (avanzar <= derecha)
            return actFORWARD;
        else
            return actTURN_R;

    else {
            if (puedoExplorarSinObstaculos((orientacion_+1)%4))
                return actTURN_R;
            else if (puedoExplorarSinObstaculos((orientacion_+3)%4))
                return actTURN_L;
            else if (puedoExplorarSinObstaculos((orientacion_+2)%4))
                return actTURN_L;
            else if (avanzar <= min(izquierda,derecha))
                return actFORWARD;
            else if (izquierda<=derecha)
                return actTURN_L;
            else
                return actTURN_R;
    }



}

int Agent::validez(int yi, int xi, int yd, int xd, int ya, int xa) {
  bool izq=obstaculos().find(mapa_entorno_[yi][xi]) == string::npos &&
                    !islower(mapa_objetos_[yi][xi]);
  bool der=obstaculos().find(mapa_entorno_[yd][xd]) == string::npos &&
                    !islower(mapa_objetos_[yd][xd]);
  bool ava=obstaculos().find(mapa_entorno_[ya][xa]) == string::npos &&
                    !islower(mapa_objetos_[ya][xa]);

  /* Valores valido
       0 -> Sólo avanzar
       1 -> Solo izquierda
       2 -> Solo derecha
       3-> Ambos giros
       4 -> Izq + Avanze
       5 -> Dercha + avance
       6 -> Todas
    */

    if (!izq && !der && ava)
        return 0;
    else if (izq && !der && !ava)
        return 1;
    else if (!izq && der && !ava)
        return 2;
    else if (!ava)
        return 3;
    else if (!der)
        return 4;
    else if (!izq)
        return 5;
    else
        return 6;

}

bool Agent::puedoExplorarSinObstaculos(int orientacion) {
    int i;
        switch(orientacion){
        case 0: // norte
            for (i=y_; mapa_entorno_[i][x_] != '?'  && i>2 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                !islower(mapa_objetos_[i][x_]); --i);
            return mapa_entorno_[i][x_]=='?';
		    break;
	    case 1: // este
            for (i=x_; mapa_entorno_[y_][i] != '?'  && i<198 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                ! islower(mapa_objetos_[y_][i]); ++i);

            return mapa_entorno_[y_][i] == '?';
            break;
	    case 2: // sur
	        for (i=y_; mapa_entorno_[i][x_] != '?'  && i<198 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                ! islower(mapa_objetos_[i][x_]); ++i);

            return mapa_entorno_[i][x_]=='?';
		    break;
	    case 3: // oeste
	        for (i=x_; mapa_entorno_[y_][i] != '?'  && i>2 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                !islower(mapa_objetos_[y_][i]); --i);

            return mapa_entorno_[y_][i]=='?';
		    break;
	  }
	  return false;
}

bool Agent::pkSinObstaculos(int orientacion) {
    int i;
        switch(orientacion){
        case 0: // norte
            for (i=y_-1; mapa_entorno_[i][x_] != 'K' && mapa_entorno_[i][x_] != '?'   && i>2 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                !islower(mapa_objetos_[i][x_]); --i);
            return mapa_entorno_[i][x_]=='K' && pkUtil(x_,i);
		    break;
	    case 1: // este
            for (i=x_+1; mapa_entorno_[y_][i] != 'K'  && mapa_entorno_[y_][i] != '?' && i<198 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                ! islower(mapa_objetos_[y_][i]); ++i);

            return mapa_entorno_[y_][i] == 'K' && pkUtil(i,y_);
            break;
	    case 2: // sur
	        for (i=y_+1; mapa_entorno_[i][x_] != 'K'  && mapa_entorno_[i][x_] != '?' && i<198 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                ! islower(mapa_objetos_[i][x_]); ++i);

            return mapa_entorno_[i][x_]=='K' && pkUtil(x_,i);
		    break;
	    case 3: // oeste
	        for (i=x_-1; mapa_entorno_[y_][i] != 'K' && mapa_entorno_[y_][i] != '?' && i>2 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                !islower(mapa_objetos_[y_][i]); --i);

            return mapa_entorno_[y_][i]=='K' && pkUtil(i,y_);
		    break;
	  }
	  return false;
}
Agent::ActionType Agent::determinarMovimiento() {
    ActionType accion = actIDLE;

    if(!puedoExplorarSinObstaculos(orientacion_))
    switch(orientacion_){
        case 0: // norte
                accion = escogerMovimiento(y_,x_-1,y_,x_+1,y_-1,x_);
		    break;
	    case 1: // este
                accion = escogerMovimiento(y_-1,x_,y_+1,x_,y_,x_+1);
		    break;
	    case 2: // sur
                accion = escogerMovimiento(y_,x_+1,y_,x_-1,y_+1,x_);
		    break;
	    case 3: // oeste
                accion = escogerMovimiento(y_+1,x_,y_-1,x_,y_,x_-1);
		    break;
	  }
    else
        accion = actFORWARD;

    // Devolvemos la acción
    return accion;

}
bool Agent::objetoAlineado(ActionType& accion, char objeto) {
    char obj_izq='n', obj_fren='n', obj_der='n', obj_atras = 'n';
      objetoUtilSinObstaculos(orientacion_,obj_fren);
      objetoUtilSinObstaculos((orientacion_+3)%4,obj_izq);
      objetoUtilSinObstaculos((orientacion_+1)%4,obj_der);
      objetoUtilSinObstaculos((orientacion_+2)%4,obj_atras);

      if (obj_fren == objeto || obj_izq == objeto || obj_der == objeto || obj_atras == objeto) {
      if (estado == ESTADO::EXPLORAR || estado == ESTADO::ORIENTARSE) {
        if (!tengoObjeto(objeto) && (objeto == zapatillas || objeto == llave || objeto == bikini)) {
                if (obj_fren == objeto)
                    accion = actFORWARD;
                else if (obj_izq == objeto || obj_atras == objeto)
                    accion = actTURN_L;
                else if (obj_der == objeto)
                    accion = actTURN_R;
                return true;
            }
      }
        else if (espacioLibre()>0) {
            if (obj_fren == objeto)
                accion = actFORWARD;
            else if (obj_izq == objeto || obj_atras == objeto)
                accion = actTURN_L;
            else if (obj_der == objeto)
                accion = actTURN_R;
            return true;
        }
      }
      return false;

}

bool Agent::personajeAlineado(ActionType& accion, char objeto) {
    char obj_izq='-', obj_fren='-', obj_der='-', obj_atras = '-';
      personajeSinObstaculos(orientacion_,obj_fren);
      personajeSinObstaculos((orientacion_+3)%4,obj_izq);
      personajeSinObstaculos((orientacion_+1)%4,obj_der);
      personajeSinObstaculos((orientacion_+2)%4,obj_atras);

      if (obj_fren == objeto || obj_izq == objeto || obj_der == objeto || obj_atras == objeto) {
            if (obj_fren == objeto)
                accion = actFORWARD;
            else if (obj_izq == objeto || obj_atras == objeto)
                accion = actTURN_L;
            else if (obj_der == objeto)
                accion = actTURN_R;
            return true;
      }
      return false;
}

void Agent::objetoEvitaColision(ActionType& accion) {
    if (accion == actFORWARD && obstaculos().find(VISTA_[1]) == string::npos) {
        if (VISTA_[1] == 'D' && !objetoEquipado(llave))
          accion = sacarObjeto(llave);
        if (VISTA_[1] == 'A' && !objetoEquipado(bikini))
          accion = sacarObjeto(bikini);
        if (VISTA_[1] == 'B' && !objetoEquipado(zapatillas))
          accion = sacarObjeto(zapatillas);
      }
}
Agent::ActionType Agent::protocoloExploracion() {
    ActionType accion = actIDLE;
    if (estado == ESTADO::ORIENTARSE) {
        // Tratamiento de PK
        size_t pos = MENSAJE_.find("PK fila:");
        if (pos != string::npos)
            getCoordenadasPK(MENSAJE_.substr(pos));

        if (pkSinObstaculos(orientacion_))
            accion = actFORWARD;
        else if (pkSinObstaculos((orientacion_+3)%4) || pkSinObstaculos((orientacion_+2)%4))
            accion = actTURN_L;
        else if (pkSinObstaculos((orientacion_+1)%4))
            accion = actTURN_R;

        if (accion != actIDLE) {
            objetoEvitaColision(accion);
            return accion;
        }
    }
    // Preferimos coger objetos que faciliten la exploración
    if (cogerObjetosExploracion(accion))
        return accion;

    accion = determinarMovimiento();
    objetoEvitaColision(accion);
    return accion;

}
/** MËTODOS RELACIONADOS CON EL CONOCIMIENTO DEL ENTORNO **/
string Agent::obstaculos() {
  string obstaculos ="MP";
  if (string(MOCHILLA_).find('0') == string::npos && EN_USO_ != '0')
    obstaculos+="A";
  if (string(MOCHILLA_).find('6') == string::npos && EN_USO_ != '6')
    obstaculos+="B";
  if (string(MOCHILLA_).find('2') == string::npos && EN_USO_ != '2')
    obstaculos+="D";
  return obstaculos;
}

/** MËTODOS RELACIONADOS CON EL INVENTARIO **/
bool Agent::tengoObjeto(char objeto) {
  return string(MOCHILLA_).find(objeto) != string::npos || objetoEquipado(objeto);
}

bool Agent::objetoEquipado(char objeto) {
    return EN_USO_ == objeto;
}

Agent::ActionType Agent::cogerObjeto(char objeto) {
        if (objetoEquipado('-'))
            return actPICKUP;
        else
            return actPUSH;
}
Agent::ActionType Agent::sacarObjeto(char objeto) {
        if (objetoEquipado('-'))
            return actPOP;
        else
            return actPUSH;
}

int Agent::espacioLibre() {
    int total = count(begin(MOCHILLA_), end(MOCHILLA_), '-');
        if (estado == ESTADO::ORIENTARSE || estado == ESTADO::EXPLORAR) {
        if (!tengoObjeto(bikini))
            --total;
        if (!tengoObjeto(llave))
            --total;
        if (!tengoObjeto(zapatillas))
            --total;
        }
    return total;
}

bool Agent::cogerObjetosExploracion(ActionType& accion) {
    if ((SURFACE_[0] == bikini || SURFACE_[0] == zapatillas || SURFACE_[0] == llave)
        && !tengoObjeto(SURFACE_[0])) {
            accion = cogerObjeto(SURFACE_[0]);
            return true;
        }
    else if(objetoAlineado(accion, zapatillas))
        return true;
    else if(objetoAlineado(accion, bikini))
        return true;
    else if(objetoAlineado(accion, llave))
        return true;
    return false;
}

/** REALIZACIÓN DE MISIONES **/

Agent::ActionType Agent::busquedaPersonaje(char objeto) {
    ActionType accion;
    for (char personaje : gustos[objeto])
        if (personajeAlineado(accion, personaje))
            return accion;
    return determinarMovimiento();
}

Agent::ActionType Agent::busquedaObjetoEntregable() {
    ActionType accion = actIDLE;
    if (pref_objetos.find(SURFACE_[0]) != string::npos)
        return cogerObjeto(SURFACE_[0]);
    for (char objeto : pref_objetos)
        if (objetoAlineado(accion, objeto)) {
            cout << "OBJETO ALINEADO!! " << objeto << endl;
            return accion;
        }
    return determinarMovimiento();

}
// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	Agent::ActionType accion = actIDLE;
	if (tengoObjeto(oro))
        objeto_entregar = oro;
    else if (tengoObjeto(manzana))
        objeto_entregar = manzana;
    else if (tengoObjeto(oscar))
        objeto_entregar = oscar;
    else if (tengoObjeto(algoritmo))
        objeto_entregar = algoritmo;
    else
        objeto_entregar = '-';

    cout << "Iteracion: " << ++iteracion << endl
         << "Porcentaje explorado: " << porcentajeExplorado() << endl;

    if (estado != ESTADO::MISIONES && estado == ESTADO::EXPLORAR) {
        if (porcentajeExplorado() == 100 || (porcentajeExplorado() >=98 && iteracion > 7500)) {
            for (int i = 0; i < 200; ++i)
                fill(begin(movimientos[i]),end(movimientos[i]),0);
            estado = ESTADO::MISIONES;
        }

    }
    if (estado != ESTADO::MISIONES)
        accion = protocoloExploracion();
    else {
        if (SURFACE_[1] > 'd' && SURFACE_[1] < 'q' && objeto_entregar != '-')
            if (EN_USO_ == objeto_entregar){
                cout << "[MISION-DAR]" << endl;
                accion = actGIVE;
                for (int i = 0; i < 200; ++i)
                fill(begin(movimientos[i]),end(movimientos[i]),0);
                }
            else
                accion = sacarObjeto(objeto_entregar);
        else if (cogerObjetosExploracion(accion));
        else if (objeto_entregar != '-') {
                cout << "[BUSCA-PERSONAJE]" << endl;
            accion = busquedaPersonaje(objeto_entregar);
        }
        else {
            cout << "[BUSCA-OBJETO]" << endl;
            accion = busquedaObjetoEntregable();
        }
        objetoEvitaColision(accion);
    }

    // recuerdo la ultima accion realizada
    movimientos[y_][x_] = iteracion;
	last_accion_ = accion;
	cout << "Accion determinada: " << ActionStr(accion) << endl;
	return accion;

}

/** Métodos relacionados con los objetos e interacción con objetos **/


int Agent::porcentajeExplorado() {
    int total = 0;
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j)
            if (mapa_solucion_[i][j] != '?')
                total++;
    return total / 100;
}

bool Agent::objetoUtilSinObstaculos(int orientacion, char& objeto) {
    int i;
        switch(orientacion){
        case 0: // norte
            for (i=y_; !isdigit(mapa_objetos_[i][x_])  && i>2 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                !islower(mapa_objetos_[i][x_]); --i);
            return isdigit(objeto=mapa_objetos_[i][x_]);
		    break;
	    case 1: // este
            for (i=x_; !isdigit(mapa_objetos_[y_][i])  && i<198 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                ! islower(mapa_objetos_[y_][i]); ++i);

            return isdigit(objeto=mapa_objetos_[y_][i]);
            break;
	    case 2: // sur
	        for (i=y_; !isdigit(mapa_objetos_[i][x_])  && i<198 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                ! islower(mapa_objetos_[i][x_]); ++i);

            return isdigit(objeto=mapa_objetos_[i][x_]);
		    break;
	    case 3: // oeste
	        for (i=x_; !isdigit(mapa_objetos_[y_][i])  && i>2 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                !islower(mapa_objetos_[y_][i]); --i);

            return isdigit(objeto=mapa_objetos_[y_][i]);
		    break;
}
return false;
}

bool Agent::personajeSinObstaculos(int orientacion, char& objeto) {
    int i;
        switch(orientacion){
        case 0: // norte
            for (i=y_; !isdigit(mapa_objetos_[i][x_])  && i>2 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                !islower(mapa_objetos_[i][x_]); --i);
            return islower(objeto=mapa_objetos_[i][x_]);
		    break;
	    case 1: // este
            for (i=x_; !isdigit(mapa_objetos_[y_][i])  && i<198 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                ! islower(mapa_objetos_[y_][i]); ++i);

            return islower(objeto=mapa_objetos_[y_][i]);
            break;
	    case 2: // sur
	        for (i=y_; !isdigit(mapa_objetos_[i][x_])  && i<198 &&
                 obstaculos().find(mapa_entorno_[i][x_]) == string::npos &&
                ! islower(mapa_objetos_[i][x_]); ++i);

            return islower(objeto=mapa_objetos_[i][x_]);
		    break;
	    case 3: // oeste
	        for (i=x_; !isdigit(mapa_objetos_[y_][i])  && i>2 &&
                 obstaculos().find(mapa_entorno_[y_][i]) == string::npos &&
                !islower(mapa_objetos_[y_][i]); --i);

            return islower(objeto=mapa_objetos_[y_][i]);
		    break;
}
return false;
}


bool Agent::recintoCerrado(int y, int x) {
    // Devuelve si una determinada casilla desconocida es de un muro
    int i,j=x, ysi,xsi,ysd,xsd,yid,xid,yii,xii;
    if (mapa_entorno_[y][x]!='?')
        return false;

    // Buscamos esquina izquierda.
    for (i = y; mapa_entorno_[i][j]!= 'M' && mapa_entorno_[i][j] != 'D'
        && i>2; i--);
    if (mapa_entorno_[i][j] == 'D' || mapa_entorno_[i][j] == 'M')
        ysi = i;
    else
        return false;
    for (j = x; mapa_entorno_[i][j]== 'M' || mapa_entorno_[i][j] == 'D'; j--);
    if (mapa_entorno_[i][++j] == 'D' || mapa_entorno_[i][j] == 'M') {
        xsi = j;
        }
    else
        return false;
    for (; mapa_entorno_[i][j]=='M' || mapa_entorno_[i][j] == 'D';++j);
    ysd = i;
    xsd = --j;
    for (; mapa_entorno_[i][j]=='M' || mapa_entorno_[i][j] == 'D';++i);
    yid = --i;
    xid = j;
    for (; mapa_entorno_[i][j]=='M' || mapa_entorno_[i][j] == 'D';--j);
    yii = i;
    xii = ++j;
    for (; mapa_entorno_[i][j]=='M' || mapa_entorno_[i][j] == 'D';--i);

    if (ysi == ++i && xsi ==j && (y > ysi && y < yii && x > xii && x < xid)) {
        cout << "[SMART-FILL] HAY MURO ALRDEDOR DE fila " << y << " columna " << x << endl;
        cout << "[SMART-FILL] RELLENANDO MURO" << endl;
        for (int a = ysi+1; a < yid; ++a)
            for (int b = xsi+1; b < xid; ++b)
                if (mapa_entorno_[a][b]=='?') {
                    mapa_entorno_[a][b]='S';
                    if (estado != ESTADO::ORIENTARSE)
                        mapa_solucion_[a][b]='S';
                }
        return true;
    }
    return false;

}
