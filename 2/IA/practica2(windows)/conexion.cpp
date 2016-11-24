#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/socket.h> //Linux
//#include <arpa/inet.h> //Linux
#include <winsock2.h>  //Windows
#include "conexion.h"

const int PORT = 5126;


int conexion_server::Crear_Servidor(){
	 char error[200];
char bienvenido[]="Bienvenido al server de las cuatro en raya.";

    WSADATA wsaData;                // Inicializamos la libreria de socket de windows
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
    printf("Error iniciando Winsock, de windows XP");
    exit(1);
    }
    else
    printf("\nIniciado Winsock, de windows XP\n");

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0){ // creamos el socket
    printf("Error creando el socket, saliendo�");
    exit(0);
    }
    else
    printf("Socket Creado con exito\n");

    server.sin_family= AF_INET; // familia socket
    server.sin_addr.s_addr = INADDR_ANY;
    cout << "direccion ip: " << server.sin_addr.s_addr << endl;
    //server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(5126); //Puerto

    if(bind(sock,(struct sockaddr *)&server,sizeof(server))<0 ){//bindeamos�
    printf("error asociando socket al puerto�");exit(0);
    }
    else
    printf("Bind con exito\n");

    listen(sock,5);    // nos quedamos a la espera con una cola de maximo 5 clientes
}


int conexion_server::Aceptar_Cliente(){
    if((conectado=accept(sock,0,0))<0){ //Es pero al primer cliente
            printf("error aceptando connexion");
            exit(0);
    }
    return conectado;
}


void conexion_server::Enviar_Cliente_Msg(const char *msg){
    char tama=strlen(msg);
    // Primero envio la longitud del mensaje
    if(send(conectado,&tama,1,0)<0){
        printf("error enviando logitud del mensaje");
        exit(0);
    }

    // Ahora envio el mensaje
    if(send(conectado,(char*) msg,tama,0)<0){
        printf("error enviando msg");
        exit(0);
    }
    else{
      cout << "\t\tEnviado el mensaje: " << msg << endl;
    }

}


void conexion_server::Recibir_Mapa(char m[100][100]){
    if(recv(conectado,(char*) m,10000,0)<0){ // Envio Estado para jugador 1
        printf("error recibiendo mapa");
        exit(0);
    }

}

void conexion_server::Recibir_Mensaje(char* msg){
   memset(msg,0,sizeof(msg));           //esta funcion vacia el buffer de entrada
   char tama;
   // Primero recibo la longitud del mensaje
   int bytesrecv=recv(conectado,&tama,1,0);
   if(bytesrecv == -1){
        cout <<"Error recibiendo la longitud del mensaje, saliendo...";
        exit(0);
    }

   bytesrecv=recv(conectado,msg,tama,0);

   if(bytesrecv == -1){
        cout <<"Error recibiendo msg, saliendo...";
        exit(0);
    }
    else{
        msg[bytesrecv]='\0';
        //cout << "\t\tRecibido mensaje: " << msg << endl;
    }
}


char conexion_server::Recibir_Accion(){
   //memset(buffer,0,sizeof(buffer));           //esta funcion vacia el buffer de entrada
   char aux;

   if((bytesrecv=recv(conectado,&aux,1,0))==-1){
        printf("Error recibiendo accion, saliendo�");
        exit(0);
    }

    return aux;
}

void conexion_server::Enviar_Accion_al_Cliente(const char accion){
    if(send(conectado,(char*) &accion,1,0)<0){ // Envio Estado para jugador 1
        printf("Error enviando accion al cliente, saliendo�");
        exit(0);
    }
}


void conexion_server::Cerrar_Conexion(){
    cout << "Cerrada la conexion por el servidor" << endl;
    //close(conectado);
}



// Para el cliente


int conexion_client::Establecer_Conexion(const char *dir_ip, const char *puerto){
	 char error[200];
     int correcto=1;
    WSADATA wsaData; // Si esto no funciona //WSAData wsaData; // prueba esto en su lugar
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
       printf("Error iniciando Winsock, de windows XP");
       exit(1);
    }

    direccion.sin_addr.s_addr=inet_addr(dir_ip);
    direccion.sin_family=AF_INET;                // protocolo af inet, visto antes.
    direccion.sin_port=htons(atoi(puerto));     //htons convierte el puerto al formato de red.

    sock=socket(AF_INET,SOCK_STREAM,0);          // obtenemos el descriptor del socket
    if(sock < 0){                                //Error
        perror(error);
        printf("%s",error);
        correcto=0;
        }
    else{
        printf("\nsocket creado con exito");
    //conectamos al servidor
        if(connect(sock,(struct sockaddr*)&direccion,sizeof(direccion))<0)
        {
            printf("error conectando...");
            correcto=0;
        }

        printf("\nconectado al servidor\n");
    }

    return correcto;
}


