#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"

  sem_t tabaco;
  sem_t papel;
  sem_t cerillas;
  sem_t estanquero;
  pthread_t ntabaco;
  pthread_t ncerillas;
  pthread_t npapel;
  pthread_t estanco;

// ----------------------------------------------------------------------------
// función que simula la acción de fumar  como un retardo aleatorio de la hebra

void fumar() 
{ 
   //  inicializa la semilla aleatoria  (solo la primera vez)
   static bool primera_vez = true ;
   if ( primera_vez )
   {   primera_vez = false ;
      srand( time(NULL) );    
   }
   
   // calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
   const unsigned miliseg = 100U + (rand() % 1900U) ; 

   // retraso bloqueado durante 'miliseg' milisegundos
   usleep( 1000U*miliseg ); 
}
// ----------------------------------------------------------------------------

void* festanco(void*){
  while(true){
  sem_wait(&estanquero);
  int opcion=rand()%3;
  switch(opcion){
    case 1:
      sem_post(&papel);
      std::cout << "Se ha producido papel.\n";
      break;
    case 2:
      sem_post(&cerillas);
      std::cout << "Se han producido cerillas.\n";
      break;
    default:
      sem_post(&tabaco);
      std::cout << "Se ha producido tabaco.\n";
    }
  }
}

void* ftabaco(void*){
    while(true){
    sem_wait(&tabaco);
    std::cout << "Fumador 1: Ya tengo tabaco. A fumar.\n";
    fumar();
    std::cout << "Fumador 1: Me he quedado sin tabaco.\n";
    sem_post(&estanquero);
    }
}

void* fcerillas(void*){
    while(true){ 
    sem_wait(&cerillas);
    std::cout << "Fumador 2: Ya tengo cerillas. A fumar.\n";
    fumar();
    std::cout << "Fumador 2: Me he quedado sin cerillas.\n";
    sem_post(&estanquero);
    }
}

void* fpapel(void*){
  while(true){
    sem_wait(&papel);
    std::cout << "Fumador 3: Ya tengo papel. A fumar.\n";
    fumar();
    std::cout << "Fumador 3: Me he quedado sin papel.\n";
    sem_post(&estanquero);
  }
}
  

// ----------------------------------------------------------------------------

int main()
{
  sem_init(&estanquero,0,1);
  sem_init(&tabaco,0,0);
  sem_init(&cerillas,0,0);
  sem_init(&papel,0,0);
  pthread_create(&estanco,NULL,festanco,NULL);
  pthread_create(&ntabaco,NULL,ftabaco,NULL);
  pthread_create(&ncerillas,NULL,fcerillas,NULL);
  pthread_create(&npapel,NULL,fpapel,NULL);
  pthread_join(estanco,NULL);
  pthread_join(ntabaco,NULL);
  pthread_join(ncerillas,NULL);
  pthread_join(npapel,NULL);
  sem_destroy(&estanquero);
  sem_destroy(&cerillas);
  sem_destroy(&tabaco);
  sem_destroy(&papel);
   
  return 0 ;
}
