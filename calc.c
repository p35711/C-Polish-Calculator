#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

#define BUFFER_SIZE 100

#define MAXVAL 100

char buf[BUFFER_SIZE];
int buffer_position = 0;

int getch(void)
{
    return (buffer_position > 0 ? buf[--buffer_position] : getchar());
}

void ungetch(int c)
{
    if (buffer_position >= BUFFER_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[buffer_position++] = c;
}

int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == ',')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;

}

int stack_position = 0;
char val[MAXVAL];

void push(double f)
{
    if(stack_position < MAXVAL) {
        val[stack_position++] = f;
    }
    else
        printf("error: stack is full, cannot push %g\n", f);
}

double pop(void)
{
    if (stack_position > 0)
        return val[--stack_position];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void printstack(void) /* Exercise 4-4 */
{
    if(stack_position > 0)
    {
        int i = stack_position;
        printf("\nstack: ");
        for(; i >= 0;--i)
           printf("[%i]:%d ", i, val[i]);  
    }
    
    printf("\n");
    

}

/* Reverse Polish Calculator */

int main(int argc, char **argv)
{
    int type;
    double op2;
    char s[MAXOP];
  
    while ((type = getop(s)) != EOF) {
         printf("%s ", s);
         
        switch(type) {       
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push (pop() + pop());
                break;
            case '*':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / - op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':   /* Exercise 4-3 */
            	  op2 = pop();
            	  push((int)pop() % (int)op2);
            	  break;
            case 'p':   /* Exercise 4-4 */
                 printstack();
                 break;
            case '\n':
                printf("equals: %.8g\n", pop());
                break;
            default:
                printf("error: unknown command [%s]\n", s);
                break;
        }
    }
    return 0;
}
