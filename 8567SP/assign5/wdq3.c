#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void myhandler(int dummy){  
	printf("ctrl-c pressed! - signo %d\n", dummy);
}

void childDeath(int dummy){  
	int status;
	pid_t pid = wait(&status);
	printf("Child %d has terminated with status %d\n", pid, WEXITSTATUS(status));
}

int main(int argc, char *argv[]){  
	pid_t pid;

    void (*oldhandler)();
    void (*oldhandler2)();

    printf("SIGTSTP %d\n", SIGTSTP);

    /***
     * a. install handler for Ctrl + C and ignore Ctrl + Z
     ***/     
	oldhandler = signal(SIGINT, myhandler);
    oldhandler2 = signal(SIGTSTP, SIG_IGN);

    signal(SIGCHLD, childDeath);

    /***
     * b. test installed handler for Ctrl + C and ignored Ctrl + Z.
     ***/
    printf("for ignored Ctrl + Z or Ctrl + C, test them within 15 seconds.\n");
    int i;
    while (i++ < 15) {
        printf("w %d\n", i);
        sleep(1);
    }

    if((pid=fork())==0){ //child process code
        execlp("./donothing", (char*)NULL);
    }
    
    for(i=1; i<=5; i++) {
        printf("I am in parent process (%d).\n", getpid());
        //send a Ctrl + C signal to child and parent process.
        kill(pid, SIGINT);
        kill(pid, SIGTSTP);

        kill(getpid(), SIGINT);
        kill(getpid(), SIGTSTP);
     
        sleep(1);
    }

    // restore handlers
    signal(SIGINT, oldhandler);
    signal(SIGTSTP, oldhandler2);

    sleep(2);
}