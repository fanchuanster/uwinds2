#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){ 

 int fd1;
 long n1, count;
 char ch;


 if ((fd1 = open(argv[1], O_RDONLY)) == -1) {

   perror("file problem ");  

   exit(1);
 }


 while((n1=read(fd1, &ch, 1)) > 0) {
	if (0 == count) {
		count = 1;
		continue;
	}
	if (ch != '\n') {
		count++;
	}
 }


// in Case of an error exit from the loop  

 if(n1 == -1){

  perror("Reading problem ");  

  exit(2);

 }

 close(fd1);
 
 printf("%d lines\n", count);

 exit(0);
}