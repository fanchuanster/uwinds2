//do nothing is a program with an infinite loop displaying â€Do  nothing programâ€ every one 
//second.

#include <unistd.h>
#include <stdio.h>

int main() {

	while(1) {
		printf(" Do nothing program.\n");
		sleep(1);
	}


}