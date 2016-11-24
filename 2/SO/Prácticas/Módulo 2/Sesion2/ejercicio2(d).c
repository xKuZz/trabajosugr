
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	DIR *dirstream;
	struct dirent *archivo;
	char *path;
	char *filepath;
	unsigned bandera;
	unsigned antigua_bandera;
	struct stat atributos;

	if (argc!=3){ /* Compruebo argumentos válidos */
			printf("Número de argumentos inválido.\n");
      perror("Número de argumentos inválido.\n");
      exit(EXIT_FAILURE);
	 }

  /* Proceso argumentos y abro directorio */
	path=argv[1];
	bandera=strtol(argv[2],NULL,8);
	if((dirstream=opendir(path))==NULL){
		printf("Error: %d al abrir el directorio.\n", errno);
    perror("Error al abrir el directorio.\n");
    exit(EXIT_FAILURE);
  }

	/* Leo todo el directorio */
	while ((archivo=readdir(dirstream))!=NULL){
		printf("%s: ",(*archivo).d_name); /* Nombre archivo */
		filepath=(char *)realloc(filepath,(strlen((*archivo).d_name)+strlen(path))+1);
		strcpy(filepath,path);
		strcat(filepath,"/");
		strcat(filepath,(*archivo).d_name);
		if (stat(filepath,&atributos)<0){ /* Leo metadatos archivo iniciales */
			printf("Error: %d al leer los metadatos de %s.\n", errno,(*archivo).d_name);
    	perror("Error al leer datos del archivo.\n");
			exit(EXIT_FAILURE);
		}
		antigua_bandera=atributos.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
		if (chmod(filepath,bandera)<0){ /* Cambio permisos */
			printf("%d %o\n",errno,antigua_bandera);
			perror("No se han podido cambiar los permisos.\n");
		}
		if (stat(filepath,&atributos)<0){ /* Releo metadatos de archivos */
			printf("Error: %d al leer los metadatos de %s.\n", errno,(*archivo).d_name);
    	perror("Error al leer datos del archivo.\n");
			exit(EXIT_FAILURE);
		}
			printf("%o %o\n",antigua_bandera,atributos.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
		
	}
	free (filepath); /* Libero memoria dinámica */

  /* Cierro directorio */
	if (closedir(dirstream)<0){
		printf("Error: %d al cerrar el directorio.\n", errno);
    perror("Error al cerrar el directorio.\n");
		exit(EXIT_FAILURE);
	}
		
	


	return EXIT_SUCCESS;
}
