#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
 #include <omp.h>
#else
 #define omp_get_thread_num() 0
#endif
main(int argc, char **argv) {
 int i, n=20, a[n],sumatotal=0, sumalocal=0;
 if(argc < 2) {
 fprintf(stderr,"Falta iteraciones\n");
 exit(-1);
 }
 n = atoi(argv[1]); if (n>20) {n=20; printf("n=%d\n",n);}
 for (i=0; i<n; i++) a[i] = i;
 #pragma omp parallel firstprivate(sumalocal)
 {
   #pragma omp for
   for (i=0; i<n; i++) sumalocal += a[i];

   #pragma omp atomic
     sumatotal +=sumalocal;
 }
   printf("Tras 'parallel' suma=%d\n",sumatotal);
}
