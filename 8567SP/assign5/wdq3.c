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

    void (*oldhandler)();
    void (*oldhandler2)();

    // install handler for Ctrl + C
	oldhandler = signal(SIGINT, myhandler);

    // ignore Ctrl + Z 24
    oldhandler2 = signal(SIGSTOP, SIG_IGN);

    printf("for ignored Ctrl + Z or Ctrl + C, test them within 10 seconds.\n")
    int i;
    while (i++ <= 10) {
        printf("w %d\n", i);
        sleep(1);
    }

    if((pid=fork())==0){ //child process code
        execlp("./donothing", (char*)NULL);
    }
    
    for(i=1; i<=15; i++){
    printf("I am in parent process.\n");
    //send a signal to child
    sleep(1);}

    // restore handlers
    signal(SIGINT, oldhandler);
    signal(SIGSTOP, oldhandler2);
}