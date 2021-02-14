#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd1;
	pid_t pid;
	
	if ((fd1 = open("wdq3.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700)) == -1) {
		perror("file problem ");
		exit(1);
	}

	pid = fork();

	if (pid == 0) {
		write(fd1, "Hello from child process, and closing fd1");

		/* sleep to allow parent process to say hello. */
		sleep(1);
		close(fd1);

		/* prolong child process longevity to preclude impact by process exit which would impact 
		 *  fd1 vadility
		 */
		sleep(2);
	} else {
		write(fd1, "Hello from parent process");

		/* sleep for a while to ensure fd1 closed. */
		sleep(2);
		if (-1 == write(fd1, "Greetings from parent process")) {
			perror("greetings failed ");
		}
		else {
			close(fd1);
		}
	}
	
    return 0;
}

