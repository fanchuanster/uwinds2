#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>

void printpstate(const char* message, int num, ...)
{
    va_list arguments;
    va_start(arguments, num);
    int i = 0;
    printf("%s\tpid %d, ppid=%d\t", message, getpid(), getppid());
    for (i=0; i<num; i++)
    {
        printf("%d, ", va_arg(arguments, pid_t));
    }
    printf("\n");
}

int main() {
    pid_t pid1, pid2, pid3;
    pid1=0, pid2=0, pid3=0;

    printpstate("main process", 3, pid1, pid2, pid3);

    pid1= fork(); /* A */   
    if(pid1==0){
        printpstate("A ", 3, pid1, pid2, pid3);
        pid2=fork(); /* B */
        printpstate("B created", 3, pid1, pid2, pid3);
        pid3=fork(); /* C */
        printpstate("C created", 3, pid1, pid2, pid3);
    } else {
        printpstate("A created", 3, pid1, pid2, pid3);
        pid3=fork(); /* D */
        if(pid3==0) {
            printpstate("D", 3, pid1, pid2, pid3);
            pid2=fork(); /* E */
            printpstate("E created", 3, pid1, pid2, pid3);
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
