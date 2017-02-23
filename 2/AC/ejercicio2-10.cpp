#include <chrono>
#include <iostream>
#include <omp.h>
using namespace std;

#define PRINT_MATRIX
int main(int argc, char** argv) {
  double t_antes, t_despues;

  if (argc != 2) {
    cerr << "ERROR: Incluir N como unico argumento.";
    return -1;
  }

  int N = atoi(argv[1]);
  // Reserva de memoria dinámica
  double** M = new double*[N];
  double* v1 = new double [N];
  double* v2 = new double [N];
  double suma = 0;

  for (int i = 0; i < N; ++i)
    M[i] = new double [N];

  #pragma omp parallel
  {
  // Inicialización de variables
  #pragma omp for
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      M[i][j] = (N + i) * 0.1 + (N-j) * 0.1;

  #pragma omp for
  for (int i = 0; i < N; ++i)
    v1[i] = i+1, v2[i] = 0;

  t_antes = omp_get_wtime();

  // Multiplicación de matriz por vector
}
  for (int i = 0; i < N; ++i) {
    suma = 0;
    #pragma omp parallel for reduction (+: suma)
    for (int j = 0; j < N; ++j)
      suma += M[i][j] * v1[j];
    v2[i] = suma;
  }

  t_despues = omp_get_wtime();


  #ifdef PRINT_MATRIX
    for (int i = 0; i < N; ++i)
      cout << v2[i] << endl;
  #endif

  cout << "Tiempo: "  << t_despues - t_antes << endl;
  // Liberación de memoria dinámica
  for (int i = 0; i < N; ++i)
    delete[] M[i];

  delete[] v1;
  delete[] v2;
  delete[] M;

}
