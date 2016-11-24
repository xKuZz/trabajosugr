#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int numero;
	int pid;
	if (argc!=2){
		printf("Debe poner un argumento.\n");
		perror("Número de argumentos invalido.");
		exit(EXIT_FAILURE);
	}

	numero=strtol(argv[1],NULL,10);
	pid=fork();

	if (pid>0){ /* Proceso padre */
		if (numero%4==0)
			printf("El número %d es divisible por 4.\n", numero);
		else
			printf("El número %d no es divisible por 4.\n", numero);
	}

	else if (pid==0){ /* Proceso hijo */
		if (numero%2==0)
			printf("El número %d es par.\n", numero);
		else
			printf("El número %d es impar.\n", numero);
	}

	else{ /* Error fork() */
		printf("Error al hacer fork.\n");
		perror("Error al hacer fork.");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
