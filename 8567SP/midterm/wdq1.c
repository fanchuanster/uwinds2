#include<stdio.h>
#include<stdlib.h>

#include <unistd.h>
#include <fcntl.h>

int main()
{
    FILE *fp;
    int fd2;
    char buffer[50];
    int roll_no, chars;
    float marks;

    const char* infilename = "records.txt";
    const char* outfilename = "results.txt";

    const char* resultpattern = "The result of multiplying %.2f by 2 is %.2f\n";

    fp = fopen(infilename, "r");
    if(fp == NULL)
    {
        perror("Error opening file\n");
        exit(1);
    }

    if ((fd2 = open(outfilename, O_CREAT | O_RDWR, 777)) == -1)
    {
        perror("Error opening file for output");
        exit(2);
    }


    while( fscanf(fp, "%f", &marks) != EOF )
    {
        printf("%.2f\n", marks);
        int size = sprintf(buffer, resultpattern, marks, marks * 2);
        write(fd2, buffer, size);
    }

    fclose(fp);
    close(fd2);
    return 0;
}

