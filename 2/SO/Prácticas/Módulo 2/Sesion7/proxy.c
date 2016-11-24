#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define tamano 1024
#define longnombre 50


int main(int argv, char* argc[]) {

  struct flock cerrojo;
  FILE* tmp=tmpfile();
  char buffer[tamano];
  int bytes;
  int fd;

  while ( (bytes = read (STDIN_FILENO, buffer, tamano)) == tamano) {
    printf ("[PROXY-TMP]: Leyendo a archivo %d bytes.\n", bytes);
    if (fwrite(buffer,1,bytes,tmp) == -1) {
      printf("Error en fwrite.\n");
      exit(-1);
    }
    else
      printf ("[PROXY-TMP]: Escritos %d bytes.\n", bytes);
  }
  
  if (bytes > 0) {
    printf ("[PROXY-FIFO]: Leyendo %d bytes.\n", bytes);
    if ((bytes = fwrite(buffer,1,bytes,tmp)) == -1 ) {
      printf("Error en fwrite.\n");
      exit(-1);
    }
    else
      printf ("[PROXY-TMP]: Escritos %d bytes.\n", bytes);
  }

  cerrojo.l_type   = F_WRLCK;
  cerrojo.l_whence = SEEK_SET;
  cerrojo.l_start  = 0;
  cerrojo.l_len    = 0;

  fd = open("bloqueo", O_RDWR );
  if (fcntl(fd,F_SETLKW,&cerrojo) == -1) {
    printf ("[PROXY-LOCK] Error al bloquear el cerrojo.\n");
    exit(-1);
  }
  
  printf("[PROXY-LOCK] Exclusión mutua garantizada.\n");
  fseek(tmp,0,SEEK_SET);
  printf("[TMP] Inicio impresión.\n");
  while ( (bytes = fread(buffer,sizeof(char),tamano,tmp)) > 0) {
    write(STDOUT_FILENO,&buffer,bytes);
  }

  printf(".\n[TMP] Fin impresión.\n");

  cerrojo.l_type = F_UNLCK;
  if (fcntl(fd,F_SETLKW,&cerrojo) == -1) {
    printf ("[PROXY-LOCK] Error al desbloquear el cerrojo.\n");
    exit(-1);
  }

  printf("[PROXY-LOCK] Fin exclusión mutua.\n");
  return 0;
}
    
