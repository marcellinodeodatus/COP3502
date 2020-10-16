#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

//Stack definition
typedef struct stack
{
    int st[MAX];
    int top;
} stack;

stack stk;

//function prototype
void push(int x);
int pop();
int peek();
void evaluate(char *postFix);
char *convertTpPostfix(char *input);
int convertToInt(char c);
char *menu();
int calculate(int a, int b, char op);
int getOperatorPriority(char c);
int isOperator(char c);
int isBalancedParenthesis(char *s);
char *convertToPostfix(char *input);

//main function
int main(void)
{
    char *str, *postFix;

    while (strcmp(str = menu(), "exit") != 0)
    {
        if (isBalancedParenthesis(str))
        {
            postFix = convertToPostfix(str);
            printf("Postfix expression: %s\n", postFix);
            evaluate(postFix);
        }
        else
            printf("Parenthesis imbalanced\n");
    }

    return 0;
}

//function to evaluate the postfix expression
void evaluate(char *b)
{
    stk.top = -1;

    int i, x;
    for (i = 0; b[i] != '\0'; i++)
    {
        char c = b[i];

        if (c == ' ')
            continue;
        if (isOperator(c))
        {
            int o2 = pop();
            int o1 = pop();
            x = calculate(o1, o2, c);
            push(x);
        }
        else
        {
            x = 0;
            do
            {
                x = x * 10 + convertToInt(c);
                c = b[++i];
            } while (isdigit(c));
            i--;
            push(x);
        }
    }

    printf("Evaluation: %d\n", pop());
}

//function to convert from infix to postfix expression
char *convertToPostfix(char *input)
{
    char *output;
    stk.top = -1;

    output = (char *)malloc(MAX);
    push('(');
    strcat(input, ")");

    int i, j = 0;

    for (i = 0; input[i] != '\0'; i++)
    {
        if (isdigit(input[i]))
        {
            do
            {
                output[j] = input[i];
                j++;
                i++;
            } while (isdigit(input[i]));
            i--;
            output[j++] = ' ';
        }
        else if (input[i] == '(')
        {
            push('(');
        }
        else if (input[i] == ')')
        {
            while (peek() != '(')
            {
                output[j] = pop();
                j++;
            }
            pop();
        }
        else
        {
            int p1 = getOperatorPriority(input[i]);
            int p2 = getOperatorPriority(peek());

            while (p1 <= p2)
            {
                output[j] = pop();

                j++;
                p2 = getOperatorPriority(peek());
            }
            push(input[i]);
        }
    }

    output[j] = '\0';

    return output;
}

//function to display menu
char *menu()
{
    char *str, ch;
    char infix[100];

    printf("\n*** Menu ***");
    printf("\ne for entering an infix expression");
    printf("\nx for exiting the program");
    printf("\nEnter option: ");
    scanf(" %c", &ch);
    if (ch == 'e')
    {
        printf("Enter an infix expression: ");
        scanf("%s", infix);

        str = (char *)malloc(strlen(infix) + 1);
        strcpy(str, infix);

        return str;
    }
    else if (ch == 'x')
    {
        free(str);
        return "exit";
    }
}

//function to check for Balanced Parenthesis
int isBalancedParenthesis(char *s)
{
    stk.top = -1;

    for (int i = 0; s[i] != '\0'; i++)
    {
        switch (s[i])
        {
        case '(':
        case '{':
        case '[':
            push(s[i]);
            break;
        case ')':
            if (stk.top == -1)
                return 0;
            if (peek() == '(')
                pop();
            break;
        case '}':
            if (stk.top == -1)
                return 0;
            if (peek() == '{')
                pop();
            break;
        case ']':
            if (stk.top == -1)
                return 0;
            if (peek() == '[')
                pop();
            break;
        }
    }
    if (stk.top == -1)
        return 1;

    return 0;
}

//function to check operator
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}

//function to get Priority of an operator
int getOperatorPriority(char c)
{
    switch (c)
    {
    case '(':
        return 0;

    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;

    default:
        return 999;
    }
}

//function to convert char to int
int convertToInt(char c)
{
    return c - '0';
}

//function to calculation
int calculate(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    }
}

//push function
void push(int x)
{
    if (stk.top == MAX - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stk.st[++stk.top] = x;
}

//pop function
int pop()
{
    if (stk.top == -1)
    {
        printf("Stack underflow\n");
        return 0;
    }
    return stk.st[stk.top--];
}

//peek function
int peek()
{
    return stk.st[stk.top];
}