void conexion_client::Enviar_Msg(const char *msg){
    char tama=strlen(msg);
    // Primero envio la longitud del mensaje
    if(send(sock,&tama,1,0)<0){ // Mensaje bienvenida para jugador 1
        printf("error enviando msg de bienvenida");
        exit(0);
    }

    // Ahora envio el mensaje
    if(send(sock,(char*) msg,tama,0)<0){ // Mensaje bienvenida para jugador 1
        printf("error enviando msg de bienvenida");
        exit(0);
    }
    else{
      cout << "\t\tEnviado el mensaje: " << msg << endl;
    }

}


void conexion_client::Recibir_Msg(char *msg){
    //memset(buffer,0,sizeof(buffer));           //esta funcion vacia el buffer de entrada
    char tama;
    // Primero recibo la longitud del mensaje
    bytesrecv=recv(sock,&tama,1,0);
    //bytesrecv=recv(sock,&tama,1,MSG_DONTWAIT);
    msg[0]='\0';

    // Ahora recibo el mensaje
    if (bytesrecv>0){
        bytesrecv=recv(sock,msg,tama,0);
        if(bytesrecv == -1){
            cout <<"Error recibiendo msg, saliendo...";
            exit(0);
        }
        else{
            msg[bytesrecv]='\0';
            cout << "\t\tRecibido mensaje: " << msg << endl;
        }
    }
    //strcpy(msg,buffer);
}


void conexion_client::Recibir_Msg_NoBlocking(char *vision, char *objetos, string &mensaje, bool &reiniciar,
	char &en_uso, char *mochila, char *puntuacion, bool &finjuego, char &vida,	bool &recibido){
    //memset(buffer,0,sizeof(buffer));           //esta funcion vacia el buffer de entrada
    char tama;
    recibido=false;
    // Primero recibo la longitud del mensaje
    //bytesrecv=recv(sock,&tama,1,MSG_DONTWAIT);
	bytesrecv=recv(sock,&tama,1,0);

    if(bytesrecv == -1){
        cout <<"Error recibiendo msg1, saliendo...";
        exit(0);
    }

    if (bytesrecv!=0){
        // Ahora recibo el paquete

		char *paquete = new char[tama+1];

        bytesrecv=recv(sock,paquete,tama,0);
        if(bytesrecv == -1){
            cout <<"Error recibiendo el paquete, saliendo...";
            exit(0);
        }
            cout << "tama: " << tama << endl;
				paquete[tama]='\0';
				string tmp = paquete;
                cout << " Paquete: " << tmp << endl;
				//Extraigo la vision
				for (int i=0; i<10; i++){
				  vision[i]=tmp[i];
				}

				//Extraigo los objetos
				for (int i=10; i<20; i++)
				  objetos[i-10]=tmp[i];


				en_uso = tmp[20];

				for (int i=21; i<25; i++)
				  mochila[i-21]=tmp[i];
				mochila[4]='\0';


				if (tmp[25]=='1')
					reiniciar=true;
				else
				  reiniciar=false;

				for (int i=26; i<34; i++)
				  puntuacion[i-26]=tmp[i];
				puntuacion[9]='\0';


				if (tmp[34]=='1')
					finjuego=true;
				else
				  finjuego=false;

				vida = tmp[35];

				mensaje = tmp.substr(36);
				// activo senal de recibido
        recibido=true;
        delete [] paquete;
    }

    //strcpy(msg,buffer);
    if (recibido)
        cout << "Recibido Paquete\n";
}


void conexion_client::Enviar_Mapa(char m[100][100]){
     memset(buffer,0,sizeof(buffer));           //esta funcion vacia el buffer de entrada
     char *memory=new char[10000];
     for (int i=0; i<100; i++)
        for (int j=0; j<100; j++)
            memory[i*100+j];

     bytesenv=send(sock,memory,10000,0);
     if(bytesenv == -1){
       printf("Error enviando el mapa...");
       exit(0);
      }

    delete [] memory;
}


void conexion_client::Enviar_Accion(char accion){
        bytesenv=send(sock,&accion,1,0);
        if(bytesenv == -1){
            cout<< "error enviando msg, cerrando...";
            exit(0);
        }
}

char conexion_client::Recibir_Accion_del_Servidor(){
   char aux;

   if((bytesrecv=recv(sock,&aux,1,0))==-1){
        printf("Error recibiendo accion, saliendo�");
        exit(0);
    }

    return aux;

}


void conexion_client::Cerrar_Conexion(){
   cout << "Cerrada la conexion por el cliente" << endl;
   //close(sock);
}
