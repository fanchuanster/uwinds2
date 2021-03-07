#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void myhandler(int dummy){  
	printf("ctrl-c pressed! - %d", dummy);
}

int main(int argc, char *argv[]){  
	pid_t pid;

    // install handler for Ctrl + C
	signal(SIGINT, myhandler);

    // ignore Ctrl + Z SIGSTOP
    signal(24, SIG_IGN);

    int i;
    while (i++ < 10) {
        printf("w %d\n", i);
    }

    // if((pid=fork())==0){ //child process code
    //     sleep(5);  
    //     exit(10);
    // }
    // printf("Created a child, pid=%d, pause...\n", pid);
    // pause();
    // printf("parent process ended.\n");
}