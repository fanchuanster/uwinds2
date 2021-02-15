#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void printt(char* message) {
	write(STDOUT_FILENO, message, strlen(message));
}

void childFunction(char* line) {
	printt("in childFunction");
	printt(line);
}

int main(int argc, char *argv[])
{
	const int MAXBUF = 256;

	char inpbuf[MAXBUF];
	pid_t pidc;

	int i;
	while(i++ < 2) {
		
		printt("Enter an arithmetic statement, e.g., 34 + 132 > ");

		char* line;
		if (NULL == (line = read(STDIN_FILENO, inpbuf, MAXBUF))) {
			printt("NULL read");
			continue;
		}

		printt(line);

		pidc = fork();
		if (pidc == 0) {
			childFunction(line);
		}
		else {
			printff("Created a child to make your operation, waiting");
		}		
	}
	
    return 0;
}

