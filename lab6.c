/* COP3502 - Lab 6
Name: Deodatus Marcellino
Date: 3/5/2021
Written in COP 3502 to illustrate an array implementation of a stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // needed for isdigit

#define SIZE 100
#define EMPTY -1

struct stack {
    char items[SIZE];
    int top;

};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);
void print_stack(struct stack* stackPtr);

int checkBalance(char exp[]);
int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);

int main(void) {
    int ch;
    char exp[SIZE], c;

    int valid;
    
    printf("\nEnter expression : ");
    scanf("%[^\n]s",exp);

    printf("Your input expression: %s", exp);

    valid = checkBalance(exp);

    if(valid)
    {
    	char * postfix = infixToPostfix(exp);
    	printf("The postfix is: %s\n", postfix);

   		free(postfix);
    }

    return 0;
} // end main function

int checkBalance(char exp[]){

	int valid = 1;
	struct stack mine;

	// Set up the stack and push a couple items, then pop one.
	initialize(&mine);

	printf("\nChecking balance...\n");
	for (int i = 0; exp[i] != '\0'; i++){
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			push(&mine, exp[i]);
		else if(exp[i] == ')')
		{
			char a = pop(&mine);
			if (a == 'I' || a != '(')
			{
				valid = 0;
				printf("INVALID for ) !!\n");
				return valid;
			}
		}
		else if(exp[i] == '}')
		{
			char a = pop(&mine);
			if(a == 'I' || a != '{')
			{
				valid = 0;
				printf("INVALID for }!!");
				return valid;
			}
		}
		else if(exp[i] == ']')
		{
			char a = pop(&mine);
			if (a == 'I' || a != '[')
			{
				valid = 0;
				printf("INVALID for ]!!");
				return valid;
			}
		}
	}

	if(pop(&mine) != 'I') // it means we still have a parenthesis in the stack
	{
		valid = 0;
		printf("INVALID, You have extra!");
	}
	if(valid == 1)
		printf("VALID");

	return valid;

} // end function checkBalance

void print_stack(struct stack* stackPtr)
{
	for (int i = 0; i <= stackPtr->top; i++)
		printf("%c-->", stackPtr->items[i]);

	printf("\n");	
}

void initialize(struct stack* stackPtr) {
     stackPtr->top = -1;
}

int push(struct stack* stackPtr, char value) {
    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {

    char retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return 'I';

    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

char* infixToPostfix(char infix[])
{
	struct stack operators;
	initialize(&operators);

	int count = 0;

	char* postfix = (char*)malloc(strlen(infix)+1 * sizeof(char));

	for(int i = 0; i < strlen(infix); i++)
	{
		if(isdigit(infix[i]))
		{
			while(isdigit(infix[i]))
			{
				postfix[count] = infix[i];
				i++;
				count++;
			}
			i--;
			postfix[count] = ' ';
			count++;
		}
		else if(isOperator(infix[i]))
		{
			if(empty(&operators))
				push(&operators,infix[i]);

			else if(priority(infix[i]) > priority(peek(&operators)))
				push(&operators, infix[i]);

			else 
			{
				while(!empty(&operators) && priority((infix[i])) <= priority(peek(&operators)) && !isParentheses(peek(&operators)))
				{
					postfix[count] = pop(&operators);
					count++;
					postfix[count] = ' ';
					count++;
				}

				push(&operators, infix[i]);
			}
		}

		else if(infix[i] == '(' || infix[i] == ')')
		{
			if(infix[i] == '(')
				push(&operators, infix[i]);
			else
			{
				while(peek(&operators) != '(')
				{
					postfix[count] = pop(&operators);
					count++;
					postfix[count] = ' ';
					count++;
				}
				pop(&operators);
			}
		}
	}

	while(!empty(&operators))
	{
		postfix[count] = ' ';
		count++;
		postfix[count] = pop(&operators);
		count++;
	}
	postfix[count] = '\0';

	return postfix;

} // end function infixToPostfix

int priority(char ch)
{
	if(ch == '(' || ch == '[' || ch == '{') 
    return 0;
	if(ch == '+' || ch == '-')
    return 1;
	if(ch == '*' || ch == '/' || ch == '%')
    return 2;
	if(ch == '^')
    return 3;

    return 0;
} // end function priority

int isOperator(char ch)
{
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%')
		return 1;
	return 0;
} // end function isOperator

int isParentheses(char ch1)
{
	if(ch1 == '{' || ch1 == '}' || ch1 == '(' || ch1 == ')' || ch1 == '[' || ch1 == ']') return 1;
	return 0;
} // end function isParenthesis
