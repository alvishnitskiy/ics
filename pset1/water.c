#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes;
    printf("How many minutes you spent in the shower?\n");
    minutes = get_int();
    int bottles = minutes * 12;
    printf("Minutes: %i\n"
		   "Bottles: %i\n", minutes, bottles);
}