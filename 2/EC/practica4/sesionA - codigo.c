// gcc -o bomba bomba.c -m32 -O0

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char password[]="contaPlz\n";
int  passcode  = 1000;

void function_b(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void function_a(){
	printf("·························\n");
	printf("··· bomba desactivada ···\n");
	printf("·························\n");
	exit(0);
}

int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
  int  i;
	int  tam;
#define TLIM 15
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);
	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);

  // Para que no sea demasiado fácil modifico dos de las letras del string

	--pass[0];
	--pass[4];
		
	if (strncmp(pass,password,strlen(password)))
	    function_b();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    function_b();

	printf("Introduce el código: ");
	scanf("%i",&pasv);
// Para que no sea excesivamente fácil realizo algunas operaciones aritméticas básicas
	pasv >>= 1;
  pasv  -= 8;
	if (pasv!=passcode) function_b();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    function_b();

	function_a();
}
