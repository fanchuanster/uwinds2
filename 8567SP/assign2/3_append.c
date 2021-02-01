#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd, fdout;
    int i;
    void filecopy(int, int);

    for (i=0; i<argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    if (argc < 3)
    {
        printf("usage: ./append filename1 filename2 combinednewfile");
        return 1;
    }

    if ((fdout = open(argv[argc-1], O_CREAT | O_WRONLY, 0700)) == -1)
    {
        printf("Failed to open file %s for writing", argv[argc-1]);
        perror("error: ");
        return (2);
    }
    
    int paramscounter = argc;
    while (--paramscounter > 1)
    {
        if ((fd = open(*++argv, O_RDONLY)) == -1)
        {
            printf("cat: can not open %s\n", *argv);
            return 3;
        }
        else
        {
            filecopy(fd, fdout);
            close(fd);
        }
    }
    close(fdout);

    if ((fdout = open(argv[argc-1], O_RDONLY)) == -1)
    {
        printf("Failed to open file %s for reading", argv[argc-1]);
        return (4);
    }

    filecopy(fdout, STDOUT_FILENO);

    printf("\n");
    return 0;
}
void filecopy(int fd1, int fd2)
{
    const int buffer_size = 100;
    char buffer[buffer_size];
    long read_size;
    while ((read_size = read(fd1, buffer, buffer_size)) > 0)
    {
        write(fd2, buffer, read_size);
    }
}