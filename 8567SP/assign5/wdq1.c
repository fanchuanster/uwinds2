#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const int max = 10000;
	int i = 0;
	char* desc = 0;
	while (i++ < max) {
		printf(i);
		desc = strsignal(i);
		if (desc) {
			printf(desc);
		} else {
			printf("None");
		}
	}
}
