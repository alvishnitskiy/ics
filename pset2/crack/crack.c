#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

void main2(const char*);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    main2(argv[1]);
    /*
    charArray[97-122, 65-90];
    const int SIZE; // 26 + 26
    cycle(0,0,0,SIZE) ? 
        OK : cycle(0,0,SIZE,SIZE) ? 
            OK : cycle(0,SIZE,SIZE,SIZE) ? 
                OK : cycle(SIZE,SIZE,SIZE,SIZE) ? OK : NULL
    cycle(0,0,0,SIZE) // 4 dimension
    for (d = 0; d < SIZE; d++)
    {
        for (c = 0; c < SIZE; c++)
        {
            for (b = 0; b < SIZE; b++)
            {
                for (a = 0; a < SIZE; a++)
                {
                    check(abcd);
                    // recursion ???
                }
            }
        }
    }
    */
    return 0;
}

// ???
void main2(const char *s)
{
    char *key = "rofl";
    char salt[2];
    strncpy(salt, s, 2);
    char *cipher = crypt(key, salt);
    if (strcmp(cipher, s) == 0)
        printf("%s\n", key);
}