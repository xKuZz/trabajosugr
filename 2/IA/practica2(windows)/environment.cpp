#include <iostream>
#include <iomanip>
#include <string>
#include "GUI.h"
#include "stdlib.h"

#include "conexion.h"
#include "environment.h"
#include "include/GL/glui.h"

using namespace std;


const string trasto[10]={"Bikini","Piedra","LLaves","Rosa","Lingote de Oro","Oscar", "Zapatillas", "Pala", "Manzana", "Algoritmo"};

Environment::Environment()
{
    agentOriented_=0; //Siempre mira hacia el norte

	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			maze_usuario_[row][col]='?';
			maze_[row][col]='?';
		}// for - col
	}// for - row

	agentPosX_=5;
	agentPosY_=5;
    agentOriented_=0; //Siempre mira hacia el norte
	en_uso_='-';
	strcpy(mochila_,"----");
	puntuacion_=0;
	puntuacion_mapa_=0;
	vida=5;
	golpeado_=false;
	finJuego_=false;
	reiniciado_=false;
}

Environment::Environment(ifstream &infile)
{
	string comment;
	//getline(infile, comment);
	//infile >> agentPosX_ >> agentPosY_;
    agentOriented_=0; //Siempre mira hacia el norte

	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			char c;
			infile >> c;
			maze_[row][col]=c;
			maze_surface_[row][col]='?';
			maze_objetos_[row][col]='?';
		}// for - col
	}// for - row

	agentPosX_=5;
	agentPosY_=5;
	en_uso_='-';
	strcpy(mochila_,"----");
	puntuacion_=0;
	puntuacion_mapa_=0;
	vida=5;
	golpeado_=false;
	finJuego_=false;
	reiniciado_=false;

	RepartirObjetos(1, 2, 1, 1, 1, 1, 1, 1, 1, 1);

	int aldeano = 0;
	int princesa = rand()%2;
	int princeso = rand()%2;
	int leonardo = rand()%2;
	int bruja = rand()%2;
	int profe = rand()%2;

	RepartirPersonajes(aldeano,princesa,princeso,leonardo,bruja,profe);


	role_ = "PlYR";
}


void Environment::randomPos(int &x, int &y, int &ori){

	x= rand() %MAZE_SIZE;
	y= rand() %MAZE_SIZE;
	while (maze_[x][y]!='T' and maze_[x][y]!='S'){
		x= rand() %MAZE_SIZE;
		y= rand() %MAZE_SIZE;
	}
}


void Environment::randomPosPlayer(){
	int x,y,c;

	x= rand() %MAZE_SIZE;
	y= rand() %MAZE_SIZE;
	while (maze_[x][y]!='T'){
		x= rand() %MAZE_SIZE;
		y= rand() %MAZE_SIZE;
	}
	agentPosX_=x;
	agentPosY_=y;
	agentOriented_= rand()%4;
	vida = 5;
}



void PintaQuesitoParaArriba(double x, double y, double size, int color){
	glBegin(GL_POLYGON);
	if (color==0)
		glColor3f(1.0,0.0,0.0);
	else
		glColor3f(1.0,0.0,1.0);

	glVertex2f(x,y+size);
	glVertex2f(x+size,y-size);
	glVertex2f(x-size,y-size);
	glEnd();
}

void PintaQuesitoParaDerecha(double x, double y, double size, int color){
	glBegin(GL_POLYGON);
	if (color==0)
		glColor3f(1.0,0.0,0.0);
	else
		glColor3f(1.0,0.0,1.0);
	glVertex2f(x+size,y);
	glVertex2f(x-size,y-size);
	glVertex2f(x-size,y+size);
	glEnd();
}

void PintaQuesitoParaAbajo(double x, double y, double size, int color){
	glBegin(GL_POLYGON);
	if (color==0)
		glColor3f(1.0,0.0,0.0);
	else
		glColor3f(1.0,0.0,1.0);
	glVertex2f(x,y-size);
	glVertex2f(x+size,y+size);
	glVertex2f(x-size,y+size);
	glEnd();
}

void PintaQuesitoParaIzquierda(double x, double y, double size, int color){
	glBegin(GL_POLYGON);
	if (color==0)
		glColor3f(1.0,0.0,0.0);
	else
		glColor3f(1.0,0.0,1.0);
	glVertex2f(x-size,y);
	glVertex2f(x+size,y-size);
	glVertex2f(x+size,y+size);
	glEnd();
}


