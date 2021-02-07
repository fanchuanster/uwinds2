//reverse lines order
#include <assert.h>
#include<stdio.h>

int main(int argc, char * argv[])
{
	FILE *inf, *outf;
	int c;
	char buf[1024];

	assert(0);

	if (argc != 3)
	{
		printf("usage:\n reverseFile infile outfile");
		exit(2)
	}

	if ((inf = fopen(argv[1],"r")) == NULL)
	{
		printf("Failed to open %s", argv[1]);
		return (-1);
	}
	if ((outf = fopen(argv[2],"w")) == NULL)
	{
		printf("Failed to open %s for write", argv[2]);
		return (-2);
	}

	if (0 != fseek(inf, -1, SEEK_END))
	{
		printf("Failed to move cur to the last char, maybe a empty input file", argv[2]);
		return (0);
	}

	do {
		c = fgetc(inf);
		if (c == '\n')
		{
			int cur = ftell(inf);
			char* p = fgets(buf, 1024, inf);
			assert(p != NULL);
			fputs(p, outf);
			fseek(inf, cur, SEEK_SET);
		}
	} while (0 == fseek(inf, -2, SEEK_CUR));
	
	fclose(inf);
	fclose(outf);

	return (0);
}


