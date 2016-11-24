#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Descomentar para que solo aparezca el tiempo que tarda
//#define ONLYPRINTTIME
// Descomentar para hacer divide y vencerás, comentar para clasico
#define DYV


//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void burbuja(vector<int>&v) {
  int n = v.size() - 1;

  for (int i = 0; i < n ; ++i)
    for (int j = n; j > i; --j)
      if    (v[j] < v[j-1])
        swap(v[j] , v[j-1]);
}

vector<int> clasico(const vector<vector<int>>& datos) {
  vector<int> salida;
  int k = datos.size();
  int n = (k > 0) ? datos[0].size() : 0;

  // Llenamos el vector
  salida.reserve(n*k);
  for (auto& v : datos)
    for (auto d: v)
      salida.push_back(d);

  // Ordenamos (Burbuja)
  burbuja(salida);

  return  salida;
}


void insercion(vector<int>& v, int inicio, int fin) {
  for (int i = inicio + 1; i < fin; ++i)
    for (int j = i; v[j] < v[j-1] && j > 0; --j)
      swap(v[j], v[j-1]);
}
void juntar(vector<int>& v, int inicio, int fin, const vector<int>& aux_1,
                                                 const vector<int>& aux_2) {
    for (int i = inicio, j = 0, k = 0; i < fin; ++i)
      if (aux_1[j] < aux_2[k]) {
        v[i] = aux_1[j];
        j++;
      }
      else {
        v[i] = aux_2[k];
        k++;
      }
}
void mergesort(vector<int>& v, int inicio, int fin, int umbral) {
   if (fin - inicio < umbral)
     insercion(v,inicio, fin);
   else {
     int mitad = (fin - inicio)/2;
     vector<int> aux_1;
     vector<int> aux_2;
     aux_1.reserve(mitad - inicio + 1);
     aux_2.reserve(fin - mitad  + 1);
     for (int l = 0, l2 = inicio; l < mitad; ++l, ++l2)
       aux_1.push_back(v[l2]);
     aux_1[mitad] = INT_MAX;

     for (int l = 0, l2 = mitad; l < fin - mitad; ++l, ++l2)
       aux_2.push_back(v[l2]);
     aux_2[fin-mitad] = INT_MAX;

     mergesort(aux_1, 0, mitad, umbral);
     mergesort(aux_2, 0, fin - mitad, umbral);
     juntar(v, inicio, fin, aux_1, aux_2);

   }
}


/** @brief Mezcla con ordenamiento mergesort **/
vector<int> dyv(const vector<vector<int>>& datos) {
  vector<int> salida;
  int k = datos.size();
  int n = (k > 0) ? datos[0].size() : 0;

  // Llenamos el vector
  salida.reserve(n*k);
  for (auto& v : datos)
    for (auto d: v)
      salida.push_back(d);

  // Ordenamos(mergesort)
  mergesort(salida,0,salida.size(),100);
  return salida;
}



int main(int argc, char * argv[])
{
  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);
  int N=k*n;
  vector<vector<int>> T(k, vector<int>(n));
  vector<int> aux(N);
  vector<int> salida(N);


  srand(time(0));
  //genero todos los enteros entre 0 y k*n-1
  for (int j=0; j<N; j++) aux[j]=j;

  //para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
  for (int i=0; i<k; i++) {
    int t=0;
    int m=0;
    while (m<n) {
      double u=uniforme();
      if ((N-t)*u >= (n-m)) t++;
      else {
        T[i][m]=aux[t];
        t++;
        m++;
      }
    }
  }
  #ifndef ONLYPRINTTIME
    for (int i=0; i<k; i++) {
      for (int j=0; j<n; j++)
        cout << T[i][j] << " ";
      cout << " " << endl;
    }
  #endif
/*---- FIN GENERADOR ----*/

  high_resolution_clock::time_point t_antes, t_despues;
  duration<double> tiempo;

  t_antes = high_resolution_clock::now();
  #ifdef DYV
    salida = dyv(T);
  #else
    salida = clasico(T);
  #endif

  t_despues = high_resolution_clock::now();
  tiempo = duration_cast<duration<double>>(t_despues - t_antes);
  cout << n << '\t' << tiempo.count() << endl; // Salida tiempo

#ifndef ONLYPRINTTIME
cout << endl << endl;
 for (auto d: salida)
     cout << d << " ";
 cout << endl;
#endif

}