// -----------------------------------------------------------
void Environment::Show(int w,int h, char maze_entorno[200][200], char maze_objetos[200][200]) const
{
	//Determino la amplitud con valores del mapa (min 25 x 25)
	int esq_sup_izq_fila=0, esq_sup_izq_columna=0, esq_inf_dch_fila=199, esq_inf_dch_columna=199;

	bool encontrado = false;
	int i,j;
	for (i=0; i<199 and !encontrado; i++){
		for (j=0; j<199 and !encontrado; j++){
			if (maze_entorno[i][j]!='?')
				encontrado=true;
		}
	}
	esq_sup_izq_fila=i-1;
	esq_sup_izq_columna=j;

	encontrado=false;
	for(j=0; j<esq_sup_izq_columna and !encontrado;j++)
		for (int i=0;i<200 and !encontrado;i++)
			if (maze_entorno[i][j]!='?')
				encontrado = true;

	esq_sup_izq_columna=j-1;

	encontrado=false;
	for (i=199; i>0 and !encontrado; i--){
		for (j=199; j>=0 and !encontrado; j--){
			if (maze_entorno[i][j]!='?')
				encontrado=true;
		}
	}

	esq_inf_dch_fila= i;
	esq_inf_dch_columna=j;

	encontrado=false;
	for(j=199; j>esq_sup_izq_columna and !encontrado ;j--)
		for (int i=199;i>=0 and !encontrado ;i--)
			if (maze_entorno[i][j]!='?')
				encontrado = true;

	esq_inf_dch_columna=j;


	int tama;
	int tama_fila = esq_inf_dch_fila - esq_sup_izq_fila+1;
	int tama_col  = esq_inf_dch_columna - esq_sup_izq_columna+1;

	if (tama_fila<25 and tama_col<25){
		tama_fila=25;
		tama_col=25;
	}

	if (tama_fila>tama_col){
		esq_inf_dch_columna += (tama_fila - tama_col);
		tama = tama_fila;
	}
	else if (tama_fila<tama_col){
		esq_inf_dch_fila += (tama_col - tama_fila);
		tama = tama_col;
	}
	else
		tama=tama_fila;




	float length=(float)(w>h?h:w)/(float)(tama+4);
	float size=0.8*length;
	for (int row=0; row<tama; row+=1)
	{
		for (int col=0; col<tama; col+=1)
		{
			float x=(col-tama/2)*length*2+length,y=(tama/2-row)*length*2-length;
			char symbol = ' ';
   			if (row + esq_sup_izq_fila == agentPosX_ and col + esq_sup_izq_columna == agentPosY_){
				symbol = '=';
				switch (agentOriented_){
					case 0: // Orientacion Norte
					PintaQuesitoParaArriba(x,y,size,0);
					break;
					case 1: // Orientacion Este
					PintaQuesitoParaDerecha(x,y,size,0);
					break;
					case 2: // Orientacion Sur
					PintaQuesitoParaAbajo(x,y,size,0);
					break;
					case 3: // Orientacion Oeste
					PintaQuesitoParaIzquierda(x,y,size,0);
					break;
				}
			}
			switch (maze_objetos[row + esq_sup_izq_fila][col + esq_sup_izq_columna]){
			  case '0':
			  case '1':
			  case '2':
			  case '3':
			  case '4':
			  case '5':
			  case '6':
			  case '7':
			  case '8':
			  case '9':
					glBegin(GL_POLYGON);
					glColor3f(1.0,1.0,1.0);
					glVertex2f(x-size,y);
					glVertex2f(x,y-size);
					glVertex2f(x+size,y);
					glVertex2f(x,y+size);
					glEnd();
				    break;


			case 'a': switch(agentOriented_){
						case 0: PintaQuesitoParaAbajo(x,y,size,1);
						        break;
						case 1: PintaQuesitoParaIzquierda(x,y,size,1);
						        break;
						case 2: PintaQuesitoParaArriba(x,y,size,1);
						        break;
						case 3: PintaQuesitoParaDerecha(x,y,size,1);
						        break;
					  }
					  break;
			case 'b': switch(agentOriented_){
						case 0: PintaQuesitoParaDerecha(x,y,size,1);
						        break;
						case 1: PintaQuesitoParaAbajo(x,y,size,1);
						        break;
						case 2: PintaQuesitoParaIzquierda(x,y,size,1);
						        break;
						case 3: PintaQuesitoParaArriba(x,y,size,1);
						        break;
					  }
					  break;
			case 'c': switch(agentOriented_){
						case 0: PintaQuesitoParaArriba(x,y,size,1);
						        break;
						case 1: PintaQuesitoParaDerecha(x,y,size,1);
						        break;
						case 2: PintaQuesitoParaAbajo(x,y,size,1);
						        break;
						case 3: PintaQuesitoParaIzquierda(x,y,size,1);
						        break;
					  }
					  break;
			case 'd': switch(agentOriented_){
						case 0: PintaQuesitoParaIzquierda(x,y,size,1);
						        break;
						case 1: PintaQuesitoParaArriba(x,y,size,1);
						        break;
						case 2: PintaQuesitoParaDerecha(x,y,size,1);
						        break;
						case 3: PintaQuesitoParaAbajo(x,y,size,1);
						        break;
					  }
					  break;
			  case 'e': // Aldenao de frente
			  case 'f': // Aldeano de espaldas
			  case 'g': // Princesa Capichosa
			  case 'h': // Princesa Caprichosa
			  case 'i': // Leonardo Di Caprio
			  case 'j': // Leonardo Di Caprio
			  case 'k': // Princeso Valeroso
			  case 'l': // Princeso Valeroso
			  case 'm': // Bruja Malvada
			  case 'n': // Bruja Malvada
			  case 'o': // Profe IA
			  case 'p': // Profe IA
			  case 'q': // Oso
					glBegin(GL_POLYGON);
					glColor3f(1.0,0.65,0.125);
					glVertex2f(x-size,y);
					glVertex2f(x,y-size);
					glVertex2f(x+size,y);
					glVertex2f(x,y+size);
					glEnd();
				    break;
			}

			switch (maze_entorno[row + esq_sup_izq_fila][col + esq_sup_izq_columna]){
			  case 'P': glColor3f(0.0,0.0,0.0);
				    break;
			  case 'B': glColor3f(0.0,1.0,0.0);
				    break;
			  case 'A': glColor3f(0.0,0.0,1.0);
				    break;
			  case 'S': glColor3f(0.6,0.6,0.6);
				    break;
			  case 'M': glColor3f(0.6,0.0,0.0);
				    break;
			  case 'T': glColor3f(0.3,0.25,0.2);
				    break;
			  case 'K': glColor3f(1.0,1.0,0.0);
				    break;
			  case 'Z': glColor3f(0.3,0.3,0.3);
				    break;
			  case 'D': glColor3f(0.0,0.0,0.0);
				    break;
			  default: glColor3f(1.0,1.0,1.0);
			}
			glBegin(GL_POLYGON);
				glVertex2f(x-length,y-length);
				glVertex2f(x+length,y-length);
				glVertex2f(x+length,y+length);
				glVertex2f(x-length,y+length);
			glEnd();

		}// for - col
	}// for - row
}
// -----------------------------------------------------------
// -----------------------------------------------------------
void Environment::WhatIsInFrontOfMe(char *vision, char *movil, string &mensaje) {

    for (int i=0; i<10; i++)
      vision[i]='?';

    switch(agentOriented_){
        case 0: // Orientacion Norte
        	// Terreno
		vision[1]=maze_[agentPosX_-1][agentPosY_];
		for (int i=0; i<3; i++){
		  vision[2+i]=maze_[agentPosX_-2][agentPosY_+i-1];
		}
		for (int j=0; j<5; j++){
		  vision[5+j]=maze_[agentPosX_-3][agentPosY_+j-2];
		}

			// Superficie
		movil[1]=maze_objetos_[agentPosX_-1][agentPosY_];
		for (int i=0; i<3; i++){
		  movil[2+i]=maze_objetos_[agentPosX_-2][agentPosY_+i-1];
		}
		for (int j=0; j<5; j++){
		  movil[5+j]=maze_objetos_[agentPosX_-3][agentPosY_+j-2];
		}

	        break;
	case 1: // Orientacion Este
			// Terreno
		vision[1]=maze_[agentPosX_][agentPosY_+1];
		for (int i=0; i<3; i++){
		  vision[2+i]=maze_[agentPosX_+i-1][agentPosY_+2];
		}
		for (int j=0; j<5; j++){
		  vision[5+j]=maze_[agentPosX_+j-2][agentPosY_+3];
		}

			//Superficie
		movil[1]=maze_objetos_[agentPosX_][agentPosY_+1];
		for (int i=0; i<3; i++){
		  movil[2+i]=maze_objetos_[agentPosX_+i-1][agentPosY_+2];
		}
		for (int j=0; j<5; j++){
		  movil[5+j]=maze_objetos_[agentPosX_+j-2][agentPosY_+3];
		}
	        break;
        case 2: // Orientacion Sur
        		// Terreno
		vision[1]=maze_[agentPosX_+1][agentPosY_];
		for (int i=0; i<3; i++){
		  vision[2+i]=maze_[agentPosX_+2][agentPosY_+1-i];
		}
		for (int j=0; j<5; j++){
		  vision[5+j]=maze_[agentPosX_+3][agentPosY_+2-j];
		}

			//Surface
		movil[1]=maze_objetos_[agentPosX_+1][agentPosY_];
		for (int i=0; i<3; i++){
		  movil[2+i]=maze_objetos_[agentPosX_+2][agentPosY_+1-i];
		}
		for (int j=0; j<5; j++){
		  movil[5+j]=maze_objetos_[agentPosX_+3][agentPosY_+2-j];
		}

                break;
        case 3: // Orientacion Oeste
        		// Terreno
		vision[1]=maze_[agentPosX_][agentPosY_-1];
		for (int i=0; i<3; i++){
		  vision[2+i]=maze_[agentPosX_+1-i][agentPosY_-2];
		}
		for (int j=0; j<5; j++){
		  vision[5+j]=maze_[agentPosX_+2-j][agentPosY_-3];
		}

		movil[1]=maze_objetos_[agentPosX_][agentPosY_-1];
		for (int i=0; i<3; i++){
		  movil[2+i]=maze_objetos_[agentPosX_+1-i][agentPosY_-2];
		}
		for (int j=0; j<5; j++){
		  movil[5+j]=maze_objetos_[agentPosX_+2-j][agentPosY_-3];
		}

        break;
    }
    vision[0]=maze_[agentPosX_][agentPosY_];
    movil[0]=maze_objetos_[agentPosX_][agentPosY_];
    mensaje = "";

    for (int i=0; i<10; i++)
    	vista_[i]=vision[i];

    for (int i=0; i<10; i++)
    	surface_[i]=movil[i];

}
// -----------------------------------------------------------
void Environment::ColocarObjetos(int num, char objeto){
	bool colocado;
	int x,y,ori;

	for (int i=0; i<num; i++){
		colocado=false;
		while (!colocado){
			randomPos(x,y,ori);
			if (maze_surface_[x][y]=='?' and maze_objetos_[x][y]=='?'){
				colocado=true;
				maze_objetos_[x][y]=objeto;
			}
		}
	}
}

