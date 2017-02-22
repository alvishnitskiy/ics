#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

char* getPlainText(void);
void encryptMessage(int, char*);
char changeAlphASCII(int, char);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    // "No need to check that it’s indeed numeric."
    int key = atoi(argv[1]);
    encryptMessage(key, getPlainText());
    return 0;
}

// Get plaintext from user
char* getPlainText(void)
{
	printf("plaintext: ");
	char* s = get_string();
	
    if (s != NULL) {
        return s;
    }
	else {
	    return "";
	}
}

// encrypting by formula c[i] = (p[i] + k) mod 26
void encryptMessage(int k, char* p)
{
    enum constants { 
        UPP_CASE = 0, LOW_CASE = 1 
    };
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++) {
        if(isalpha(p[i])) {
            printf("%c", changeAlphASCII(k, p[i]));
        }
        else {
            printf("%c", p[i]);
        }
    }
    printf("\n");
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
    if(letterСase) {
        return sym += DIFF_CASE;
    }
    // For capital letters
    return sym;
}