#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <assert.h>

void checker(const char*);
void counter(int*, int);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    const char *password = argv[1];
    checker(password);
    return 0;
}

// Setting parameters and check password
void checker(const char *password)
{
    /*
    SALT       - two characters
    RIGHT_ELEM - right element of array
    ALL_ELEM   - all elements of array
    KEY_ELEM   - all elements of array + \0
    ALPHABET   - letters in alphabet
    O_CAPITAL  - character before capital letters
    O_SMALL    - character before small letters
    */
    enum constants {
        SALT = 2, RIGHT_ELEM = 3, ALL_ELEM = 4, KEY_ELEM = 5, 
        ALPHABET = 26, O_CAPITAL = 64, O_SMALL = 96
    };
    // Initialization from 1 ('A')
    int coun[] = { 0, 0, 0, 1 };
    assert(coun[RIGHT_ELEM] > 0);
    while(coun[RIGHT_ELEM] > 0) {
        char key[KEY_ELEM] = "";
        char cc;
        for (int i = 0; i < ALL_ELEM; i++ )
        {
            if(coun[i] > 0){
                if(coun[i] > ALPHABET)
                    cc = O_SMALL + coun[i] - ALPHABET; // '`'
                else
                    cc = O_CAPITAL + coun[i]; // '@'
                strncat(key, &cc, 1);
            }
        }
        printf("%s\n", key);
        char salt[SALT];
        strncpy(salt, password, SALT);
        char *cipher = crypt(key, salt);
        if (strcmp(cipher, password) == 0){
            printf("%s\n", key);
            break;
        }
        counter(coun, RIGHT_ELEM);
    }
}

// Recursive character counter
void counter(int *coun, int curElem)
{
    /*
    ALL_ELEM        - all elements of array
    DOUBLE_ALPHABET - capital and small letters
    */
    enum constants {
        ALL_ELEM = 4 , DOUBLE_ALPHABET = 53
    };
    int digTrans = 0;
    digTrans = (++coun[curElem]) / DOUBLE_ALPHABET;
    coun[curElem] = (coun[curElem]++) % DOUBLE_ALPHABET;
    if(digTrans > 0) {
        if(curElem == 0) 
            for(int i = 0; i < ALL_ELEM; i++ )
                coun[i] = 0;
        else {
            coun[curElem]++;
            curElem--;
            counter(coun, curElem);
        }
    }
}