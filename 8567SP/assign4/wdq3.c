#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd1;
	pid_t pid;
	const char* hello_from_child = "Hello from child process, and closing fd1";
	const char* hello_from_parent = "Hello from parent process";
	const char* greetings_from_parent = "Greetings from parent process";
	const char* output_file = "wdq3.txt";
	
	if ((fd1 = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0700)) == -1) {
		perror("file problem ");
		exit(1);
	}

	pid = fork();

	if (pid == 0) {
		write(fd1, hello_from_child, strlen(hello_from_child));
		write(fd1, "\n", 1);

		/* sleep to allow parent process to say hello. */
		sleep(1);
		close(fd1);
		if (-1 == write(fd1, "s", 1)) {
			perror("greetings failed in child ");
		}

		/* prolong child process longevity to preclude impact by process exit which would impact 
		 *  fd1 vadility
		 */
		// printf("end of child\n");
		sleep(2);
	} else {
		write(fd1, hello_from_parent, strlen(hello_from_parent));
		write(fd1, "\n", 1);

		/* sleep for a while to ensure fd1 closed. */
		// printf("writing to the file again\n");
		sleep(2);
		if (-1 == write(fd1, greetings_from_parent, strlen(greetings_from_parent))) {
			perror("greetings failed ");
		}
		else {
			close(fd1);
		}

		printf("test strings wrote to %s\n", output_file);
	}	
	
    return 0;
}

