/**
 * Dat Vo 250983323
 * */
#include <stdio.h>
#include <stdlib.h>

/* returns the next operator of the expression */
char get_op()
{
    char op;
    do
    {
        scanf("%c", &op); // gets next operand
    } while (op == ' ');
    if (!(op == '+' || op == '-' || op == '*' || op == '/' || op == '\n')) // check for correct operand
        exit(EXIT_FAILURE);
    
    return op;
}

/* returns the next numeric value of the expression */
float get_num()
{
    float num;
    scanf("%f", &num);
    return num;
}

/* m_exp function returns the value of the current m_expression */
float m_exp(float sub_exp, char op)
{
    if (op == '\n' || op == '+' || op == '-')
    {
        ungetc(op, stdin);
        return sub_exp;
    }
    else 
    {
        float nextNum = get_num();
        char nextOp = get_op();

        /* recursive calls */
        if (op == '*')
            return  m_exp(sub_exp * nextNum, nextOp);
        else if (op == '/')
            return m_exp(sub_exp / nextNum, nextOp);
    }
}

/* s_exp function returns the value of the s_expression */
float s_exp(float sub_exp, char op)
{
    if (op == '\n')
    {
        return sub_exp;
    }
    else
    {
        float nextNum = m_exp(1, '*'); // calls m_exp for next number
        char nextOp = get_op();
        /* recursive calls */
        if (op == '+')
            return s_exp(sub_exp + nextNum, nextOp);
        else if (op == '-')
            return s_exp(sub_exp - nextNum, nextOp);
    }
}
/**
 * Main function
 */
int main()
{
    
    int confirm = 0;
    int confirm2 = 0;

    while (confirm == 0)
    {
        printf("Enter the equation you want to solve: \n");
        scanf("");

        float ans = s_exp(0, '+');
        printf("%f\n", ans);

        while (confirm2 == 0)
        {
            /* User continue confirmation */
            char userInput;
            printf("Would you like to continue? (Y/N): ");
            scanf(" %c", &userInput);
            if ((int)userInput < 123 && (int)userInput > 96)
            {
                userInput -= 32; // change input to uppercase
            }
            if (userInput == 'N') // breaks both loops
            {
                confirm = 1;
                confirm2 = 1;
            }
            else if (userInput == 'Y')
                confirm2 = 1; // breaks inner loop
            else if (userInput != 'N' && userInput != 'Y')
            {
                printf("invalid input.\n");
            }
        }
        confirm2=0; // resets inner loop
    }

    return 0;
}