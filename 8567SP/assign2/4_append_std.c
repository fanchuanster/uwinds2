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
    int ch;
    
    while ((ch = getc(fd1)) != EOF)
    {
        putc(ch, fd2); 
    }
}