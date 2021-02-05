//copy file f1 to f2 using standard I/O

#include<stdio.h>

int main(int argc, char * argv[])
{
	FILE *inf;
	int c;
	char buf[512];

	if ((inf = fopen(argv[1],"r")) == NULL)
	{
		return (-1);
	}

	while(!feof(inf)) {
		char *p;
		p=fgets(buf, 512, inf);
		fputs(buf,stdout);

	}
	
	fclose(inf);


	return (0);
}


