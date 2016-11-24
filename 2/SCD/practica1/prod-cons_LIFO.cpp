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
int utilizados;
sem_t puede_leer, puede_escribir;

unsigned producir_dato()
{
  static int contador = 0 ;
  cout << "producido: " << contador << endl << flush ;
  return contador++ ;
}
// ---------------------------------------------------------------------

void consumir_dato( int dato )
{
    cout << "dato recibido: " << dato << endl ;
}
// ---------------------------------------------------------------------

void * productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {

    if (utilizados<tam_vector){
        sem_wait(&puede_escribir);
        int dato = producir_dato();
        v[utilizados++]=dato;
        sem_post(&puede_leer);
    }
    else {
        i--;
    }

  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato;
    if (utilizados>0){
        sem_wait(&puede_leer);
        dato=v[--utilizados];
        consumir_dato( dato ) ;
        sem_post(&puede_escribir);
    }
    else{
        i--;
    }

  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  pthread_t escribe, usa;

  sem_init(&puede_leer,0,0);
  sem_init(&puede_escribir,0,tam_vector);
  pthread_create(&escribe,NULL, productor, NULL);
  pthread_create(&usa,NULL,consumidor, NULL);
  pthread_join(escribe,NULL);
  pthread_join(usa,NULL);
  sem_destroy(&puede_leer);
  sem_destroy(&puede_escribir);

  return 0;
}
