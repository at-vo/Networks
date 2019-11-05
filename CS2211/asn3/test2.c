#include <stdio.h>
#include <stdlib.h>

char get_op()
{
    char op;
    do
    {
        scanf("%c", &op);
    } while (op == ' ');

    return op;
}

float get_num()
{
    float num;
    scanf("%f", &num);
    return num;
}

float m_exp(float sub_exp, char op)
{
   if(op == '\n'|| op == '+' || op=='-'){
        ungetc(op,stdin);
        return sub_exp;
   }
    else{
        float f1;
        char op1;
        f1 = get_num();
        op1 = get_op();
        if (op=='*'){
            f1 = sub_exp * f1;
        }
        else if (op=='/'){
            f1 = sub_exp / f1;
        }
        return m_exp (f1, op1);

    }
}

float s_exp(float sub_exp, char op)
{

    if (op=='\n')
        return sub_exp;
    
    else{
        float f1 ;
        char op1 ;

        f1= m_exp(1,'*');
        op1= get_op();
        if (op=='+'){
            f1 = sub_exp + f1;
        }
        else if (op=='-'){
            f1 = sub_exp - f1;
        }    
        return s_exp(f1,op1);
    }
}

int main()
{
    int confirm = 0;
    int confirm2 = 0;

    /* while (confirm == 0)
    { */
        printf("Enter the equation you want to solve: \n");
        scanf("");

          float num = get_num();
          char op = get_op();

        float ans = s_exp(0, '+');
        printf("%f\n", ans);
/* 
        while (confirm2 == 0)
        {
            char userInput;
            printf("Would you like to continue? (Y/N): ");
            scanf(" %c", &userInput);
            if ((int)userInput < 123 && (int)userInput > 96)
            {
                userInput -= 32;
            }
            if (userInput == 'N')
            {
                confirm = 1;
                confirm2 = 1;
            }
            else if (userInput == 'Y')
                confirm2 = 1;
            else if (userInput != 'N' && userInput != 'Y')
            {
                printf("invalid input.\n");
            }
        } 
        }
        */
    

    return 0;
}