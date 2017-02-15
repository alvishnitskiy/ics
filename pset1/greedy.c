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
    printf("%i", countCoins(money, coins));
    printf("\n");
}

// Recursive calculation of the number of coins
int countCoins(int money, int *coins)
{
    const int COINS_TYPE = 4;
    int change = 0;
    int coin = 0;
    for (int i = 0; i < COINS_TYPE; i ++)
    {
        if ((money - coins[i]) >= 0)
        {
            coin = coins[i];
            break;
        }
    }
    change = (int) (money / coin);
    money = money % coin;
    if (money > 0)
        return change + countCoins(money, coins);
    else
        return change;
}