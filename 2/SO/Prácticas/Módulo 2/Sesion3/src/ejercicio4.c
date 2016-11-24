#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int childpid=0;
	int waitpid;
	int numhijos=5;
  int hijosrestantes=5;
	int i;

 for (i=0; i < numhijos; ++i) {
	if ((childpid= fork()) == -1) {
		fprintf(stderr, "No he podido crear un hijo %d: %s\n",i,strerror(errno));
		exit(-1);
	}
	if (!childpid)
		break;
	}

	if (childpid==0){
		printf("Soy el hijo %d.\n", getpid());	
	}
	else if (childpid>0) {
		while (hijosrestantes!=0){
			waitpid=wait(NULL);
			printf("Acaba de finalizar mi hijo con PID %d.\n", waitpid);
			printf("Sólo me quedan %d por finalizar.\n", hijosrestantes);
			--hijosrestantes;
		}
	}
	else
		printf("Error al crear nuevo proceso.\n");
}
	

	
