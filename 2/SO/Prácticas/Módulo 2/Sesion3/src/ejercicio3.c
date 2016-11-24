#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define JERARQUIA1 0 // 1 Para Jeraquia 1, 0 para JERARQUIA 2
#define nprocs 21


int main(int argc, char *argv[]){
int childpid;
int i;
#if JERARQUIA1
/*
Jerarquía de procesos tipo 1
*/
	for (i=1; i < nprocs; i++) {
	if ((childpid= fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
		}


	if (childpid)
		break;

	printf("PID: %d PPID: %d\n", getpid(),getppid());
	}

#else
/*
Jerarquía de procesos tipo 2
*/
for (i=1; i < nprocs; i++) {
if ((childpid= fork()) == -1) {
fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
exit(-1);
}
if (!childpid)
break;
}
printf("PID: %d PPID: %d\n", getpid(),getppid());
#endif
}
