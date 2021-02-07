//reverse lines order
#include <assert.h>
#include<stdio.h>

void copyline(FILE* inf, FILE* outf)
{
	char buf[1024];
	char* p = fgets(buf, 1024, inf);
	if (p)
	{
		printf("writing - %s", p);
		fputs(p, outf);
	}
}

int main(int argc, char * argv[])
{
	FILE *inf, *outf;
	int c;
	

	if (argc != 3)
	{
		printf("usage:\n reverseFile infile outfile");
		return (-2);
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
		int cur = ftell(inf);
		if (0 == cur)
		{
			copyline(inf, outf);
		}
		else
		{
			c = fgetc(inf);
			if (c == '\n')
			{
				copyline(inf, outf);
			}

			fseek(inf, cur, SEEK_SET);
		}
		
	} while (0 == fseek(inf, -1, SEEK_CUR));
	
	fclose(inf);
	fclose(outf);

	return (0);
}


