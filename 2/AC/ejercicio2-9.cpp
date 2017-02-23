#include <iostream>
using namespace std;

//#define PRINT_MATRIX
int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "ERROR: Incluir N como unico argumento.";
    return -1;
  }

  int N = atoi(argv[1]);
  // Reserva de memoria dinámica
  double** M1 = new double*[N];
  double** M2 = new double*[N];
  double*  v  = new double [N];

  for (int i = 0; i < N; ++i) {
    M1[i] = new double[N];
    M2[i] = new double[N];
  }
  double t_antes, t_despues;
  #pragma omp parallel
  {

    // Inicialización de variables
    #pragma omp for
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) {
        M1[i][j] = (N + i) * 0.1 + (N-j) * 0.1;
        M2[i][j] = 0;
      }

    #pragma omp for
    for (int i = 0; i < N; ++i)
      v[i] = i+1;

    #pragma omp single
      t_antes = omp_get_wtime();

    // Multiplicación de matriz por vector
      #pragma omp for
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
          for (int k = 0; k < N; ++k)

      #pragma omp single
        t_despues = omp_get_wtime();
  }
  #ifdef PRINT_MATRIX
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
        cout << M2[i][j] << '\t';
    cout << endl;
  }
  #endif

  // Liberación de memoria dinámica
  for (int i = 0; i < N; ++i) {
    delete[] M1[i];
    delete[] M2[i];
  }
  delete[] M1;

}
