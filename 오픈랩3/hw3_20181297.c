#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 1000

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

typedef struct element
{
	struct element* link;
	precedence data;
}stack;
stack* top = NULL;

char expr[MAX_EXPR_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void rExpr(FILE* _fp, char* expr);
precedence getToken(char*, int*);
void postfix();
void printToken(precedence);
precedence pop();
void push(precedence);

int main() {
	FILE* rfp = fopen("expr.txt", "r");

	rExpr(rfp, expr);
	postfix();

	return 0;
}

void rExpr(FILE* rfp, char* expr)
{

	/* File Existence Check */
	if (!rfp) {
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be shuts down\n");
		exit(0);
	}

	/* Scanning Input */
	int i = 0;
	while (1) { //공백처리를 위해 fgetc를 이용하여 문자를 하나씩 받는다.
		char c = fgetc(rfp); 
		if (c == EOF) break;
		else if (c == ' ') {}
		else {
			expr[i++] = c;
		}
	}

	fclose(rfp);
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void postfix() {
	char symbol;
	precedence token;
	int n = 0;

	push(eos);

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand )
			printf("%c ", symbol);
		else if (token == rparen) {
			while (top->data != lparen)
				printToken(pop());
			pop();
		}
		else {
			while (isp[top->data] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}

void printToken(precedence token) {
	switch (token) {
	case plus: printf("+ ");	break;
	case minus: printf("- "); break;
	case divide: printf("/ "); break;
	case times: printf("* "); break;
	case mod: printf("%% "); break;
	case eos: printf(" "); break;
	default: printf("\n");
	}
}

precedence pop() {
	stack* temp = top;
	precedence token = temp->data;

	top = temp->link;
	free(temp);

	return token;
}

void push(precedence item) {
	stack* temp = (stack*)malloc(sizeof(stack));
	temp->data = item;
	temp->link = top;
	top = temp;
}