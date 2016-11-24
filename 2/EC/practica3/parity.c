#define TEST 0
#define COPY_PASTE_CALC 0
#include <stdio.h>    // para printf()
#include <stdlib.h>   // para exit()
#include <sys/time.h> // para gettimeofday(), struct timeval


#if ! TEST
#define NBITS 20
#define SIZE (1<<NBITS) // tamaño suficiente para tiempo apreciable
    unsigned lista[SIZE]; // unsigned-> desplazamiento a derecha lógico (mete 0)
#define RESULT (1<<NBITS-1) //nueva fórmula
#else
/* --------------------------------------------------------------------------*/
    #define SIZE 4
    unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001}; 

    #define RESULT 4
/* --------------------------------------------------------------------------* /
    #define SIZE 8
    unsigned lista[SIZE]={0x7FFFFFFF, 0xFFEFFFFF, 0xFFFFF7FF, 0xFFFFFFFE,
                          0x10000024, 0x00356700, 0x8900AC00, 0x00BD00EF};

    #define RESULT 8

/* --------------------------------------------------------------------------* /
    #define SIZE 8
    unsigned lista[SIZE]={0x00000000, 0x10204080, 0x3590AC06, 0x70B0D0E0,
                          0xFFFFFFFF, 0x12345678, 0x9ABCDEF0, 0xCAFEBEEF}; 
    #define RESULT 2

/* --------------------------------------------------------------------------*/
#endif
int resultado=0;

int parity1(unsigned* array, int len)
{
    int i, res=0;
        int j, val;
        unsigned x;

    for (i=0; i<len; i++) {                         // Recorremos el array
            x=array[i];
            val=0;
             for (j=0; j<8*sizeof(unsigned); j++){  // Para cada ejemplar
                val ^= x & 0x1;                     // Aplico xor-máscara
                x >>= 1;                            // Desplazo hacia la derecha
            }
            res += val;                               
        }
    return res;
}

int parity2(unsigned  *array, int len)
{
    int i, val, res=0;
        unsigned x;
    for (i=0; i<len; i++) {                 // Recorremos el array
            x=array[i];
            val=0;
             do {                           // Para cada ejmplar
                val ^= x & 0x1;             // Aplico xor-máscara
                x >>= 1;                    // Desplazo hacia la derecha
            } while (x);                    // Mientras me queden unos
            res +=val;
        }
    return res;
}

int parity3(unsigned *array, int len){
    int i, val, res=0;
        unsigned x;
    for (i=0; i<len; i++) {                 // Recorremos el array
            x=array[i];
            val=0;
             do {                           // Para cada ejemplar
                val ^= x;                   // Aplico xor
                x >>= 1;                    // Desplazo hacia la dercha
            } while (x);                    // Mientras me queden unos.

            res += val & 0x1;               // Aplico máscara
        }
    return res;
}

int parity4(unsigned *array, int len){
    int i, val, res=0;
        unsigned x;
    for (i=0; i<len; i++) {                      // Recorremos el array
            x=array[i];
            val=0;
            asm("\n"                             // Para cada elemento
            "ini4:                 \n\t"               
            "     xor %[x], %[v]   \n\t"         // Aplico xor
            "     shr %[x]         \n\t"         // Desplazo hacia la derecha
            "     jne ini4         \n\t"         // Mientras me queden unos

            : [v]       "+r"      (val)          // E/S : paridad ejemplar
            : [x]        "r"        (x)          // entrada: ejemplar
            );
            res += val & 0x1;
        }
    return res;
}

int parity5(unsigned *array, int len){
        int i, j, val, result=0;
        unsigned x;
    for (i=0; i<len; i++) {                      // Recorremos el array
            x=array[i];                                                                
                                                 // Para cada ejemplar:
             for (j = 16; j >0; j/=2)            // Recorremos en árbol   
                x ^= x>>j;                       // Aplicamos xor-desplz

            result += x & 0x01;                  // Aplicamos máscara
        }
            
        return result;
}

int parity6(unsigned *array, int len){
int i, j, val, result=0;
        unsigned x;
    for (i=0; i<len; i++) {                       // Recorremos array
            x=array[i];

             asm(                                 // Para cada ejemplar
                "mov         %[x], %%edx     \n\t"       // Lo copiamos al registro

                "shr           $8, %%edx     \n\t"       // Despl lógico derecha (j=16)
                "xor        %%edx, %[x]      \n\t"              // x ^= %edx
                "setnp        %%dl           \n\t"       // Activamos si paridad impar

                "shr           $8, %%edx     \n\t"             
                "xor        %%edx, %[x]      \n\t"
                "setnp        %%dl           \n\t"
                
                "shr           $8, %%edx     \n\t"             
                "xor        %%edx, %[x]      \n\t"
                "setnp        %%dl           \n\t"
                
                "shr           $8, %%edx     \n\t"             
                "xor        %%edx, %[x]      \n\t"
                "setnp        %%dl           \n\t"

                "movzx       %%dl, %[x]      \n\t"  // Movemos con extensión 0

                : [x]           "+r"          (x)   // E/S: ejemplar                            
                :
                :               "edx"               // clobber                      
            );
            result += x;
        }
        return result;
}


void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;                        // gettimeofday() secs-usecs
    long           tv_usecs;                       // y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);

#if COPY_PASTE_CALC
    printf (   "%ld" "\n",      tv_usecs);
#else
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
#endif
}

int main()
{
#if ! TEST
    int i;                                         // inicializar array
    for (i=0; i<SIZE; i++)                         // se queda en cache
           lista[i]=i;
#endif

    crono(parity1, "parity1 (lenguaje C -               for)");
    crono(parity2, "parity2 (lenguaje C -             while)");
    crono(parity3, "parity3 (1.CS:APP 3.22 -     mask final)");
    crono(parity4, "parity4 (lenguaje ASM -    cuerpo while)");
    crono(parity5, "parity5 (1.CS:APP 3.49 -      32b 16 1b)");
    crono(parity6, "parity6 (lenguaje ASM-cuerpo for- setnp)");
#if ! COPY_PASTE_CALC
    printf("calculado = %d\n", RESULT);
#endif
       

    exit(0);
}
