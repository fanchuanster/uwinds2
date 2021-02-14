#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>

void printpstate(int num, ...)
{
    va_list arguments;
    va_start(arguments, num);
    int i = 0;
    printf("pid %d\tppid=%d\n", getpid(), getppid());
    for (i=0; i<num; i++)
    {
        printf("%d\n", va_arg(arguments, pid_t));
    }
}

int main() {
    pid_t pid1, pid2, pid3;
    pid1=0, pid2=0, pid3=0;

    printpstate(3, pid1, pid2, pid3);

    pid1= fork(); /* A */

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
       return 0;
    }
}
