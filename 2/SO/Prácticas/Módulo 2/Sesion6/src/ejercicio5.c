#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  struct stat st;
  char*  map_out;
  char*  map_in;
  int    fd_out;
  int    fd_in;

  if (argc != 3) {
    printf("Número de argumentos inválido.\n");
    exit(-1);
  }

  if ( (fd_in = open(argv[1], O_RDONLY)) < 0) {
    printf("Error al abrir archivo a copiar.\n");
    exit(-1);
  }

  if (fstat(fd_in,&st) < 0) {
    printf("Error en stat.\n");
    exit(-1);
  }
  
  map_in = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd_in, 0);
  if (map_in == MAP_FAILED) {
    printf("Error en el mapeo de entrada.\n");
    exit(-1);
  }

  umask(0);
	fd_out = open(argv[2], O_RDWR| O_CREAT| O_TRUNC, S_IRWXU);
  ftruncate(fd_out, st.st_size);
 
  map_out = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd_out, 0);
  if (map_out == MAP_FAILED) {
    printf("Error en el mapeo de saida %s.\n",strerror(errno));
    exit(-1);
  }
  memcpy(map_out,map_in,st.st_size);
  return 0;
}
