#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void action(int dummy){  
  	 sleep(1); 
	 printf("Switching\n");
}

int main(int argc, char *argv[]){  
	pid_t pid;

	if((pid=fork())==0) {//child
		int counter;
		while(1){
			printf("In child process, counter \n", ++counter);
            sleep(1);
		}
	}
	else  //parent
		while(1){
			kill(pid, SIGSTOP);
			printf("SIGSTOP has been sent to Child\n");  
            sleep(3);
            kill(pid, SIGCONT);
            printf("SIGCONT has been sent to Child\n");
            sleep(3);
            kill(pid, SIGTERM);
			printf("SIGTERM has been sent to Child\n");
	}
    sleep(1);
    
    return 0;
}