// -----------------------------------------------------------

void Environment::RepartirObjetos(int banador, int piedra, int espada, int rosa, int oro, int oscar,
								  int zapatillas, int pala, int manzana, int algoritmo){
	ColocarObjetos(banador,'0');
	ColocarObjetos(piedra,'1');
	ColocarObjetos(espada,'2');
	ColocarObjetos(rosa,'3');
	ColocarObjetos(oro,'4');
	ColocarObjetos(oscar,'5');
	ColocarObjetos(zapatillas,'6');
	ColocarObjetos(pala,'7');
	ColocarObjetos(manzana,'8');
	ColocarObjetos(algoritmo,'9');
}

void Environment::RepartirPersonajes(int aldeano, int Princesa, int princeso, int Leonardo, int bruja, int profe){
	ColocarObjetos(aldeano,'e');
	ColocarObjetos(Princesa,'g');
	ColocarObjetos(Leonardo,'i');
	ColocarObjetos(princeso,'k');
	ColocarObjetos(bruja,'m');
	ColocarObjetos(profe,'o');
}


// -----------------------------------------------------------
void Environment::DesperdigarObjetosTrasReiniciado(){
	if (en_uso_!='-'){
		ColocarObjetos(1,en_uso_);
		en_uso_='-';
	}
	int i=0;
	while (i<5 and mochila_[i]!='-'){
		ColocarObjetos(1,mochila_[i]);
		mochila_[i]='-';
		i++;
	}
	vida=5;

}
// -----------------------------------------------------------
void Environment::AcceptAction(Agent::ActionType action)
{
	char delante[10];
	char movil[10];
	bool avanza=false;
	mensaje_="";
	reiniciado_=false;
	alcanzado_=false;

	if (golpeado_){
		golpeado_=false;
		reiniciado_=true;
		randomPosPlayer();
		DesperdigarObjetosTrasReiniciado();
		mensaje_+="Alguien te golpeo con una piedra. Quedas reiniciado. ";
	}
	else {
		WhatIsInFrontOfMe(delante, movil, mensaje_);
		switch (action)
		{
			case 0: // Avanzar

			    if (delante[1]=='A' and en_uso_!='0'){
			    	mensaje_+="Caiste al agua. ";
			    	reiniciado_=true;
					DesperdigarObjetosTrasReiniciado();
			    	randomPosPlayer();
			    }
			    else if (delante[1]=='B' and en_uso_!='6'){
			    	mensaje_+="Menudo golpe contra el arbol. ";
			    	vida--;
			    	if (vida==0){
			    		mensaje_+="Este golpe ha sido fatal, quedas reiniciado. ";
			    		reiniciado_=true;
						DesperdigarObjetosTrasReiniciado();
				    	randomPosPlayer();
			    	}
			    }
			    else if (delante[1]=='P'){
			    	mensaje_+="Por que te suicidas tirandote por el precipicio!!!. ";
			    	reiniciado_=true;
					DesperdigarObjetosTrasReiniciado();
				    randomPosPlayer();

			    }
			    else if (delante[1]=='M'){
			    	mensaje_+="Intentando atravesar un muro, Copperfield?. ";
			    	vida--;
			    	if (vida==0){
			    		mensaje_+="Este golpe ha sido fatal, quedas reiniciado. ";
			    		reiniciado_=true;
						DesperdigarObjetosTrasReiniciado();
				    	randomPosPlayer();
			    	}
			    }
			    else if (delante[1]=='D' and en_uso_!='2'){
			    	mensaje_+="Intentando atravesar una puerta cerrada, Eres un fantasma?. ";
			    	vida--;
			    	if (vida==0){
			    		mensaje_+="Este golpe ha sido fatal, quedas reiniciado. ";
			    		reiniciado_=true;
						DesperdigarObjetosTrasReiniciado();
				    	randomPosPlayer();
			    	}
			    }
			    else if (movil[1]>='a' and movil[1]<='z'){
			    	mensaje_+="Has chocado con un obstaculo movil. ";
			    }
			    else{
			    	avanza=true;
					switch(agentOriented_){
					  case 0: // Orientacion Norte
						  agentPosX_-=1;
						  break;
					  case 1: // Orientacion Este
						  agentPosY_+=1;
						  break;
					  case 2: // Orientacion Sur
						  agentPosX_+=1;
						  break;
					  case 3: // Orientacion Oeste
						  agentPosY_-=1;
						  break;

					}
			    }
			    break;
			case 1: // Girar a la izquierda
			    agentOriented_ = (agentOriented_+3)%4;
				break;
			case 2: // Girar a la derecha
			    agentOriented_ = (agentOriented_+1)%4;
				break;
			case 3: // No hacer nada
				mensaje_+="Asi me gusta, que no te precipites!!. ";
				break;
			case 4: // Recoger
				if (movil[0]<'0' or movil[0]>'9'){
					mensaje_+="No hay nada que recoger. ";
				}
				else if (en_uso_!='-'){
					mensaje_+="Tienes que tener las manos libres para recoger un objeto. ";
				}
				else {
					en_uso_= maze_objetos_[agentPosX_][agentPosY_];
					maze_objetos_[agentPosX_][agentPosY_]='?';
					switch(en_uso_){

						case '0':
								  mensaje_+="Recogido bikini. ";
								  break;
						case '1':
								  mensaje_+="Recogida piedra. ";
								  break;
						case '2':
								  mensaje_+="Recogidas llaves. ";
								  break;
						case '3':
								  mensaje_+="Recogida rosa. ";
								  break;
						case '4':
								  mensaje_+="Recogido lingote de oro. ";
								  break;
						case '5':
								  mensaje_+="Recogido Oscar, no sabes la ilusion que me hace y lo quiero dedicar... ";
								  break;
						case '6':
								  mensaje_+="Recogidas zapatillas. ";
								  break;
						case '7':
								  mensaje_+="Recogida pala. ";
								  break;
						case '8':
								  mensaje_+="Recogida manzana. ";
								  break;
						case '9':
								  mensaje_+="Recogido algoritmo, no se como, pero lo he recogido. ";
								  break;
					}
				}
				break;
      		case 5: // Soltar
				if (en_uso_=='-'){
					mensaje_+="No tienes nada en las manos para soltar. ";
				}
				else if (movil[0]!='?'){
					mensaje_+="Aqui no se puede soltar. Busca otro sitio. ";
				}
				else {
					maze_objetos_[agentPosX_][agentPosY_]=en_uso_;
					en_uso_= '-';
					switch(maze_objetos_[agentPosX_][agentPosY_]){
						case '0':
						case '4':
						case '5':
								  mensaje_+="Soltado"+ trasto[maze_objetos_[agentPosX_][agentPosY_]-48]+ ". ";
								  break;
						case '9':
						case '1':
						case '2':
						case '3':
						case '6':
						case '7':
						case '8':
								  mensaje_+="Soltada"+ trasto[maze_objetos_[agentPosX_][agentPosY_]-48]+ ". ";
								  break;
					}
				}
				break;
			case 6: // Guardar
				if (en_uso_=='-'){
					mensaje_+="No tienes nada para guardar. ";
				}
				else{
					int i=0;
					while (i<5 and mochila_[i]!='-')
						i++;
					if (i==5){
						mensaje_+="No lo puedes guardar, la mochila esta llena. ";
					}
					else {
						mensaje_+="Guardado objeto en la mochila. ";
						mochila_[i]=en_uso_;
						en_uso_='-';
					}
				}
			    break;
			case 7: // Sacar
				if (en_uso_!='-'){
					mensaje_+="Tienes las manos ocupadas!!!. ";
				}
				else if (mochila_[0]=='-'){
					mensaje_+="Tienes la mochila vacia!!!. ";
				}
				else {
					en_uso_=mochila_[0];
					for (int i=1; i<4; i++)
						mochila_[i-1]=mochila_[i];
					mochila_[3]='-';
					mensaje_+="Usando "+trasto[en_uso_-48]+".  ";
				}
				break;
			case 8: // Dar
				if (en_uso_=='-'){
					mensaje_+="No tienes en la mano nada que dar. ";
				}
				else if (movil[1]=='?'){
					mensaje_+="No hay nadie a quien darle eso. ";
				}
				else if (movil[1]<'g' or movil[1]>'p'){
					mensaje_+="No le interesa lo que le quieres dar. ";
				}
				else {
					mensaje_+="Objeto Entregado. ";
					// Cambiar puntuacion en funcion de que se ha entregado a quien.
					Puntuar(en_uso_,movil[1], mensaje_);
					// Generar otro item igual al entregado y posicionarlo aleatoriamente en el mapa.
					ColocarObjetos(1,en_uso_);
					en_uso_='-';
				}
				break;
			case 9: // Lanzar
				if (en_uso_=='-'){
					mensaje_+="Muy bien, y te parece bonito lanzar aire; Muy original. ";
				}
				else if (en_uso_!='1'){
					mensaje_+="Eres salvaje, eso no se puede lanzar. ";
				}
				else {
					en_uso_='-';
					alcanzado_=false;
					// Determinar si le ha dado a alguien
					int new_fila, new_columna, i=1;
					cout << "Orientacion agente: " << agentOriented_ << endl;

					cout << "Trayectoria: ";
					switch (agentOriented_){
						case 0:
								  	while (i<5 and agentPosX_-i>=0 and
								  		(maze_objetos_[agentPosX_-i][agentPosY_]<'a' or
								  		maze_objetos_[agentPosX_-i][agentPosY_]>'q') and
								  		maze_[agentPosX_-i][agentPosY_]!='B' and
								  		maze_[agentPosX_-i][agentPosY_]!='M' and
								  		maze_[agentPosX_-i][agentPosY_]!='D'){

								  		cout << maze_[agentPosX_-i][agentPosY_];
								  		i++;
								  	}
								  	if (i<5 and agentPosX_-i>=0){
								  		new_fila=agentPosX_-i;
								  		new_columna=agentPosY_;
								  		alcanzado_=true;
								  	}
								  	cout << endl;
								  	cout << "valor de i: "<< i << endl;
								  	break;
						case 1:
								  	while (i<5 and agentPosY_+i<200 and
								  		 (maze_objetos_[agentPosX_][agentPosY_+i]<'a' or
								  		 maze_objetos_[agentPosX_][agentPosY_+i]>'q') and
								  		 maze_[agentPosX_][agentPosY_+i]!='B' and
								  		 maze_[agentPosX_][agentPosY_+i]!='M' and
								  		 maze_[agentPosX_][agentPosY_+i]!='D'){

								  		cout << maze_[agentPosX_][agentPosY_+i];
								  		i++;
								  	}
								  	if (i<5 and agentPosY_+i<200){
								  		new_fila=agentPosX_;
								  		new_columna=agentPosY_+i;
								  		alcanzado_=true;
								  	}
								  	cout << endl;
								  	cout << "valor de i: "<< i << endl;
								  	break;
						case 2:
								  	while (i<5 and agentPosX_+i<200 and
								  		 (maze_objetos_[agentPosX_+i][agentPosY_]<'a' or
								  		 maze_objetos_[agentPosX_+i][agentPosY_]>'q') and
								  		 maze_[agentPosX_+i][agentPosY_]!='B' and
								  		 maze_[agentPosX_+i][agentPosY_]!='M' and
								  		 maze_[agentPosX_+i][agentPosY_]!='D'){

								  		cout << maze_[agentPosX_+i][agentPosY_];

								  		i++;
								  	}
								  	if (i<5 and agentPosX_+i<200){
								  		new_fila=agentPosX_+i;
								  		new_columna=agentPosY_;
								  		alcanzado_=true;
								  	}
								  	cout << endl;
								  	cout << "valor de i: "<< i << endl;
								  	break;
						case 3:
								  	while (i<5 and agentPosY_-i>=0 and
								  		 (maze_objetos_[agentPosX_][agentPosY_-i]<'a' or
								  		 maze_objetos_[agentPosX_][agentPosY_-i]>'q') and
								  		 maze_[agentPosX_][agentPosY_-i]!='B' and
								  		 maze_[agentPosX_][agentPosY_-i]!='M' and
								  		 maze_[agentPosX_][agentPosY_-i]!='D'){

								  		cout << maze_[agentPosX_][agentPosY_-i];
								  		i++;
								  	}
								  	if (i<5 and agentPosY_-i>0){
								  		new_fila=agentPosX_;
								  		new_columna=agentPosY_-i;
								  		alcanzado_=true;
								  	}
								  	cout << endl;
								  	cout << "valor de i: "<< i << endl;
								  	break;



					}
					if (alcanzado_){ // Has alcanzado algo
						cout << "fila: " << new_fila << "  columna: " << new_columna
							 << " maze: " << maze_[new_fila][new_columna] << " "
							 << "objetos: " << maze_objetos_[new_fila][new_columna] << endl;

						if (maze_[new_fila][new_columna]=='B'){ // Le dio a un arbol
							mensaje_+= "Se oye ruido de pajaros, le diste a un arbol. ";
							alcanzado_=false;
						}
						else if (maze_[new_fila][new_columna]=='M'){ // Le dio a un muro
							mensaje_+= "No destroces el mobiliario urbano!!. ";
							alcanzado_=false;
						}
						else if (maze_[new_fila][new_columna]=='D'){ // Le dio a una puerta
							mensaje_+= "No le tires piedras a mi puerta, gamberros!!. ";
							alcanzado_=false;
						}
						else if (maze_objetos_[new_fila][new_columna]>='e' and maze_objetos_[new_fila][new_columna]<='p'){ // Le dio a un muro
							mensaje_+= "Esto es intolerable; Quedas reiniciado. ";
							alcanzado_=false;
							reiniciado_=true;
							randomPosPlayer();
							DesperdigarObjetosTrasReiniciado();
						}
						else if (maze_objetos_[new_fila][new_columna]=='q'){ // Le dio a un oso
							mensaje_+= "Le diste al oso!!! Buena Punteria; Consigues 100 puntos. ";
							puntuacion_+=100;
							alcanzadox_=new_fila;
							alcanzadoy_=new_columna;
							// Reubicar al oso en otro punto del mapa
						}
						else if (maze_objetos_[new_fila][new_columna]>='a' and maze_objetos_[new_fila][new_columna]<='d'){
							mensaje_+="Le diste a otro jugador!!! dice que ya te pillara; Consigues 50 puntos. ";
							puntuacion_+=50;
							alcanzadox_=new_fila;
							alcanzadoy_=new_columna;
							// Encontrar al jugador, avisarle que ha sido alcanzado y reiniciarlo.
						}
						else {
							mensaje_+="No le diste a nada. ";
							alcanzado_=false;
						}


					}
					else
						mensaje_+="Eres muuu malo, o muy civilizado, no le has dado a nadie. ";

					// Generar aleatoriamente una nueva piedra y posicionarla aleatoriamente en el mapa.
					ColocarObjetos(1,'1');
				}
				break;
		}

		// Manda mensaje en funcion de lo que hay en la nueva posicion.
		if (avanza){
			if (delante[1]=='K'){
                char aux1[20], aux2[20];
                string saux1, saux2;
                sprintf(aux1, "%d", agentPosX_);
                sprintf(aux2, "%d", agentPosY_);
                saux1=aux1;
                saux2=aux2;

				mensaje_+="PK fila: "+saux1+" columna: " + saux2+". ";
			}
			else if ( (movil[1]>='0' and movil[1]<='9') or (movil[3]>='a' and movil[3]<='z') ){
				switch (movil[1]){
					case '0':
							  mensaje_+="Has encontrado un bikini, y parece de tu talla. ";
							  break;
					case '1':
							  mensaje_+="Has encontrado una piedra, que suerte la mia!!. ";
							  break;
					case '2':
							  mensaje_+="Has encontrado una llave, que puerta abrira?. ";
							  break;
					case '3':
							  mensaje_+="Has encontrado una rosa, ayyyyyyyyyyyy!! pincha. ";
							  break;
					case '4':
							  mensaje_+="Has encontrado un lingote de oro, bien bien BIEN!!!. ";
							  break;
					case '5':
							  mensaje_+="Has encontrado un Oscar, no sabia que se puediera encontrar esto!!!. ";
							  break;
					case '6':
							  mensaje_+="Has encontrado unas zapatillas, con sus cordones y todo!!!. ";
							  break;
					case '7':
							  mensaje_+="Has encontrado una pala, si, una pala de cavar; Para cavar estoy yo!!. ";
							  break;
					case '8':
							  mensaje_+="Has encontrado una manzana, y por poco no te dio en la cabeza Einstein. ";
							  break;
					case '9':
							  mensaje_+="Has encontrado un algoritmo, UN ALGORITMO!!!, COMO UN ALGORITMO?. ";
							  break;
				}
				switch (movil[3]){
					case 'e':
					case 'f':
							  mensaje_+="Hola Aldeano. ";
							  break;
					case 'g':
					case 'h':
							  mensaje_+="Hola Princesa. ";
							  break;
					case 'i':
					case 'j':
							  mensaje_+="Hombre!! Leonardo Di Caprio. ";
							  break;
					case 'k':
					case 'l':
							  mensaje_+="Eres el principe valiente? ";
							  break;
					case 'm':
					case 'n':
							  mensaje_+="Jod..!! Una bruja. ";
							  break;
					case 'o':
					case 'p':
							  mensaje_+="Querido Profe!!. ";
							  break;
					case 'q':
							  mensaje_+="Un oso!! pies para que os quiero!!! ";
							  break;
				}
			}
		}
	}
}

