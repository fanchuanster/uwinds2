#include <stdio.h>

int main() {

//	char *s="34 asfd 132>";

	char *s="34 + 132>";

 	int op1,op2;
	char op; char ending;

	int rt=sscanf(s, "%d %c %d %c", &op1, &op, &op2, &ending);

	printf("rt=%d\n", rt); //rt==4, correct statement, rt!==4, wrong statement

	printf("op1=%d op=%c op2=%d ending=%c\n", op1, op, op2, ending);

}
