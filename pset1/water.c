#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Bottles of water per minute
    const int BOTTL_PER_MIN = 12;
    int minutes = 0;
    printf("How many minutes you spent in the shower?\n");
    minutes = get_int();
    int bottles = minutes * BOTTL_PER_MIN;
    printf("Minutes: %i\n"
		   "Bottles: %i\n", minutes, bottles);
}