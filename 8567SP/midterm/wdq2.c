#include<stdio.h>
#include<stdlib.h>

#include <unistd.h>
#include <fcntl.h>


int main()
{
    pid_t pid;
    char buffer[100];
    const char* child_self_intro = "%s I am a child process, my parent pid = %d, my pid = %d\n";

    printf("I am the parent process, my pid = %d\n", getpid());

    // create c3
    pid = fork();
    if (0 == pid)
    {
        printf(buffer, ".", getppid(), getpid());
        exit(0);
    }

    // create c2
    pid = fork();
    if (0 == pid)
    {
        printf(buffer, ".", getppid(), getpid());
        exit(0);
    }

    // create c1
    pid = fork();
    if (0 == pid)
    {
        printf(buffer, ".", getppid(), getpid());

        // create c4
        pid = fork();
        if (0 == pid)
        {
            printf(buffer, "..", getppid(), getpid());
            sleep(1);   // dummy doing something.
            exit(57);
        }

        int status;
        waitpid(pid, &status, 0);

        printf(". I am process c1, Exit status from child process c4 was %d\n", WEXITSTATUS(status));

        // sleep for my parent process to end so myself become an orphan.
        sleep(3);

        printf(buffer, ".", getppid(), getpid());

        exit(0);
    }

    sleep(1);

    return 0;
}

