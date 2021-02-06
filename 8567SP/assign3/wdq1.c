#include<stdio.h>
#include <unistd.h>

int main(){
	printf("my pid is %d with ppid %d\n" , getpid(), getppid());
	fork();
	printf("my pid is %d with ppid %d\n" , getpid(), getppid());
	fork();
	printf("my pid is %d with ppid %d\n" , getpid(), getppid());
	fork();
	printf("my pid is %d with ppid %d\n" , getpid(), getppid());
	sleep(1);
}
