#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

void printSubCommand(char* command, char* optionalArgument){
	const int MAXBUF = 256;
	char buf[MAXBUF];

	sprintf(buf, "in sub process %d, executing %s %s\n", getpid(), command, optionalArgument);
	printf(buf);
}

void executeCommand(char* command, char* optionalArgument) {
	pid_t childPid;

	childPid = fork();
	if (childPid == 0) {
		printSubCommand(command, optionalArgument);
		execlp(command, optionalArgument);
	}
}

int main(int argc, char *argv[])
{
	const int MAXBUF = 256;
	char buf[MAXBUF];

	int i;
	for (i=0; i<argc; i++) {
		printf(argv[i]);
		printf("\n");
	}
		
    return 0;
}

