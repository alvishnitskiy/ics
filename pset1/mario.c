#include <stdio.h>
#include <cs50.h>

int getValue();
bool checkValue(int);
void createPyramids(int);
void printChar(int, const char*);
/*void printSpaces(int);
void printHashes(int);*/

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
	if(userValue < 0 || userValue > 23)
	{
	    printf("Your value must be between 0 and 23.\n");
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
	for (int lines = 0; lines < height; lines++) {
		printChar(height - lines - 1, " "); //printSpaces(height - lines - 1);
		printChar(lines + 1, "#");			//printHashes(lines + 1);
		printChar(GAP, " ");				//printSpaces(GAP);
		printChar(lines + 1, "#");			//printHashes(lines + 1);
		printf("\n");
	}
}

// Print any symbol multiple times
void printChar(int count, const char* sym)
{
	for (int c = 0; c < count; c++)
		printf("%s", sym);
}

// Print spaces multiple times
/*void printSpaces(int count)
{
	for (int c = 0; c < count; c++)
		printf("%s", " ");
}

// Print hashes multiple times
void printHashes(int count)
{
	for (int c = 0; c < count; c++)
		printf("%s", "#");
}*/