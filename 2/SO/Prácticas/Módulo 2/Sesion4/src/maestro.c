#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
  int cauce[2][2];
  int i, leidos;
  int ext_inferior;
  int ext_superior;
  int intermedio;
  char *inter1;
  char *inter2;
  char buffer[1000]="";
  char buffer1[1000]="";
  
  pid_t esclavo1, esclavo2;

  if (argc!=3) {
    perror("Número de argumentos incorrecto.");
    printf("Formato: <ext_inferior> <ext_superior>\n");
    exit(-1);
  }
  ext_inferior=strtol(argv[1],NULL,10);
  ext_superior=strtol(argv[2],NULL,10);
  intermedio=(ext_superior-ext_inferior)/2 + ext_inferior;
  asprintf(&inter1,"%d",intermedio);
  asprintf(&inter2,"%d",intermedio+1);

  
  pipe(cauce[0]);
  pipe(cauce[1]);


  
  esclavo1=fork();

  if (esclavo1 == 0) { 
    close(cauce[0][0]);
    close(cauce[1][0]);
    close(cauce[1][1]);
    close(1);
    dup(cauce[0][1]);
    execl("./esclavo","./esclavo",argv[1],inter1,NULL); 
  } 
  else { 
  
  esclavo2 = fork();
       
  if (esclavo2 == 0) { /* Esclavo 2 */
       close(cauce[0][0]);
       close(cauce[0][1]);
       close(cauce[1][0]);
       close(1);
       dup(cauce[1][1]);
       execl("./esclavo","./esclavo",inter2,argv[2],NULL); 
    }   
   
   else {
      close(cauce[0][1]);
      while ((leidos=read(cauce[0][0],buffer,sizeof(buffer)))>0) {
        char salida[leidos];
        for(i=0; i<=leidos; i++) {
          salida[i]=buffer[i];
        }
        printf("%s",salida);
      }
      close(cauce[0][0]);
      close(cauce[1][1]);
      while ((leidos=read(cauce[1][0],buffer1,sizeof(buffer1)))>0) {
        char salida[leidos];
        for(i=0; i<=leidos; i++) {
            salida[i]=buffer1[i];
        }
        printf("%s",salida);
      }
     close(cauce[1][0]);
    }
  }
  return 0;
}
    
