#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  struct flock cerrojo;
  int child1;
  int child2;
  int fd;

  // El archivo ejer3 se supone que ya existe y que contiene al menos 2 bytes.
  fd = open("ejer3", O_RDWR);

  cerrojo.l_whence = SEEK_SET;
	cerrojo.l_type   = F_WRLCK;
	cerrojo.l_start  = 0;
	cerrojo.l_len    = 2;

  if (fcntl(fd, F_SETLK,&cerrojo) == -1) 
        printf("Fallo inicial en cerrojo\n");

  if ( (child1 = fork()) > 0 ) // Padre
    if (  (child2 = fork()) > 0) {
      cerrojo.l_type = F_UNLCK;
      cerrojo.l_len  = 2;
            
      sleep(2);
      printf("Proceso padre desbloqueando cerrojos.\n");
      fcntl(fd, F_SETLKW, &cerrojo);
      waitpid(child1,NULL,0);
      waitpid(child2,NULL,0);

    }
    else { // Hijo 2
      cerrojo.l_len   = 1;
      cerrojo.l_start = 1;
      printf("Hijo 2 bloqueando segundo byte.\n");
      if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
        if (errno == EDEADLK)
          printf("El kernel ha evitado un interbloqueo.\n");
        
      sleep(1);
      cerrojo.l_start = 0;
      printf("Hijo 2 bloqueando primer byte.\n");
      if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
        if (errno == EDEADLK)
          printf("El kernel ha evitado un interbloqueo.\n");
      
    }
  else { // Hijo 1
    cerrojo.l_len = 1;
    printf("Hijo 1 bloqueando primer byte.\n");
    if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
      if (errno == EDEADLK)
        printf("El kernel ha evitado un interbloqueo.\n");

    sleep(1);
    cerrojo.l_start = 1;
    printf("Hijo 1 bloqueando segundo byte.\n");
    if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
      if (errno == EDEADLK)
          printf("El kernel ha evitado un interbloqueo.\n");
  }

  return 0; 
}
