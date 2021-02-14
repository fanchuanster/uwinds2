#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>

void printpstate(int num, ...)
{
    va_list arguments;
    va_start(arguments, num);
    int i = 0;
    printf("pid %d, ppid=%d\t", getpid(), getppid());
    for (i=0; i<num; i++)
    {
        printf("%d, ", va_arg(arguments, pid_t));
    }
    printf("\n");
}

int main() {
    pid_t pid1, pid2, pid3;
    pid1=0, pid2=0, pid3=0;

    printf("\n");

    printpstate(3, pid1, pid2, pid3);

    pid1= fork(); /* A */   
    printpstate(3, pid1, pid2, pid3);
    if(pid1==0){
        printpstate(3, pid1, pid2, pid3);
        pid2=fork(); /* B */
        printpstate(3, pid1, pid2, pid3);
        pid3=fork(); /* C */
        printpstate(3, pid1, pid2, pid3);
    } else {
        pid3=fork(); /* D */
        printpstate(3, pid1, pid2, pid3);
        if(pid3==0) {
            pid2=fork(); /* E */
            printpstate(3, pid1, pid2, pid3);
        }
        if((pid1 == 0)&&(pid2 == 0))
            printf("Level 1\n");
        if(pid1 !=0)
            printf("Level 2\n");
        if(pid2 !=0)
           printf("Level 3\n");
        if(pid3 !=0)
           printf("Level 4\n");
        sleep(1);
       return 0;
    }
}
