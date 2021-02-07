#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {  
	int newpid;
	int status;

	const char* message_pattern = "I am a child process, my parent pid = %d, my pid = %d\n";

	printf("I am the parent process, my pid = %d\n", getpid());

	if ((newpid = fork()) == -1 )
	{
		perror("fork"); 
		return -1;
	}

	if (newpid == 0) {
		printf(message_pattern, getppid(), getpid());
		newpid = fork();
		if (newpid == 0) {
			sleep(1);
			printf(message_pattern, getppid(), getpid());
		} else {
			waitpid(newpid, &status, 0);
		}
	}
	else {
		newpid = fork();
		
		if (newpid == 0) {
			printf(message_pattern, getppid(), getpid());
			newpid = fork();
			if (newpid == 0) {
				sleep(1);
				printf(message_pattern, getppid(), getpid());
			} else {
				waitpid(newpid, &status, 0);
			}
		} else {
			printf("I am the parent process, my pid = %d\n", getpid());
			sleep(2);
		}
	}
}


