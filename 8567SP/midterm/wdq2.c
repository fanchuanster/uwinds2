#include<stdio.h>
#include<stdlib.h>

#include <unistd.h>
#include <fcntl.h>


int main()
{
    printf("I am the parent process, my pid = %d", getpid());
    return 0;
}

