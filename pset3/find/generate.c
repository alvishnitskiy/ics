/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    /*If program is executed without any command-line 
    arguments or with more than two, it should print 
    an error message and return a value of 1 immediately.*/
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    /*To indicate how many pseudorandom numbers user 
    like to generate, program converts argument from 
    string to an actual int.*/
    int n = atoi(argv[1]);

    /*If program is executed with two command-line arguments, 
    second argument is used by srand48 to initialize the 
    generation of pseudorandom numbers. Otherwise, for this 
    purpose, is used time(NULL). It returns the current calendar 
    time. In both cases, argument of srand48 will be long integer.*/
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    /*Before printing each value that is returned by drand48 
    would be incrised on upper limit on range of integers.*/
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
