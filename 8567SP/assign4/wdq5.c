#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

void printSubCommand(const char* command, const char* optionalArgument){
	const int MAXBUF = 256;
	char buf[MAXBUF];

	sprintf(buf, "in sub process %d, executing %s %s\n", getpid(), command, optionalArgument);
	printf(buf);
}

void executeCommand(const char* command, const char* optionalArgument) {
	pid_t childPid;

	childPid = fork();
	if (childPid == 0) {
		printSubCommand(command, optionalArgument);
		execlp(command, command, optionalArgument, (char*)NULL);
	}
	else {
		int status;
		waitpid(childPid, &status, 0);
	}
}

int main(int argc, char *argv[])
{
	int i;
	for (i=1; i<argc; i += 2) {
		char* command = argv[i];
		char* optionalArgument;
		optionalArgument = NULL;
		if (i+1 < argc) {
			optionalArgument = argv[i+1];
		}
		executeCommand(command, optionalArgument);
	}
		
    return 0;
}

