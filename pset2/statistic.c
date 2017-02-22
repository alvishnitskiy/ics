/*
спросить у человека строку, надо посчитать количество вхождений каждой буквы и вывести статистику,
например: vvedi stroku: hello WORLD
L - 3
O - 2
H - 1
E - 1
W - 1
R - 1
D - 1  
(читать про пузырьковую сортировку)
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

char* getTextLine(void);
void calculation(int letters[][2], char*);
void assign(int [], int);
void bubbleSort(int [][2]);
void printResults(int [][2]);

 int main(void)
 {
    /*
    DIMENSION  - 2 dimention: letters and values
    ALPHABET   - letters in alphabet
    */
    enum constants {
        DIMENSION = 2, ALPHABET = 26
    };
    int letters [ALPHABET][DIMENSION];
    for(int i = 0; i < ALPHABET; i++ ) {
        letters [i][0] = letters [i][1] = 0;
    }
    
    calculation(letters, getTextLine());
    bubbleSort(letters);
    printResults(letters);
    return 0;
 }

// Get a line of text from the user
char* getTextLine(void)
{
    printf("Eenter the string: ");
    char* userString = get_string();
    
    if (userString != NULL) {
        return userString;
    }
    else {
        exit(1);
    }
}

// Make statistical calculations
void calculation(int letters[][2], char* userString)
{
    int letter = 0;
    for (int i = 0; userString[i] != '\0'; i++ ) {
        letter = (int)toupper(userString[i]);
        if(i == 0) {
            assign(letters[0], letter);
        }
        else if(i != 0) {
            for(int l = 0; letters [l][0] != 0; l++) {
                if(letters [l][0] == letter) {
                    letters [l][1] += 1;
                    break;
                }
                else if(letters [l + 1][0] == 0) {
                    l++;
                    assign(letters[l], letter);
                };
            }
        }
    }
}

// Assigning values
void assign(int letters[], int letter)
{
    letters[0] = letter;
    letters[1] = 1;
}

// Bubble sorting of array
void bubbleSort(int letters[][2])
{
    enum constants {
        DIMENSION = 2, ALPHABET = 26
    };
    int x, curElem[DIMENSION], permutation;

    do {
        permutation = 0;
        for (x = 1; x < ALPHABET; x++ ) {
            if (letters[x - 1][1] < letters[x][1]) {
                
                curElem[0] = letters[x][0];
                curElem[1] = letters[x][1];
                
                letters[x][0] = letters[x - 1][0];
                letters[x][1] = letters[x - 1][1];
                
                letters[x - 1][0] = curElem[0];
                letters[x - 1][1] = curElem[1];
                
                permutation = 1;
            };
        }
    } while (permutation);
}

// View, so to speak
void printResults(int letters[][2])
{
    const int ALPHABET = 26;
    for (int i = 0; i < ALPHABET; i++ ) {
        if (isalpha(letters [i][0])) {
            printf("%c - %i\n", letters [i][0], letters [i][1]);
        }
    }
}