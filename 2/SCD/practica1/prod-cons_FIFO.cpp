#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

using namespace std ;

// ---------------------------------------------------------------------
// constantes
const unsigned
  num_items  = 40 ,
  tam_vector = 10 ;

// ---------------------------------------------------------------------
int v[tam_vector];
int utilizados=0;
int primera_libre=0;
int primera_ocupada=0;
sem_t puede_leer, puede_escribir, io;

unsigned producir_dato()
{
  static int contador = 0 ;
  sem_wait(&io);
  cout << "producido: " << contador << endl << flush ;
  sem_post(&io);
  return contador++ ;
}
// ---------------------------------------------------------------------

void consumir_dato( int dato )
{
   sem_wait(&io);
    cout << "dato recibido: " << dato << endl ;
   sem_post(&io);
}
// ---------------------------------------------------------------------

void * productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    if (utilizados<tam_vector){
    sem_wait(&puede_escribir);
    int dato = producir_dato();
    v[primera_libre]=dato;
    utilizados++;
    if (++primera_libre==tam_vector)
      primera_libre=0;
    sem_post(&puede_leer);
    }
    else
      i--;

  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    if (utilizados>=0){
      sem_wait(&puede_leer);
      int dato=v[primera_ocupada];
      consumir_dato( dato );
      if (++primera_ocupada==tam_vector)
        primera_ocupada=0;
      utilizados--;
      sem_post(&puede_escribir);
    }
    else
      i--;
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  pthread_t escribe, usa;

  sem_init(&puede_leer,0,0);
  sem_init(&puede_escribir,0,tam_vector);
  sem_init(&io,0,1);
  pthread_create(&escribe,NULL, productor, NULL);
  pthread_create(&usa,NULL,consumidor, NULL);
  pthread_join(escribe,NULL);
  pthread_join(usa,NULL);
  sem_destroy(&puede_leer);
  sem_destroy(&puede_escribir);
  sem_destroy(&io);
   return 0 ;
}
