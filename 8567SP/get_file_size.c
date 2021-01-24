#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){ 

 int fd1;
 long filesize;


 if ((fd1 = open(argv[1], O_RDONLY)) == -1) {

   perror("file problem ");  

   exit(1);
 }


 filesize = lseek(fd1, 0, SEEK_END);

// in Case of an error exit from the loop  
 if(filesize == -1){
  perror("Reading problem ");  
 }

 close(fd1);
 
 printf("%d\n", filesize);

 exit(0);
}