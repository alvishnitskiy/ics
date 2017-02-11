#include <stdio.h>
#include <cs50.h>

long long getValue();
int realCard(long long);
bool arithmetic(int [], const int);
void company(int);

int main(void)
{
	realCard(getValue());
	return 0;
}

// Get credit card number from user
long long getValue()
{
    long long input = 0;
	printf("Enter your credit card number.\n");
	do {
		input = get_long_long();
	} while (input == 0);
	return input;
}

// Setting parameters
int realCard(long long number)
{
	int numberArray[20] = {0};
	int i = 0;
	for (; number > 0; i++) {
		numberArray[i] = number % 10;
		number /= 10;
	}
	const int SIZE = i;

	if (SIZE > 12 && arithmetic(numberArray, SIZE))
		company(numberArray[SIZE - 1]);
	else 
		company(0);
	return 0;
}

// Makes arithmetic actions
bool arithmetic(int number[], const int SIZE)
{
	/*int sum = 0;
	int mult = 0;*/
	for (int i = 1; i < SIZE; i += 2) {
		number[17] = number[i] * 2;			//mult = number[i] * 2;
		if (number[17] >= 10)				//if(mult >= 10) 
			number[18] += (number[17] - 9);		//sum += (mult-9);
		else 
			number[18] += number[17];			//sum += mult;
	}
	for (int i = 0; i < SIZE; i += 2)
		number[18] += number[i];				//sum += number[i];
	return  number[18] % 10 == 0;			//sum % 10 == 0;
}

// Define payment cards company
void company(int first)
{
	enum cardsCompany { AMEX = 3, VISA, MASTERCARD };
	switch (first)
	{
	case AMEX:
		printf("AMEX\n");		break;
	case VISA:
		printf("VISA\n");		break;
	case MASTERCARD:
		printf("MASTERCARD\n");	break;
	default:
		printf("INVALID\n");	break;
	}
}