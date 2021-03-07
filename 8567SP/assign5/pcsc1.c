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

	if((pid=fork())>0){//parent  
		sleep(1);
		while(1){
			printf("Parent is running\n");
			kill(pid, SIGUSR1);  
			signal(SIGUSR1, action);  
			printf("Parent paused\n");
			pause();
		}
	}
	else  //child code
		while(1){//child  
			signal(SIGUSR1, action);  
			kill(getppid(), SIGUSR1);
			sleep(1);
			int status
			waitpid(getppid(), &status, 0);
			printf("parent has terminated with status %d\n", WEXITSTATUS(status));
			printf("child paused\n");
			pause();
			printf("Child is running\n");  
			
	}
}