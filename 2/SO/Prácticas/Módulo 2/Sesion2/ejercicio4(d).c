
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
unsigned contador=0;
unsigned long bytes=0;
char *dirpath;

int visitar(const char *path, const struct stat *statbuf, int typeflag, 
						struct FTW *ftwbuf) {
		if (statbuf->st_mode & S_IFREG){
			printf("%s/%s %lu\n", dirpath,path,(unsigned long) statbuf->st_ino);
	 	  if (statbuf->st_mode & (S_IXGRP | S_IXOTH)) 	
					++contador;
			bytes+=statbuf->st_size;
		}
		return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
		dirpath=argc >= 2 ? argv[1] : ".";
		struct stat atributos;
    if(nftw(dirpath, visitar, 10, 0) != 0){
			perror("Fallo en nftw");
		}

		printf("Hay %i archivos regulares con permiso x para grupo y otros.\n",
              contador);
		printf("Todos ellos ocupan %lu bytes\n", bytes);
		
		return EXIT_SUCCESS;
}

  

