#include <stdio.h>


int main(int argc, char *argv[]){  
	FILE *fd;
	
	char ch;

	int fileSize=-1;

	fd = fopen(argv[1], "r+");      
	 
	fseek(fd, 10L, SEEK_SET);
	putc(-1, fd);	
	rewind(fd);                 //try uncomment this block, to see what it does.

	do{
		ch=getc(fd);  
		fileSize++;
	} while( ch != EOF);

    fclose(fd);
	
	printf("Size of %s is %d\n", argv[1], fileSize);
}
