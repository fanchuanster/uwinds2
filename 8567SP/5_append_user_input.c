#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){ 

 char buffer[100], append[256]; long int n1;

 int fd1;


 if((fd1 = open(argv[1], O_WRONLY)) == -1){

   perror("file open problem ");

   exit(1);
 }


 while((n1=read(fd1, buffer, 100)) > 0) {
   printf("%s", buffer);
 }
 printf("\n+============please input the you would like to append, 256 chars at maximum================\n");
 n1 = scanf("%s", append);
 if (n1 > 0) {
	 write(fd1, append, n1);
 }


// in Case of an error exit from the loop  

 if(n1 == -1){

  perror("Reading problem ");  

  exit(2);

 }

 close(fd1);

 exit(0);
}