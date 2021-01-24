#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char* pp[2][4] = { { "101", "GM", "Buick", "2010" }, { "102", "Ford", "Lincoln", "2005" } };
	int i, j, n1;
	int fd1;
	if ((fd1 = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0700)) == -1) {
		perror("file problem ");
		exit(1);
	}

	for (i = 0; i < sizeof(pp) / sizeof(char**); i++) {
		for (j = 0; j < sizeof(*pp) / sizeof(char*); j++) {
			printf("%s", pp[i][j]);
			n1 = write(fd1, pp[i][j], strlen(pp[i][j]));
			if (n1 != strlen(pp[i][j])) {
				perror("write problem "); exit(2);
			}
			if (j == 0) {
				write(fd1, "   ", 3);
			}
			else {
				write(fd1, "\t", 1);
			}
		}
		write(fd1, "\n", 1);
	}
	close(fd1);

	printf_s("file %s created", argv[1]);
	
    return 0;
}

