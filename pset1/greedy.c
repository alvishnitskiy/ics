#include <stdio.h>
#include <math.h>
#include <cs50.h>

int getValue(void);
bool checkValue(float);
void giveChange(int);
int countCoins(int, int*);

int main(void)
{
    giveChange(getValue());
    return 0;
}

// Get query of user change
int getValue(void)
{
    // Round to integers
    const int TO_INT = 100;
    float input = 0;
	printf("O hai! How much change is owed?\n");
	do {
		input = get_float();
	} while (!checkValue(input));
	// Further operate with integer values
	return (int) round(input * TO_INT);
}

// Check user input
bool checkValue(float userValue)
{
	if(userValue <= 0)
	{
	    printf("How much change is owed?\n");
	    return false;
	}
    else
    {
        return true;
    }
}

// Setting parameters
void giveChange(int money)
{
    enum coinsNames { QUARTER = 25, DIME = 10, NICKEL = 5, PENNY = 1 };
    int coins [] = { QUARTER, DIME, NICKEL, PENNY };
    
    printf("%i", countCoins(money, &coins[0]));
    printf("\n");
}

// Recursive calculation of the number of coins
int countCoins(int money, int *coins)
{
    int change = 0;
    change = (int) (money / *coins);
    money %= *coins;
    
    if (money > 0)
        return change + countCoins(money, ++coins);
    return change;
}