// ------------------------------------------------------------
void Environment::SenSorStatus(char *terreno, char *objetos, string &mensaje, bool &reiniciar, char &en_uso, char *mochila,
	char *puntuacion, bool &finjuego, char &salud, bool remote){
	if (!remote)
		WhatIsInFrontOfMe(terreno,objetos,mensaje);
	else{
		for (int i=0; i<10; i++)
			terreno[i]=vista_[i];

		for (int i=0; i<10; i++)
			objetos[i]=surface_[i];
	}
	mensaje = mensaje_;
	reiniciar = reiniciado_;
	en_uso = en_uso_;
	strcpy(mochila, mochila_);
    char aux1[20];
    sprintf(aux1, "%d", puntuacion_);
	strcpy(puntuacion, aux1);
	finjuego=finJuego_;
	salud = vida+48;
}


// -----------------------------------------------------------
int Environment::Puntuar(char objeto, char personaje, string &mensaje){
	int valor=0;
	switch (objeto){
		case '0':
		case '1':
		case '2':
		case '3':
		case '6':
		case '7':
				  mensaje+="Menudo regalo de mie...!! Anda alejate de mi vista";
				  break;
		case '4':
				  switch(personaje){
				  	case 'g':
				  	case 'h':
				  		mensaje+="PRINCESA: Tu si que sabes lo que me gusta!!!. ";
				  		valor=100;
						break;
				  	case 'i':
				  	case 'j':
				  		mensaje+="LEONARDO: No esta mal, pero prefiero otra cosa en este mismo color. ";
				  		valor=75;
						break;
				  	case 'k':
				  	case 'l':
				  		mensaje+="PRINCESO: Yo soy valeroso, pero nunca digo no al oro. ";
				  		valor=90;
						break;
				  	case 'm':
				  	case 'n':
				  		mensaje+="BRUJA: Esto no es util para mis pociones. ";
				  		valor=10;
						break;
				  	case 'o':
				  	case 'p':
				  		mensaje+="PROFE IA: Esto no sera un soborno?, Como te atreves? Me lo quedo por no hacerte el feo. ";
				  		valor=50;
						break;
				  }
			          break;
		case '5':
				  switch(personaje){
				  	case 'g':
				  	case 'h':
				  		mensaje+="PRINCESA: Que bonito!! Soy tu estrella. ";
				  		valor=50;
						break;
				  	case 'i':
				  	case 'j':
				  		mensaje+="LEONARDO: Por fin tengo un Oscar!!! Gracias, quiero agradecer este Oscar... ";
				  		valor=100;
						break;
				  	case 'k':
				  	case 'l':
				  		mensaje+="PRINCESO: Soy un guerrero, no me traigas cosas de adorno. ";
				  		valor=25;
						break;
				  	case 'm':
				  	case 'n':
				  		mensaje+="BRUJA: Esto es bueno para remover el caldero de las pociones. ";
				  		valor=70;
						break;
				  	case 'o':
				  	case 'p':
				  		mensaje+="PROFE IA: Estas de broma, verdad? Que hago yo con eso. ";
				  		valor=25;
						break;
				  }
			          break;
		case '8':
				  switch(personaje){
				  	case 'g':
				  	case 'h':
				  		mensaje+="PRINCESA: Eres una bruja? Tu has leido alguna vez un cuento? No me fio de las manzanas. ";
				  		valor=30;
						break;
				  	case 'i':
				  	case 'j':
				  		mensaje+="LEONARDO: Pues gracias, ya empezaba a tener hambre. ";
				  		valor=50;
						break;
				  	case 'k':
				  	case 'l':
				  		mensaje+="PRINCESO: Los guerreros tambien comemos, bien visto!. ";
				  		valor=75;
						break;
				  	case 'm':
				  	case 'n':
				  		mensaje+="BRUJA: Gracias, esto es justo lo que estaba buscando. ";
				  		valor=100;
						break;
				  	case 'o':
				  	case 'p':
				  		mensaje+="PROFE IA: Una manzana? y donde ha quedado lo del jamon. ";
				  		valor=75;
						break;
				  }
			          break;
		case '9':
				  switch(personaje){
				  	case 'g':
				  	case 'h':
				  		mensaje+="PRINCESA: 'A' estrella dices? Bueno me lo quedo por lo de la estrella. ";
				  		valor=10;
				  		break;
				  	case 'i':
				  	case 'j':
				  		mensaje+="LEONARDO: Dices que esto me valdra para obtener un Oscar? No termino de creerte. ";
				  		valor=10;
				  		break;
				  	case 'k':
				  	case 'l':
				  		mensaje+="PRINCESO: Los guerreros tambien tenemos apretones, me vendra bien antes de la batalla. ";
				  		valor=50;
				  		break;
				  	case 'm':
				  	case 'n':
				  		mensaje+="BRUJA: Se parece a uno de mis conjuros aunque este genera peores vibraciones. ";
				  		valor=75;
				  		break;
				  	case 'o':
				  	case 'p':
				  		mensaje+="PROFE IA: Que dije de no pasar codigo? Es que tengo que repetir todo 100 veces. ";
				  		valor=100;
				  }
			          break;

	}
    char aux1[20];
    string saux1;
    sprintf(aux1, "%d", valor);
    saux1=aux1;

	mensaje+="Te han dado "+saux1+" puntos";
	puntuacion_+=valor;
	return valor;
}

// -----------------------------------------------------------
void Environment::ActualizarMatrizUsuario(char mapa[200][200]){
	for (int i=0; i<200; i++)
		for (int j=0; j<200; j++)
			maze_usuario_[i][j]=mapa[i][j];
}

// -----------------------------------------------------------
bool Environment::Perceive_Remote(conexion_client &Cliente){

	bool actualizado=false;
	char salud, valor[9];

	cout << "Antes de recibir el paquete\n";
    Cliente.Recibir_Msg_NoBlocking(vista_, surface_, mensaje_, reiniciado_,
      en_uso_, mochila_, valor, finJuego_, salud, actualizado);

    vida=salud-48;
    puntuacion_ = atoi(valor);



	cout << "Despues de recibir el paquete\n";

    return actualizado;
}



int Environment::Comparar(char m[100][100]) const{

	double aciertos=0;
	for (int i=0; i<100; i++)
		for (int j=0; j<100; j++)
			if (maze_[i][j]==m[i][j]){
				aciertos++;
			}
	int porcentaje = aciertos/100;
	return porcentaje;
}
