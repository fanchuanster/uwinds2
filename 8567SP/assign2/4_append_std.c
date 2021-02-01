#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    FILE* fd;
    FILE* fdout;
    int i;
    void filecopy(FILE*, FILE*);

    // for (i=0; i<argc; i++)
    // {
    //     printf("%s\n", argv[i]);
    // }

    if (argc < 3)
    {
        printf("usage: ./append filename1 filename2 combinednewfile");
        return 1;
    }

    if ((fdout = fopen(argv[argc-1], "w+")) == NULL)
    {
        printf("Failed to open file %s for writing", argv[argc-1]);
        perror("error: ");
        return (2);
    }
    
    int paramscounter = argc;
    while (--paramscounter > 1)
    {
        if ((fd = fopen(*++argv, "r")) == NULL)
        {
            printf("cat: can not open %s\n", *argv);
            return 3;
        }
        else
        {
            filecopy(fd, fdout);
            fclose(fd);
        }
    }

    fseek(fdout, 0, SEEK_SET);

    filecopy(fdout, stdout);
    fclose(fdout);

    printf("\n");
    return 0;
}
void filecopy(FILE* fd1, FILE* fd2)
{
    const int buffer_size = 100;
    char buffer[buffer_size];
    long read_size;
    int n;
    
    while ((read_size = fread(buffer, buffer_size, 1, fd1)) > 0)
    {
        n = fwrite(buffer, read_size, 1, fd2);
        printf("%d bytes writen\n", n);
    }
    printf("%d read_size", read_size);
}