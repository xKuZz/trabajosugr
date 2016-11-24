
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
		char *dirpath;
		char *filepath;
		long unsigned bytes=0;
		unsigned contador=0;
		DIR *dirstream;
		struct dirent *archivo;
		struct stat atributos;

		if (argc>2){
			/* Compruebo argumentos válidos */
			printf("Número de argumentos inválido.\n");
      perror("Número de argumentos inválido.\n");
      exit(EXIT_FAILURE);
		}
		if (argc==2)
			dirpath=argv[1];
		else {
			dirpath=(char *) malloc(1);
			dirpath[0]='.';
    }

	 	if((dirstream=opendir(dirpath))==NULL){
    	/* Abro directorio */
			printf("Error: %d al abrir el directorio.\n", errno);
  		perror("Error al abrir el directorio.\n");
  	  exit(EXIT_FAILURE);
  	}
			
		printf("Los inodos son: \n");
		while ((archivo=readdir(dirstream))!=NULL){
			/* Leo todos los ficheros del directorio */
			filepath=(char *)realloc(filepath,(strlen((*archivo).d_name)+strlen(dirpath))+1);
			strcpy(filepath,dirpath);
			strcat(filepath,"/");
			strcat(filepath,(*archivo).d_name);

			

			if (stat(filepath,&atributos)<0){ /* Leo metadatos de cada archivo */
				printf("Error: %d al leer los metadatos de %s.\n", errno,(*archivo).d_name);
    		perror("Error al leer datos del archivo.\n");
				exit(EXIT_FAILURE);
			}

			if (atributos.st_mode & S_IFREG){
				printf("%s %lu\n", filepath, (unsigned long) (*archivo).d_ino);
				if (atributos.st_mode & (S_IXGRP | S_IXOTH)) 	
					++contador;
				bytes+=atributos.st_size;
			}
			
    }

		printf("Hay %i archivos regulares con permiso x para grupo y otros.\n",
              contador);
		printf("Todos ellos ocupan %lu bytes\n", bytes);
		
 		free (filepath); /* Libero memoria dinámica */

 	  /* Cierro directorio */
	  if (closedir(dirstream)<0){
		  printf("Error: %d al cerrar el directorio.\n", errno);
   	  perror("Error al cerrar el directorio.\n");
			exit(EXIT_FAILURE);
		}
		return EXIT_SUCCESS;
}

  

