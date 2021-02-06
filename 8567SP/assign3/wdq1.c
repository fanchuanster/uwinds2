#include<stdio.h>
#include <unistd.h>

int main(){
	printf("before fork, my pid is %d, ppid is %d\n" , getpid(), getppid());
	fork();
	printf("after 1 fork, my pid is %d with ppid %d\n" , getpid(), getppid());
	fork();
	printf("after 2 fork, my pid is %d with ppid %d\n" , getpid(), getppid());
	fork();
	printf("after 3 fork, my pid is %d with ppid %d\n" , getpid(), getppid());
	sleep(1);
}
