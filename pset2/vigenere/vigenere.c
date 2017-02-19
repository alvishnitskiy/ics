#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

char* getValue(void);
bool checkValue(char* userValue);
void cryptography(char*, char*);
int changeAlph(char);
char changeAlphASCII(int, char);

int main(int argc, string argv[])
{
    if (argc != 2 || !checkValue(argv[1]))
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    cryptography(argv[1], getValue());
    return 0;
}

// Get plaintext from user
char* getValue(void)
{
	printf("plaintext: ");
	char* s = get_string();
    if (s != NULL)
        return s;
	else
	    return "";
}

// Check user input
bool checkValue(char* userValue)
{
	for (int i = 0, n = strlen(userValue); i < n; i++ ){
	    if(!isalpha(userValue[i]))
	        return false;
	}
    return true;
}

// encrypting by formula c[i] = (p[i] + k[j]) mod 26
void cryptography(char* k, char* p)
{
    enum constants { UPP_CASE = 0, LOW_CASE = 1, MAX_SIZE = 30 };
    const int SIZE = strlen(k);
    int keyInt[MAX_SIZE];
    for (int i = 0; i < SIZE; i++ ){
        keyInt[i] = changeAlph(k[i]);
    }
    printf("ciphertext: ");
    int j = 0;
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if(isalpha(p[i])) {
            printf("%c", changeAlphASCII(keyInt[j], p[i]));
            j = (j + 1) % SIZE;
        }
        else
            printf("%c", p[i]);
    }
    printf("\n");
}

// To alphabet change
int changeAlph(char sym)
{
    enum constants {
        DIFF_CASE = 32, A_ASCII = 65
    };
    if(islower(sym)) {
        // In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
        sym -= DIFF_CASE;
    }
    // In the case of capital letters 65 ('A') is deducted
    sym = sym - A_ASCII;
    return sym;
}

// ASCII => alphabet change => ASCII
char changeAlphASCII(int k, char sym)
{
    enum constants {
        ALPHABET = 26, DIFF_CASE = 32, A_ASCII = 65
    };
    int letterСase = 0;
    if(islower(sym)) {
        letterСase = 1;
        // In the case of small letters 65 ('A') and 32 ('A'...'a') are deducted
        sym -= DIFF_CASE;
    }
    // In the case of capital letters 65 ('A') is deducted
    sym = (sym - A_ASCII + k) % ALPHABET;
    sym += A_ASCII;
    // Back to small letters
    if(letterСase)
        return sym += DIFF_CASE;
    // For capital letters
    return sym;
}