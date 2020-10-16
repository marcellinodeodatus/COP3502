// Deodatus Marcellino
// 9/30/2020
// Written in COP 3502 to illustrate an array implementation of a stack.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.

#define SIZE 100
#define EMPTY 'I'

typedef struct stack
{

    char items[SIZE];
    int top;
} stack;

stack sta;

// ================================= Function Prototype ====================================== //
void initialize(struct stack *stackPtr);
int full(struct stack *stackPtr);
char push(struct stack *stackPtr, int value);
int empty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
char top(struct stack *stackPtr);
void display(struct stack *stackPtr);
int checkBalance(char exp[]);
int priority(char ch);              //returns the priority of a given operator.
int isOperator(char ch);            //check whether it is an operator.
char *infixToPostfix(char infix[]); // convert a given infix into postfix.
int isParentheses(char ch1);        // Check is it a parenthesis or not.

int main()
{
    char expression[SIZE];
    printf("\n enter expression: ");
    scanf("%[^\n]s", expression);

    int valid = checkBalance(expression);
    if (valid)
    {
        printf("\nit's Valid! :)");
        char *postfix = infixToPostfix(expression);
        printf("The postfix is: %s\n", postfix);
        free(postfix);
    }
    else
    {
        printf("\n Parenthesis imbalanced\n");
    }

    return 0;
}

void initialize(struct stack *stackPtr)
{
    stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
char push(struct stack *stackPtr, int value)
{

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top + 1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack *stackPtr)
{
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack *stackPtr)
{
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack *stackPtr)
{

    int retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char top(struct stack *stackPtr)
{

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

void display(struct stack *stackPtr)
{
    printf("\nPrinting the Current stack...");
    for (int i = 0; i <= stackPtr->top; i++)
        printf("%d ", stackPtr->items[i]);
}

// Read the string char by char left to right.
// If you see a (, [, or {, push it on the stack
// if you see a ), ], or }, pop the stack and check whether you got the corresponding (, [, or {
// when you reach the end, check that the stack is empty. If it is empty, it is balanced.
int checkBalance(char exp[])
{
    stack checker;
    initialize(&checker);

    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '{' || exp[i] == '[' || exp[i] == '(')
        {
            push(&checker, exp[i]);
        }
        else if (exp[i] == '}' || exp[i] == ']' || exp[i] == ')')
        {
            char popped = pop(&checker);
            if (exp[i] == ']' && popped != '[')
            {
                return 0;
            }
            else if (exp[i] == ')' && popped != '(')
            {
                return 0;
            }
            else if (exp[i] == '}' && popped != '{')
            {
                return 0;
            }
        }
    }

    if (empty(&checker) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

    return empty(&checker);
}

int priority(char ch)
{
    if (ch == '(' || ch == '[' || ch == '{')
        return 0;
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    if (ch == '^')
        return 3;
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '^' || ch == '%');
}

int isParentheses(char ch1)
{
    return (ch1 == '{' || ch1 == '}' || ch1 == '(' || ch1 == ')' || ch1 == '[' || ch1 == ']');
}

char *infixToPostfix(char infix[])
{

    char *postfix = calloc(strlen(infix) + 1, sizeof(char));
    int pIndex = 0;
    stack operators;
    initialize(&operators);

    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]))
            {
                postfix[pIndex] = infix[i];
                pIndex++;
                i++;
            }
            i--;
            postfix[pIndex] = '\0';
            pIndex++;
        }
        else if (isOperator(infix[i]))
        {
            if (empty(&operators))
            {
                push(&operators, infix[i]);
            }
            else
            {
                char op = top(&operators);
                if (priority(infix[i]) > priority(op))
                {
                    push(&operators, infix[i]);
                }
                else
                {
                    while (!empty(&operators) && priority(op) >= priority(infix[i]) && !isParentheses(op))
                    {
                        postfix[pIndex++] = pop(&operators);
                        postfix[pIndex++] = '\0';
                        postfix[pIndex++] = '\0';
                        op = top(&operators);
                    }
                    push(&operators, infix[i]);
                }
            }
        }
        else if (infix[i] == '(')
        {
            push(&operators, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top(&operators) != '(')
            {
                postfix[pIndex++] = pop(&operators);
                postfix[pIndex++] = '\0';
            }
            pop(&operators);
        }
    }
    while (!empty(&operators))
    {
    }
    postfix[pIndex] = '\0';
    return postfix;
}