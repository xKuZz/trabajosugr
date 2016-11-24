#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define tamano 1024
#define longnombre 50
#define IN    0
#define OUT   1
#define PROXY 2

static void mimanejador (int signal) {
  wait(NULL);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Número de argumentos inválidos.\n");
    exit(-1);
  }
  struct sigaction sa;
  char fifo_proxy[longnombre];
  char fifo_out[longnombre];
  char fifo_in[longnombre];
  char buffer[tamano];
  int  fifo[3];
  int  bytes;
  int  pid;
  umask(0);
  
  sa.sa_handler = mimanejador;
  sigaction(SIGCHLD,&sa,NULL);

  // Creación y apertura de FIFO
  sprintf(fifo_in ,"%se",argv[1]);
  sprintf(fifo_out,"%ss",argv[1]);
  unlink(fifo_in);
  unlink(fifo_out);
  unlink("./bloqueo");

  if (mkfifo(fifo_in,0777) == -1 || mkfifo(fifo_out,0777) == -1) {
    printf("Error en mkfifo.\n");
    exit(-1);
  }

  fifo[IN]  = open(fifo_in , O_RDWR);
  fifo[OUT] = open(fifo_out, O_RDWR);
  creat("bloqueo",0777);

  // Iniciamos la lectura
  printf("[IN<-Cliente]: Intentando leer petición.\n");
  if ((bytes = read(fifo[IN], buffer, tamano)) == -1){
        printf("Error en read.\n");
        exit(-1);
  }

  while (bytes>0) 
    if ((pid = fork()) == 0) { // Hijo: Llama a proxy
      sprintf(fifo_proxy,"fifo.%d",getpid());
      if (mkfifo(fifo_proxy,0777) == -1){
        printf("[MKFIFO-ERROR] Error al crear %s.\n", fifo_proxy);
        exit(-1);
      }

      int aux = getpid();

      if (write(fifo[OUT],&aux,sizeof(int)) == -1){
        printf("Error en write.\n");
        exit(-1);
      }
      printf("[OUT->Cliente]: Comunicando PID %d.\n",aux);
      
      fifo[PROXY] = open(fifo_proxy, O_RDWR);
      dup2(fifo[PROXY], STDIN_FILENO);
      printf("[PROXY-EXEC] Iniciando proxy para PID: %d.\n", getpid());
      execl("./proxy","./proxy",NULL);
        printf("[EXEC-ERROR] No se ha podido llamar a proxy.\n"
               "[EXEC-ERROR] PID: %d.\n", getpid());
    }
    else if (pid > 0) { // Padre
      bytes = read(fifo[IN], buffer, tamano);
      printf("[IN<-Cliente]: Intentando leer petición.\n");
    }
    else {
      printf("Fallo en fork.\n");
      exit(-1);
    }


  return 0;
  
}
