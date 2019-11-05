/**
 * Dat Vo 250983323
 * */
#include <stdio.h>

/* Initialize constants */
const char segments[10][3][3] = {
    // top            // mid            // bot
    {{' ', '_', ' '}, {'|', ' ', '|'}, {'|', '_', '|'}}, // 0
    {{' ', ' ', ' '}, {' ', ' ', '|'}, {' ', ' ', '|'}}, // 1
    {{' ', '_', ' '}, {' ', '_', '|'}, {'|', '_', ' '}}, // 2
    {{' ', '_', ' '}, {' ', '_', '|'}, {' ', '_', '|'}}, // 3
    {{' ', ' ', ' '}, {'|', '_', '|'}, {' ', ' ', '|'}}, // 4
    {{' ', '_', ' '}, {'|', '_', ' '}, {' ', '_', '|'}}, // 5
    {{' ', '_', ' '}, {'|', '_', ' '}, {'|', '_', '|'}}, // 6
    {{' ', '_', ' '}, {' ', ' ', '|'}, {' ', ' ', '|'}}, // 7
    {{' ', '_', ' '}, {'|', '_', '|'}, {'|', '_', '|'}}, // 8
    {{' ', '_', ' '}, {'|', '_', '|'}, {' ', '_', '|'}}  // 9
};
const int numArray = 12;
const int middle = 1;

/* display function takes user input and displays in 7 segment format */
void display()
{
    char nums[numArray];
    int get; // gets the inputted value
    int count = 0; // keeps track of how many elements in nums array

    printf("enter input: ");
    scanf("%d", &get);
    sprintf(nums, "%d", get); // places int value into nums array
    while (nums[count] != '\0')
    {
        count++;
    }

    for (int i = 0; i < 3; i++) // rows
    {
        for (int j = 0; j < count; j++) // columns
        {
            /* displays negative */
            if (get < 0)
            {
                if (j == 0 && i != middle)
                    printf(" ");
                else if (j == 0 && i == middle)
                    printf("_");
            }
            /* displays the  */
            for (int k = 0; k < 3; k++)
                printf("%c", segments[nums[j] - '0'][i][k]);
        }
        printf("\n");
    }
}

int main()
{
    int confirm = 0;
    int confirm2 = 0;

    while (confirm == 0)
    {
        display();

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