#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printl(char* message) {
	write(STDOUT_FILENO, message, strlen(message));
	if (message[strlen(message)-1] != '\n') {
		write(STDOUT_FILENO, "\n", 1);
	}
	fsync(STDOUT_FILENO);
}

void childFunction(char* line) {
	printl("in childFunction");
	printl(line);
}

int main(int argc, char *argv[])
{
	const int MAXBUF = 256;

	char inpbuf[MAXBUF];
	pid_t pidc;

	int i = 0;
	while(i++ < 2) {
		
		printl("Enter an arithmetic statement, e.g., 34 + 132 >");

		ssize_t readSize;
		if (EOF == (readSize = read(STDIN_FILENO, inpbuf, MAXBUF))) {
			printl("EOF read");
			continue;
		}

		// printl(readSize);
		printl(inpbuf);

		pidc = fork();
		if (pidc == 0) {
			childFunction(inpbuf);
		}
		else {
			printl("Created a child to make your operation, waiting");
			int status;
			wait(&status);
		}		
	}
	
    return 0;
}

