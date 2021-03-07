#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void childDeath(int dummy){  
	int status;
	pid_t pid = wait(&status);
	printf("Child %d has terminated with status %d\n", pid, WEXITSTATUS(status));
}

int main(int argc, char *argv[]){  
	pid_t pid;

    // install handler for SIGCHLD
	signal(SIGCHLD, childDeath);

    if((pid=fork())==0){ //child process code
        sleep(5);  
        exit(10);
    }
    printf("Created a child, pid=%d, pause...\n", pid);
    pause();
    printf("parent process ends.");
}