#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const int max = 1000;
	int i = 0;
	char* desc = 0;
	while (i++ < max) {
		desc = strsignal(i);
		if (strcmp("Unknown signal", desc) != 0) {
			printf("%d - %s\n", i, desc);
		}		
	}
}
