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
	char str1[] = "abcd", str2[] = "abCd", str3[] = "abcd";
    int result;

    // comparing strings str1 and str2
    result = strcmp(str1, str2);
    printf("strcmp(str1, str2) = %d\n", result);

    // comparing strings str1 and str3
    result = strcmp(str1, str3);
    printf("strcmp(str1, str3) = %d\n", result);

    return 0;
}
