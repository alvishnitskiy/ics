#include <stdio.h>
#include <cs50.h>

int getValue();
bool checkValue(int);
void createPyramids(int);
void printChar(int, const char*);

//more comfortable
int main(void)
{
	createPyramids(getValue());
	return 0;
}

// Get height from user
int getValue()
{
    int input = 0;
	printf("Which must be the half-pyramids' heights?\n");
	do {
		input = get_int();
	} while (!checkValue(input));
	return input;
}

// Check user input
bool checkValue(int userValue)
{
	const int MAX_HEIGHT = 23;
	if(userValue < 0 || userValue > MAX_HEIGHT)
	{
	    printf("Your value must be between 0 and %i.\n", MAX_HEIGHT);
	    return false;
	}
    else
    {
        return true;
    }
}

// View, so to speak
void createPyramids(int height)
{
	const int GAP = 2;
	for (int lines = 1; lines <= height; lines++) {
		printChar(height - lines , " ");
		printChar(lines, "#");
		printChar(GAP, " ");
		printChar(lines, "#");
		printf("\n");
	}
}

// Print any symbol multiple times
void printChar(int count, const char* sym)
{
	for (int c = 0; c < count; c++)
		printf("%s", sym);
}