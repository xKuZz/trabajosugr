#define TEST 1
#define COPY_PASTE_CALC 0
#include <stdio.h>    // para printf()
#include <stdlib.h>    // para exit()
#include <sys/time.h>    // para gettimeofday(), struct timeval


#if ! TEST
#define NBITS 20
#define SIZE (1<<NBITS) // tamaño suficiente para tiempo apreciable
    unsigned lista[SIZE]; // unsigned-> desplazamiento a derecha lógico (mete 0)
#define RESULT (NBITS*(1<<NBITS-1)) //nueva fórmula
#else
/* --------------------------------------------------------------------------*/ 
    #define SIZE 4
    unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001}; 

    #define RESULT 4
/* --------------------------------------------------------------------------* /
    #define SIZE 8
    unsigned lista[SIZE]={0x7FFFFFFF, 0xFFEFFFFF, 0xFFFFF7FF, 0xFFFFFFFE,
                          0x10000024, 0x00356700, 0x8900AC00, 0x00BD00EF};

    #define RESULT 156

/* --------------------------------------------------------------------------* /
    #define SIZE 8
    unsigned lista[SIZE]={0x00000000, 0x10204080, 0x3590AC06, 0x70B0D0E0,
                          0xFFFFFFFF, 0x12345678, 0x9ABCDEF0, 0xCAFEBEEF}; 
    #define RESULT 116

/* --------------------------------------------------------------------------*/
#endif


int resultado=0;

int popcount1(unsigned* array, int len)
{
    int i, result=0;
        int j;
        unsigned x;
    for (i=0; i<len; i++) {                      // Recorremos el array
            x=array[i];
             for (j=0; j<8*sizeof(unsigned); j++){       // Para cada bit de un ejemplar
                result += x & 0x1;                       // añadimos si 1
                x >>= 1;                                 // pasamos al siguiente
            }
        }
    return result;
}

int popcount2(unsigned  *array, int len)
{
    int i, result=0;
        unsigned x;
    for (i=0; i<len; i++) {                      // Recorremos el array
            x=array[i];                          // Para cada bit de un ejemplar
             do {
                result+= x & 0x1;                // añadimos si 1
                x >>= 1;                         // pasamos al siguiente
            } while (x);                         // mientras queden unos
        }
    return result;
}

int popcount3(unsigned *array, int len){
    int i, result=0;
    unsigned x;
    for (i=0; i<len; i++) {
      x=array[i];
             asm("\n"
            "ini3:                   \n\t"       // Inicio bucle
            "   shr          %[x]    \n\t"       // Despl lógico derecha -> CF
            "   adc      $0, %[r]    \n\t"       // r= r+0+CF
            "   test   %[x], %[x]    \n\t"       // Si x!=0
            "   jne        ini3      \n\t"       // Salto a inicio bucle

            : [r]        "+r"     (result)       // E/S resultado
            : [x]         "r"          (x)       // Entrada ejemplar 
            : "edx"
            );
        }
    return result;
}

int popcount4(unsigned *array, int len){         
        int i, j, val, result=0;
        unsigned x;
    for (i=0; i<len; i++) {                      // Recorremos el array 
            x=array[i];
            val=0;
             for (j = 0; j < 8; j++) {               // Para cada bit del ejemplar
                val += x & 0x01010101;               // Acumulamos con la máscara
                x >>= 1;                             // Pasamos al siguiente
            }
            val += (val >> 16);                      // Sumamos las agrupaciones
            val += (val >> 8);                       // de 8 bits
            result += val & 0xFF;                    // Aplicamos la otra máscara
        }
            
        return result; 
}

int popcount5(unsigned *array, int len){
    int i, val, result=0;
    int SSE_mask[] = {0x0f0f0f0f, 0x00f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f};
    int SSE_LUTb[] = {0x02010100, 0x003020201, 0x03020201, 0x04030302};
    if (len & 0x3) printf("leyendo 128b pero len no múltiplo de 4?\n");
    for (i=0; i<len; i+=4){
        asm("\n"
"      movdqu       %[x], %%xmm0      \n\t"      // Hago 2 copias del ejemplar
"      movdqa     %%xmm0, %%xmm1      \n\t"
"      movdqu       %[m], %%xmm6      \n\t"      // Máscara
"      psrlw          $4, %%xmm1      \n\t"

"      pand       %%xmm6, %%xmm0      \n\t"      // xmm0 a nibbles inferiores
"      pand       %%xmm6, %%xmm1      \n\t"      // xmm1 a nibbles superiores
"      movdqu       %[l], %%xmm2      \n\t"      // Hacemos dos copias de LUT
"      movdqa     %%xmm2, %%xmm3      \n\t"
"      pshufb     %%xmm0, %%xmm2      \n\t"             // popcount inferiores
"      pshufb     %%xmm1, %%xmm3      \n\t"      // popcount superiores

"      paddb      %%xmm2, %%xmm3      \n\t"      // vector popcount bytes
"      pxor       %%xmm0, %%xmm0      \n\t"             // xmm0 a 0
"      psadbw     %%xmm0, %%xmm3      \n\t"             // xmm3 popcount[B:0..7 |8..15] 
"      movhlps    %%xmm3, %%xmm0      \n\t"      // xmm0 [ 0 | popcount B: 0..7]
"      paddd      %%xmm3, %%xmm0      \n\t"             // xmm0 [sin usar | pcnt 0..15]
"      movd       %%xmm0, %[val]      \n\t"      // Devolvemos

           :     [val]        "=m"               (val)      // Salida: popcount de ejemplar
           :     [x]           "m"          (array[i]),     // Lectura: ejemplar
                 [m]           "m"       (SSE_mask[0]),     // Lecturas: máscaras
                 [l]           "m"       (SSE_LUTb[0])
        );

        result +=val;
        }

    return result;
}
void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;                      // gettimeofday() secs-usecs
    long           tv_usecs;                     // y sus cuentas

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

    crono(popcount1, "popcount1 (lenguaje C -         for)");
    crono(popcount2, "popcount2 (lenguaje C -       while)");
    crono(popcount3, "popcount3 (leng.ASM -  cuerpo while)");
    crono(popcount4, "popcount4 (1.CS:APP 3.49 - group 8b)");
    crono(popcount5, "popcount5 (asmSSE3  -   pshufb 128b)");

#if ! COPY_PASTE_CALC
    printf("calculado = %d\n", RESULT);
#endif
       

    exit(0);
}
