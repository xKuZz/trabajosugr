#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){

    pid_t childpid, childpid2;

    struct flock cerrojo;
    int fd, status;

    if ((fd=open("ejer3", O_RDWR)) == -1) 
        perror("apertura fallo");

    cerrojo.l_type   = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start  = 0;
    cerrojo.l_len    = 2; /* lock "doors" (i.e. bytes)  0 and 1*/

    if (fcntl(fd, F_SETLK,&cerrojo) == -1) 
        perror("cerrojo fallo");


    if((childpid= fork())){ /* parent */
      if ((childpid2= fork())) { /* still parent */

            cerrojo.l_type = F_UNLCK;
            cerrojo.l_len  = 2; /* unlock both doors: let the fun begin :-) */

            sleep(2);
            printf("Tata va a quitar el cerrojo....\n");
            fcntl(fd, F_SETLKW, &cerrojo); 

            waitpid(childpid,&status,0);
            waitpid(childpid2,&status,0);
        }
    }

    if(!childpid||!childpid2){ /* in child 1 or child 2 */

        printf("Soy el hijo %d\n",getpid());

        int offset0 = (childpid ? 0 : 1);  /* child1 gets 0 and 1, child 2 gets 1 and 0 */
        int offset1 = (childpid ? 1 : 0);
        cerrojo.l_len = 1;


        cerrojo.l_start =  offset0; /* lock door 0 (1) as soon as parent lets us*/
        printf("PID %d locking byte %d\n", getpid(), offset0);
        if(fcntl(fd, F_SETLKW,&cerrojo) == -1){ 
          printf("CERROJO byte %d FALLA EN PID %d (%s)\n",offset0, getpid(),  strerror(errno));
        }

        sleep(1); /* guarantee that the other child has our next door locked ... */
        printf("PID %d locking byte %d\n", getpid(), offset1);
        cerrojo.l_start =  offset1; /* lock door 1 (0). The second of both children who gets here closes the circle and faces deadlock */
        if(fcntl(fd, F_SETLKW,&cerrojo) == -1){
          printf("CERROJO byte %d FALLA EN PID: %d (%s)\n", offset1, getpid(), strerror(errno));
        }

        printf("HIJO %d ACABADO (releasing its lock)\n", getpid()); /* Falling off the end of main() will release the lock anyway */

    }
}
