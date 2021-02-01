#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);

    if (argc == 1)
    {
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fd = open(*++argv, O_RDONLY)) == -1)
            {
                printf("cat: can not open %s\n", *argv);
                return 1;
            }
            else
            {
                filecopy(fd, STDOUT_FILENO);
                close(fd);
            }
        }
    }
    return 0;
}
void filecopy(int fd1, int fd2)
{
    const int buffer_size = 100;
    char buffer[buffer_size];
    long read_size;
    while ((read_size = read(fd1, buffer, buffer_size)) != -1)
    {
        write(fd2, buffer, read_size);
    }
}