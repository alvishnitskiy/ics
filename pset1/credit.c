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
	/*
	MAX_LENGTH - maximum length of array
	MOD        - modulo
	MIN_LENGTH - credit cards start from 13-digit numbers
	INVALID    - invalid credit card number
	*/
	enum constants {
		INVALID = 1, MOD = 10, MIN_LENGTH = 13, MAX_LENGTH = 20
	};
	int numberArray[MAX_LENGTH] = {0};
	int i = 0;
	for (; number > 0; i++) {
		numberArray[i] = number % MOD;
		number /= MOD;
	}
	const int SIZE = i;
	
	if (SIZE >= MIN_LENGTH && arithmetic(numberArray, SIZE))
		// SIZE - 1 in this case first number in credit card
		company(numberArray[SIZE - 1]);
	else 
		company(INVALID);
	return 0;
}

// Makes arithmetic actions
bool arithmetic(int number[], const int SIZE)
{
	/*
	PROD - current product
	SUM  - current sum
	MOD  - modulo
	DOUB - double the value of every second digit
	SUB  - if the result of doubling operation > 9, then subtract 9 from the product
	*/
	enum constants {
		DOUB = 2, STEP = 2, SUB = 9, MOD, PROD = 17, SUM 
	};
	for (int i = 1; i < SIZE; i += STEP) {
		number[PROD] = number[i] * DOUB;
		if (number[PROD] >= MOD)
			number[SUM] += (number[PROD] - SUB);
		else 
			number[SUM] += number[PROD];
	}
	for (int i = 0; i < SIZE; i += STEP)
		number[SUM] += number[i];
	return  number[SUM] % MOD == 0;
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