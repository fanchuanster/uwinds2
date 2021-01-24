#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	long n1;
	char* str = "101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005";
	
	if ((fd1 = open("list1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700)) == -1) {
		perror("file problem ");
		exit(1);
	}

	n1 = write(fd1, str, strlen(str));
	if (n1 != strlen(str)) {
		perror("write problem ");
		exit(1);
	}
	close(fd1);

	printf("file list1.txt created", argv[1]);
	
    return 0;
}

