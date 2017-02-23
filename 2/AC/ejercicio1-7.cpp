#include <cstdlib>
#include <iostream>
#include <omp.h>

using namespace std;


int main(int argv, char** argc) {

  if (argv != 2)
      cout << "Error: Introducir como argumento tamaño de entrada" << endl;
  else {
    unsigned N = atoi(argc[1]);

    double* v1 = new double[N];
    double* v2 = new double[N];
    double* v3 = new double[N];

    double t_antes, t_despues;

    #pragma omp parallel
    {

      #pragma omp for
      for (unsigned i=0; i < N; ++i) {
        v1[i] = (N + i) * 0.1;
        v2[i] = (N - i) * 0.1;
      }

      #pragma omp single
        t_antes   = omp_get_wtime();

      #pragma omp for
      for (unsigned i=0; i < N; ++i)
        v3[i] = v2[i] + v1[i];


      #pragma omp single
      {
         t_despues = omp_get_wtime();
         cout << "v1\t" << v1[0] << " | " << v1[N-1] << endl
              << "v2\t" << v2[0] << " | " << v2[N-1] << endl
              << "v3\t" << v3[0] << " | " << v3[N-1] << endl
              << "Tiempo:\t" << t_despues - t_antes;
         delete[] v1;
         delete[] v2;
         delete[] v3;
      } // fin single
    } // fin parallel
  } // fin else (argc)
}
