#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include <cs50.h>

void cryptography(int, const char*);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    // "No need to check that it’s indeed numeric."
    int key = atoi(argv[1]);
    printf("plaintext: ");
    const char* s = get_string();
    if (s != NULL)
        cryptography(key, s);
    
    return 0;
}

// encrypting
void cryptography(int k, const char* p)
{
    // formula is c[i] = ( p[i] + k ) mod 26
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // isalpha() ???
        printf("%c", p[i] + k); // mod 26 ???
    }
    printf("\n");
}