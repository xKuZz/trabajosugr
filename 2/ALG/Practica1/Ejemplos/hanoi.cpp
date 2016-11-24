/**
   @file Resoluci�n del problema de las Torres de Hanoi
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;




/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: n�mero de discos. M > 1.
   @param i: n�mero de columna en que est�n los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: n�mero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funci�n imprime en la salida est�ndar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricci�n de que ning�n
   disco se puede situar sobre otro de tama�o menor. Utiliza
   una �nica columna auxiliar.
*/
void hanoi (int M, int i, int j);




void hanoi (int M, int i, int j)
{
  if (M > 0)
    {
      hanoi(M-1, i, 6-i-j);
      //cout << i << " -> " << j << endl;
      hanoi (M-1, 6-i-j, j);
  }
}

int main(int argc, char * argv[])
{
  
    if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_discos>" << endl;
      return -1;
    }

  int M = atoi(argv[1]);
  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido;

  /*clock_t tantes;
  clock_t tdespues;
  double tiempo_transcurrido;
  const int NUM_VECES=10000;
  int i;
  
  tantes = clock();
  for(i=0; i<NUM_VECES; i++){
  cout << "Antes de ejecutar." << endl;*/
  
  tantes = high_resolution_clock::now();
  hanoi(M, 1, 2);
  tdespues = high_resolution_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);
  cout << transcurrido.count() << endl;
  

  
  /*tdespues = clock();
  tiempo_transcurrido=((double)(tdespues-tantes)/(CLOCKS_PER_SEC*(double)NUM_VECES));


  cout << tiempo_transcurrido << endl;*/

  return 0;
}
