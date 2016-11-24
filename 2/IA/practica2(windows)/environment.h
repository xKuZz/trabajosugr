
#ifndef ENVIRONMENT__
#define ENVIRONMENT__

#include <fstream>
#include <string>
#include <map>
#include <cstring>

#include "conexion.h"
using namespace std;

struct registro{
  char nick[1024];
  int cliente;
  int pid;
  char ip[12];
  time_t fecha;
  bool activo;
  int fila;
  int columna;
  int brujula;
  char en_uso;
  char mochila[5];
  char role[5];
  int puntuacion;
  int puntuacion_mapa;
  int last_action;
  char salud;
  int veces_reiniciado;
  int objetivos_cumplidos[5];
  bool golpeado;
};

// -----------------------------------------------------------
//				class Environment
// -----------------------------------------------------------

class Environment
{
public:
	static const int MAZE_SIZE = 100;

	Environment();
	Environment(ifstream &infile);
	void Show(int,int,char maze_entorno[200][200], char maze_objetos[200][200]) const;
	void ActualizarMatrizUsuario(char mapa[200][200]);	
	void AcceptAction(Agent::ActionType);

	void WhatIsInFrontOfMe(char *vision, char *movil, string &mensaje);
	bool Perceive_Remote(conexion_client &Cliente);

	void SenSorStatus(char *terreno, char *objetos, string &mensaje, bool &reiniciar, char &en_uso, char *mochila, 
					  char *puntuacion, bool &finjuego, char &salud, bool remote);

	bool Reiniciado() const {return reiniciado_;};

	void randomPos(int &x, int &y, int &ori);
	void randomPosPlayer();
	void PutCoord(int fila, int columna, int ori) {agentPosX_ = fila; agentPosY_ = columna; agentOriented_=ori;};
	void GetCoord(int &fila, int &columna, int &ori) {fila =agentPosX_; columna = agentPosY_; ori=agentOriented_;};
	void PutRole(char *papel){role_=papel;};
	void GetRole(char *papel){strcpy(papel,role_.c_str());};

    void ColocarObjetos(int num, char objeto);
	void RepartirObjetos(int banador, int piedra, int espada, int rosa, int oro, int oscar, int zapatillas, 
						 int palo, int manzana, int algoritmo);
	void RepartirPersonajes(int aldeano, int Princesa, int Princeso, int Leonardo, int bruja, int profe);
	void DesperdigarObjetosTrasReiniciado();
	int Puntuar(char objeto, char personaje, string &mensaje);


	bool JuegoTerminado(){return finJuego_;}
	void PutFinJuego(){finJuego_=true;};

	int Comparar(char m[100][100]) const;
private:

	int agentPosX_, agentPosY_, agentOriented_; // Orientacion: 0 Norte, 1 Este, 2 Sur, 3 Oeste.
	char en_uso_; 
	char mochila_[5]; 
	int puntuacion_;
	int vida; 
	bool reiniciado_;
	bool finJuego_;
	char maze_[MAZE_SIZE][MAZE_SIZE];
	char maze_surface_[MAZE_SIZE][MAZE_SIZE];
	char maze_usuario_[2*MAZE_SIZE][2*MAZE_SIZE];
	char maze_objetos_[MAZE_SIZE][MAZE_SIZE];
	string mensaje_;
	string role_;
	int alcanzadox_, alcanzadoy_;
	bool alcanzado_;
	bool golpeado_;
	char vista_[10], surface_[10];
	int puntuacion_mapa_;
};
// -----------------------------------------------------------

#endif
