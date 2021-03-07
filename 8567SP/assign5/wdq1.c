#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const int max = 1000;
	int counter;
	int i = 0;
	char* desc = 0;
	while (i++ < max) {
		desc = strsignal(i);
		if (strstr(desc, "Unknown signal") == 0) {
			counter++;
			printf("%d - %s\n", i, desc);
		}		
	}

	printf("in all, %d signals are supported by the system.\n", counter);
	return 0;
}
