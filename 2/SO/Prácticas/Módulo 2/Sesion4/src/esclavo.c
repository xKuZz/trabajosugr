#include<sys/types.h>
#include<fcntl.h>
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]){
  int ext_inferior;
  int ext_superior;
  double raiz;
  int i,j;
  int primo;
  if (argc!=3)
    exit(-1);
  ext_inferior=strtol(argv[1],NULL,10);
  ext_superior=strtol(argv[2],NULL,10);

  for (i=ext_inferior; i<=ext_superior; ++i){
    raiz=sqrt(i*1.0);
    primo=1;
    for(j=2;j<=raiz ;++j)
      if(i%j==0) {
        primo=0;
        break;
      }
    if(primo) 
        printf("%d\n", i);
    
      
  }
  return 0;
}
  
