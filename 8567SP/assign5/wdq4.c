#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void my_alarm_handler(int dummy){  
	printf("Ding!\n", getpid(), dummy);
}

int main(int argc, char *argv[]){  
	pid_t pid;
    void (*oldhandler)(int);
    int alarm_in_seconds;

    if (argc != 2) {
        printf("usage: alarm n\n");
        exit(1);
    }

    printf("alarm application starting\n");

    alarm_in_seconds = atoi(argv[1]);

	oldhandler = signal(SIGALRM, my_alarm_handler);

    if((pid=fork())==0){ //child process code
        sleep(alarm_in_seconds);
        kill(getppid(), SIGALRM);
    }
    printf("waiting for alarm to go off\n");
    pause();

    // restore handler.
    signal(SIGALRM, oldhandler);

    printf("done");

    return 0;
}