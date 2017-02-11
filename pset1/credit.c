#include <stdio.h>
#include <cs50.h>

long long getValue();
int realCard(long long);
bool arithmetic(char number[], const int SIZE);
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
	char numberArray[20];
	const int SIZE = sprintf(numberArray, "%lld", number);
	for (int i = 0; i < SIZE; i++)
		numberArray[i]-=48;

	if (arithmetic(numberArray, SIZE))
		company(numberArray[0]);
	else 
		company(0);
	return 0;
}

// Makes arithmetic actions
bool arithmetic(char number[], const int SIZE)
{
	int sum = 0;
	int mult = 0;
	for (int i = SIZE - 2; i >= 0; i -= 2) {
		mult = number[i] * 2;
		if(mult >= 10) sum += (mult-9);
		else sum += mult;
	}
	for (int i = SIZE - 1; i >= 0; i -= 2)
		sum += number[i];
	return sum % 10 == 0;
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