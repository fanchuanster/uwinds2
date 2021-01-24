#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){ 

 char buffer[100], append[256]; long int n1, input_size;

 int fd1;


 if((fd1 = open(argv[1], O_RDWR)) == -1){

   perror("file open problem ");

   exit(1);
 }


 while((n1=read(fd1, buffer, 100)) > 0) {
   printf("%s", buffer);
 }
 printf("============please input the you would like to append, 256 chars at maximum================\n");
 scanf("%s", append);
 input_size = strlen(append);
 if (input_size > 0) {
	 printf("input:%s", append);
	 lseek(fd1, 0, SEEK_END);
	 n1 = write(fd1, append, input_size);
 } else {
	 perror("scanf problem ");
	 exit(2);
 }


// in Case of an error exit from the loop  

 if(n1 == -1){

  perror("Reading problem ");  

  exit(2);

 }

 close(fd1);

 exit(0);
}