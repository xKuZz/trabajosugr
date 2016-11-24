
#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include <tuple>
#include <map>
#include <set>
#include <vector>
#include "conexion.h"
using namespace std;

using PK = tuple<int, int, int, int>;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		x_= 99;
		y_= 99;
		orientacion_= 0;
		iteracion = 0;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		estado=ESTADO::ORIENTARSE;
		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
		      movimientos[i][j]=0;
		    }

		for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++)
              if (i<3 || j <3 || i>96 || j>96)
		      mapa_solucion_[i][j]='P';
              else
              mapa_solucion_[i][j]='?';

        // Gustos
        gustos[oro] = "ghklijopmn";
        gustos[oscar] = "ijmnghklop";
        gustos[manzana] = "mnklopijgh";
        gustos[algoritmo] = "opmnklijgh";
	}


	enum ActionType
	{
	    actFORWARD = 0, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};


	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};

    enum class GIRO {NO, IZQUIERDA, DERECHA, REVES, UNKNOWN};
    enum class ESTADO {ORIENTARSE, EXPLORAR, MISIONES};
private:
    // Métodos de orientación
    bool pkSinObstaculos(int orientacion); // Movimiento para favorecer PK
    bool pkUtil(int x, int y); // Determina si se ha usado el PK
    void getCoordenadasPK(string mensaje); // Determina la posición falsa y real de un punto de referencia
    void comprobarPrecipicios(); // Actualiza la ubicación de precipicios
    GIRO getGiro(PK mi_pk1, PK mi_pk2); // Determina el giro entre 2 PK
    GIRO getGiroPrecipicio(PK mi_pk); // Determinar el giro entre 1 PK y precipicios
    void orientarse(GIRO giro, PK mi_pk); // Realiza el proceso de rotación/traslación de datos

    string obstaculos();

    // Métodos de Exploración
    ActionType determinarMovimiento();
    bool puedoExplorarSinObstaculos(int orientacion);
    ActionType escogerMovimiento(int yi, int xi, int yd, int xd, int ya, int xa);
    int validez(int yi, int xi, int yd, int xd, int ya, int xa);
    bool objetoUtilSinObstaculos(int orientacion, char& objeto);
    bool objetoAlineado(ActionType& accion, char objeto);
    bool espacioObjetosExplorar();
    ActionType protocoloExploracion();

    // Métodos de Misiones
    ActionType busquedaPersonaje(char objeto);
    ActionType busquedaObjetoEntregable();
    bool personajeAlineado(ActionType& accion, char objeto);
    bool personajeSinObstaculos(int orientacion, char& objeto);

    // Inventario
    int espacioLibre();
    bool tengoObjeto(char objeto);
    bool objetoEquipado(char objeto);
    ActionType sacarObjeto(char objeto);
    ActionType cogerObjeto(char objeto);
    bool cogerObjetosExploracion(ActionType& accion);
    void objetoEvitaColision(ActionType& accion);

    // AutoFill
    bool recintoCerrado(int y, int x);
    // ComprobacionSolución
    int porcentajeExplorado();

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Variables de conocimiento
	const char aldeano1 = 'e';
	const char aldeano2 = 'f';
	const char princesa1 = 'g';
	const char princesa2 = 'h';
	const char leonardo1 = 'i';
	const char leonardo2 = 'j';
	const char principe1 = 'k';
	const char principe2 = 'l';
	const char bruja1 = 'm';
	const char bruja2 = 'n';
	const char profe1 = 'o';
	const char profe2 = 'p';
	const char oso = 'q';
	const char bikini = '0';
	const char piedra = '1';
	const char llave = '2';
	const char rosa = '3';
	const char oro = '4';
	const char oscar = '5';
	const char zapatillas = '6';
	const char pala = '7';
	const char manzana = '8';
	const char algoritmo = '9';
	char objeto_entregar = '-';
    string pref_objetos = "4859";
	map<char, string> gustos;

	//Variables de estado
	ESTADO estado;
	int iteracion;
	int movimientos[200][200];
	int x_,y_, orientacion_;
	int precipicio[4] = {-1, -1, -1, -1};
	set<PK> mis_pk;
	int last_accion_;
	string role_;

};

string ActionStr(Agent::ActionType);

#endif
