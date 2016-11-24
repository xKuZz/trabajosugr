#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
   char buffer[80];
   char* aux;
   char* aux2;
   int fd_in;
   int fd_out;
   ssize_t rstatus=80;
   int bloque;
   ssize_t contador=0; /* Para modificación adicional, cuenta bytes para el tamaño del
                    buffer */

    /* Configuro fd_in como archivo o entrada estándar */
    if(argc==2){
      if((fd_in=open(argv[1],O_RDONLY))<0){
        printf("Error: %d, al abrir el archivo %s\n", errno, argv[1]);
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
      }
    }
    else {
      fd_in=STDIN_FILENO;
    }
    
    /* Creo o sobreescribo archivo de salida */
    if((fd_out=open("salida.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRUSR|S_IWUSR))<0){
      printf("Error %d, al crear archivo salida.txt.\n", errno);
      perror("Error al crear archivo de salida.\n");
      exit(EXIT_FAILURE);
    }

    /* Lectura/escritura a través de buffer */
    for (bloque=1; rstatus==80; ++bloque){
        rstatus=read(fd_in,buffer,80);
        if (rstatus<0){
          printf("Error: %d, al leer.\n", errno);
          perror("Error al leer.\n");
          exit(EXIT_FAILURE);
        }

        if (bloque==1){
          asprintf(&aux, "Bloque %d\n", bloque);
          }
        else {
          asprintf(&aux, "\nBloque %d\n", bloque);
        }

        if ((write(fd_out,aux,strlen(aux)))<0){
          printf("Error: %d, al escribir el número de bloque %d.\n",errno, bloque);
          perror("Error al escribir número de bloque.\n");
          exit(EXIT_FAILURE);
        }
        contador+=strlen(aux);
    

        if ((write(fd_out,buffer,rstatus))<0){
          printf("Error: %d, al escribir bloque número %d.\n",errno, bloque);
          perror("Error al escribir un bloque.\n");
          exit(EXIT_FAILURE);
        }
        contador+=rstatus;
      
    }
    /* Modificación adicional. Guardo el archivo en memoria dinámica
       y sobreescribo desde el principio */
        aux=(char*) realloc(aux,contador*sizeof(char));
        asprintf(&aux2, "El número de bloques es %d\n",bloque-1);
        if((lseek(fd_out,0,SEEK_SET))<0){
          printf("Error: %d, al reposicionar puntero.\n", errno);
          perror("Error de reposicionamiento de puntero\n");
          exit(EXIT_FAILURE);
        }
        if((read(fd_out,aux,contador))<0){
          printf("Error: %d, al releer el archivo.\n", errno);
          perror("Error de relectura de archivo\n");
          exit(EXIT_FAILURE);
        } 
        if((lseek(fd_out,0,SEEK_SET))<0){
          printf("Error: %d, al reposicionar puntero.\n", errno);
          perror("Error de reposicionamiento de puntero\n");
          exit(EXIT_FAILURE);
        }
        if(write(fd_out,aux2,strlen(aux2))<0){
          printf("Error: %d, al escribir el número de bloques.\n", errno);
          perror("Error al escribir el número de bloques.\n");
          exit(EXIT_FAILURE);
        }
        if(write(fd_out,aux,strlen(aux))<0){
          printf("Error: %d, al reescribir el resto del archivo.\n", errno);
          perror("Error al reescribir el resto del archivo.\n");
          exit(EXIT_FAILURE);
        }

      /* Cerramos archivos y liberamos memoria dinámica */
        free(aux2);
        free(aux);
        if (argc==2 && close(fd_in)<0){
          printf("Error: %d, al cerrar archivo de entrada.\n", errno);
          perror("Error al cerrar archivo de entrada.\n");
          exit(EXIT_FAILURE);          
        }

        if (close(fd_out)<0){
          printf("Error: %d, al cerrar archivo de salida.\n", errno);
          perror("Error al cerrar archivo de salida.\n");
          exit(EXIT_FAILURE);
        }

    return EXIT_SUCCESS;

}
