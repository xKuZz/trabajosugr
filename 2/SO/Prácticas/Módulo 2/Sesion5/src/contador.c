#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
static int contador[32]={0};
static void handler(int signum) {
 ++contador[signum];
 printf("La señal %d se ha recibido %d veces.",signum,contador[signum]);
}
int main(){

 int i=0;
 struct sigaction sa;
  sa.sa_handler=handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

 for (; i<32; ++i){
  
  if (sigaction(i, &sa, NULL) == -1) 
    printf("No puedo manejar la señal %d", i);
 }
 printf("Esperando el envío de señales....\n");
 while(1);
}

 
