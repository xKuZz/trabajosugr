#include <chrono>
#include <iostream>
using namespace std;

#define PRINT_MATRIX
int main(int argc, char** argv) {
  chrono::high_resolution_clock::time_point t_antes, t_despues;
  chrono::duration<double> tiempo;

  if (argc != 2) {
    cerr << "ERROR: Incluir N como unico argumento.";
    return -1;
  }

  int N = atoi(argv[1]);
  // Reserva de memoria dinámica
  double** M = new double*[N];
  double* v1 = new double [N];
  double* v2 = new double [N];

  for (int i = 0; i < N; ++i)
    M[i] = new double [N];


  // Inicialización de variables
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      M[i][j] = (N + i) * 0.1 + (N-j) * 0.1;

  for (int i = 0; i < N; ++i)
    v1[i] = i+1, v2[i] = 0;

  t_antes = chrono::high_resolution_clock::now();
  // Multiplicación de matriz por vector
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      v2[i] += M[i][j] * v1[j];

  t_despues = chrono::high_resolution_clock::now();
  #ifdef PRINT_MATRIX
  for (int i = 0; i < N; ++i)
    cout << v2[i] << endl;
  #endif

  tiempo = chrono::duration_cast<chrono::duration<double>>(t_despues - t_antes);

  cout << "Tiempo: "  << tiempo.count() << endl;
  // Liberación de memoria dinámica
  for (int i = 0; i < N; ++i)
    delete[] M[i];

  delete[] v1;
  delete[] v2;
  delete[] M;

}
