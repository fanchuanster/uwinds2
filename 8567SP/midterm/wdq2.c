#include<stdio.h>
#include<stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    
    const char* child_self_intro = "%s I am a child process, my parent pid = %d, my pid = %d\n";

    printf("I am the parent process, my pid = %d\n", getpid());

    // create c3
    pid = fork();
    if (0 == pid)
    {
        printf(child_self_intro, ".", getppid(), getpid());
        exit(0);
    }

    // create c2
    pid = fork();
    if (0 == pid)
    {
        printf(child_self_intro, ".", getppid(), getpid());
        exit(0);
    }

    // create c1
    pid = fork();
    if (0 == pid)
    {
        printf(child_self_intro, ".", getppid(), getpid());

        // create c4
        pid = fork();
        if (0 == pid)
        {
            printf(child_self_intro, "..", getppid(), getpid());
            sleep(1);   // dummy doing something.
            exit(57);
        }

        int status;
        waitpid(pid, &status, 0);

        printf(". I am process c1 pid %d, Exit status from child process c4 pid %d was %d\n", getpid(), pid, WEXITSTATUS(status));

        // sleep for my parent process to end so myself become an orphan.
        sleep(3);

        printf(child_self_intro, ".", getppid(), getpid());

        exit(0);
    }

    sleep(1);

    return 0;
}

