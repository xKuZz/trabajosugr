#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define tagOcupar 0
#define tagLiberar 1
#define tagSentarse 2
#define tagLevantarse 3
#define CAMARERO 10

using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);
void Camarero();

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;

   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   if( size!=11)
   {
      if( rank == 0)
         cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( );
      return 0;
   }

   if(rank==CAMARERO)
        Camarero();
   else if((rank % 2)==0)
        Filosofo(rank,size);
   else
        Tenedor(rank,size);


   MPI_Finalize( );
   return 0;
}
// ---------------------------------------------------------------------

void Filosofo( int id, int nprocesos )
{
   int izq = (id+1) % nprocesos;
   int der = ((id+nprocesos)-1) % nprocesos;

   while(1)
   {

       // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;

      // espera bloqueado durante un intervalo de tiempo aleatorio
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );

      //Solicita sentarse en la mesa.
      cout << "Filosofo " << id << " solicita sentarse en la mesa al camarero." << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,CAMARERO,tagSentarse,MPI_COMM_WORLD);

      // Solicita tenedor izquierdo
      cout << "Filosofo "<<id<< " solicita tenedor izq ..." << izq << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,izq,tagOcupar,MPI_COMM_WORLD);

      // Solicita tenedor derecho
      cout <<"Filosofo "<<id<< " solicita tenedor der ..." << der << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,der,tagOcupar,MPI_COMM_WORLD);

      cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo

      // Suelta el tenedor izquierdo
      cout <<"Filosofo "<<id<< " suelta tenedor izq ..." << izq << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,izq,tagLiberar,MPI_COMM_WORLD);

      // Suelta el tenedor derecho
      cout <<"Filosofo "<<id<< " suelta tenedor der ..." << der << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,der,tagLiberar,MPI_COMM_WORLD);

      // Solicita levantarse de la mesa.
      cout << "Filosofo " << id << " solicita levantarse de la mesa al camarero." << endl << flush;
      MPI_Ssend(NULL,0,MPI_INT,CAMARERO,tagLevantarse,MPI_COMM_WORLD);


 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  MPI_Status status;
  int Filo;

  while( true )
  {
    // Espera un peticion desde cualquier filosofo vecino para ocupar el tenerdor en cuestión ...
    MPI_Probe(MPI_ANY_SOURCE,tagOcupar,MPI_COMM_WORLD,&status);

    Filo=status.MPI_SOURCE;

    // Recibe la peticion del filosofo ...
    MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,tagOcupar,MPI_COMM_WORLD,&status);

    cout << "Ten. " << id << " recibe petic. de " << Filo << endl << flush;

    // Espera a que el filosofo suelte el tenedor...
    MPI_Recv(NULL,0,MPI_INT,Filo,tagLiberar,MPI_COMM_WORLD,&status);
    cout << "Ten. " << id << " recibe liberac. de " << Filo << endl << flush;
  }
}

  void Camarero(){
    const int MAXFILO=4;  // Este es elmaximo de filosofos que puede haber sentados en la mesa por definición del problema.
    int mesa=0, peticion=1; // Variable que indica los filosofos que hay en la mesa sentados.
    MPI_Status status;
    while(true){
            if(mesa==0)  // En el caso de que la mesa esta vacía solo puede esperar un mensaje de un filosofo para sentarse
                MPI_Probe(MPI_ANY_SOURCE,tagSentarse,MPI_COMM_WORLD,&status);
            else if(mesa<MAXFILO)// EN el caso de que haya alguien en la mesa pero no este ocupada al completo puede recibir mensajes tanto para levantarse como para sentarse
                MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            else  //En elcasode que la mesa este completa solo puede recibir mensajes para levantarse nopara sentarse.
                MPI_Probe(MPI_ANY_SOURCE,tagLevantarse,MPI_COMM_WORLD,&status);

        if(status.MPI_TAG==tagSentarse){  // Si el mensaje que ha recibido es de sentarse
            MPI_Recv(NULL,0,MPI_INT,status.MPI_SOURCE,tagSentarse,MPI_COMM_WORLD,NULL);
            mesa++;
            cout << "Camarero ha sentado al filosofo " << status.MPI_SOURCE << " en la mesa." << endl << flush;
            cout << "Hay actualmente " << mesa << " filosofos en la mesa." << endl << flush;
        }
        else{  // Si el mensaje que ha recibido es de levantarse.
            MPI_Recv(NULL,0,MPI_INT,status.MPI_SOURCE,tagLevantarse,MPI_COMM_WORLD,&status);
            mesa--;
            cout << "Camarero le da permiso al filosofo " << status.MPI_SOURCE << " y se levanta de la mesa." << endl << flush;
            cout << "Hay actualmente " << mesa << " filosofos en la mesa." << endl << flush;
        }
    }
}
// ---------------------------------------------------------------------
