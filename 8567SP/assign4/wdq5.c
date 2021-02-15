#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

static char tmpbuf[1000];

#define	E_WRONG_STATEMENT	50
#define	E_DIVISION_BY_ZERO	100
#define	E_WRONG_OP			200

const char VALID_OPERATORS[] = {'+', '-', '*', '/'};

void printl(char* message) {
	write(STDOUT_FILENO, message, strlen(message));
	if (message[strlen(message)-1] != '\n') {
		write(STDOUT_FILENO, "\n", 1);
	}
	fsync(STDOUT_FILENO);
}

int arrayContains(const char* array, char c) {
	int i =0;
	for (i=0; i<sizeof(array)/sizeof(array[0]); i++) {
		if (array[i] == c) {
			return 1;
		}
	}
	return 0;
}

int basicArithmeticsOperation(int operand1, char operator, int operand2) {
	switch (operator) {
		case '+':
			return operand1 + operand2;
		case '-':
			return operand1 - operand2;
		case '*':
			return operand1 * operand2;
		case '/':
			return operand1 / operand2;
		default:
			assert(0);
			break;
	}
}

void childFunction(char* line) {
	printl("I am a child working for my parent");
	int operand1, operand2;
	char operator;
	int count = sscanf(line, "%d %c %d", &operand1, &operator, &operand2);
	if (count != 3) {
		exit(E_WRONG_STATEMENT);
	}
	else if (!arrayContains(VALID_OPERATORS, operator)) {
		exit(E_WRONG_OP);
	} else if (operand2 == 0 && operator == '/') {
		exit(E_DIVISION_BY_ZERO);
	}

	sprintf(tmpbuf, "%d %c %d = %d", operand1, operator, operand2, basicArithmeticsOperation(operand1, operator, operand2));
	printl(tmpbuf);

	exit(0);
}

int main(int argc, char *argv[])
{
	const int MAXBUF = 256;

	char inpbuf[MAXBUF];
	pid_t pidc;

	while(1) {
		
		printl("Enter an arithmetic statement, e.g., 34 + 132 >");

		ssize_t readSize;
		if (EOF == (readSize = read(STDIN_FILENO, inpbuf, MAXBUF))) {
			printl("EOF read");
			break;
		}

		pidc = fork();
		if (pidc == 0) {
			childFunction(inpbuf);
		}
		else {
			printl("Created a child to make your operation, waiting");
			
			int status;
			wait(&status);

			status = WEXITSTATUS(status);

			switch(status) {
				case E_WRONG_STATEMENT:
					printl("Wrong statement");
					break;
				case E_DIVISION_BY_ZERO:
					printl("Division by zero");
					break;
				case E_WRONG_OP:
					printl("Wrong operator");
					break;
				default:
					assert(status == 0);
					break;
			}
		}		
	}
	
    return 0;
}

