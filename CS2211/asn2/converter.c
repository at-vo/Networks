#include <stdio.h>

/* Define Constants */
const float K_TO_M = 0.621371;
const float M_TO_K = 1.609344;
const float M_TO_F = 3.28084;
const float F_TO_M = 0.3048;
const float C_TO_I = 0.393701;
const float I_TO_C = 2.54;
const float FREEZING_PT = 32.0;
const float TEMP_CONVERT = ((float)9 / (float)5);
const int VALID = 1;
const int TERMINATE = 1;
const int MIN = 1;
const int MAX = 5;
const int INITIAL = 0;

int main()
{

	/* Define Variables */
	int option, optionCheck, valueCheck = INITIAL;
	char inputChar;
	float inputValue;

	/* Initialize loop to return to (1) */
	while (optionCheck == INITIAL)
	{
		printf("enter option between 1 and 5: \n");
		scanf(" %d", &option);
		if (option > MAX || option < MIN) // dealing with invalid user input for (1)
		{
			printf("invalid input\n");
		}

		/* Switch cases for option */
		switch (option)
		{

		/* If User input is 1 */
		case 1:

			printf("K: Kilometer to Mile \n");
			printf("M: Kilometer to Mile \n");
			while (valueCheck == INITIAL) // loop to deal with invalid character input
			{
				printf("enter K or M: \n");
				scanf(" %c", &inputChar);

				if (inputChar == 'K' || inputChar == 'k') // checks for valid character case
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = inputValue * K_TO_M;
					printf("conversion from Kilometer to Mile: %.2f\n", inputValue);
					valueCheck = VALID; // confirms valid character input
				}
				else if (inputChar == 'M' || inputChar == 'm')
				{
					printf("enter a value: ");
					scanf("%f", &inputValue);
					inputValue = inputValue * M_TO_K;
					printf("conversion from Mile to Kilometer: %.2f\n", inputValue);
					valueCheck = VALID;
				}

				else
				{
					printf("invalid input. \n");
				}
			}

			break;

		/* If user input is 2 */
		case 2:
			printf("M: Meter to Feet \n");
			printf("F: Feet to Meter \n");
			while (valueCheck == INITIAL)
			{
				printf("enter M or F: ");
				scanf(" %c", &inputChar);

				if (inputChar == 'M' || inputChar == 'm')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = inputValue * M_TO_F;
					printf("conversion from Meters to Feet: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else if (inputChar == 'F' || inputChar == 'f')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = inputValue * F_TO_M;
					printf("conversion from Feet to Meters: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else
				{
					printf("invalid input. \n");
				}
			}
			break;

		/* If user input is 3 */
		case 3:
			printf("C: Centimeter to Inch \n");
			printf("I: Inch to Centimeter \n");
			while (valueCheck == INITIAL)
			{
				printf("enter C or I: ");
				scanf(" %c", &inputChar);

				if (inputChar == 'C' || inputChar == 'c')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = inputValue * C_TO_I;
					printf("conversion from Centimetre to Inch: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else if (inputChar == 'I' || inputChar == 'i')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = inputValue * I_TO_C;
					printf("conversion from Inch to Centimetre: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else
				{
					printf("invalid input. \n");
				}
			}
			break;

		/* If user input is 4 */
		case 4:
			printf("C: Celcius to Farenheit \n");
			printf("F: Farenheit to Celcius \n");
			while (valueCheck == INITIAL)
			{

				printf("enter C or F: ");
				scanf(" %c", &inputChar);

				if (inputChar == 'C' || inputChar == 'c')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					getchar();
					inputValue = (inputValue * TEMP_CONVERT) + FREEZING_PT;
					printf("conversion from Celsius to Fahrenheit: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else if (inputChar == 'F' || inputChar == 'f')
				{
					printf("enter a value: ");
					scanf(" %f", &inputValue);
					inputValue = (inputValue - FREEZING_PT) / TEMP_CONVERT;
					printf("conversion from Fahrenheit to Celsius: %.2f\n", inputValue);
					valueCheck = VALID;
				}
				else
				{
					printf("invalid input. \n");
				}
			}

			break;

		/* If user input is 5 */
		case 5:
			optionCheck = TERMINATE; // terminates
			break;
		}
		valueCheck = 0; // resets valid character check
	}
	return 0;
}