#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf(" first  ");
	fork();
	printf(" second ");
}
