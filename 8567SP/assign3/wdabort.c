#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {  
	int newpid;
	
	printf("before: mypid is %d\n", getpid());  

	if ((newpid = fork()) == -1 )
		perror("fork");  
	else if (newpid == 0){
		printf("I am the child %d now sleeping...\n",getpid());  
		sleep(5);
		abort();
	}
	else{
		printf("I am the parent %d\n",getpid());  

		int status;
		int child_pid  = wait(&status);

		printf("My child %d has terminated\n",child_pid);
		printf("I have received the status = %d\n",status);  

		int child_status = WEXITSTATUS(status);

		int signal = WTERMSIG(status);  
		int core = WCOREDUMP(status);

		printf("Child status = %d Signal = %d Core = %d\n",
				child_status, signal, core);
	}
}


