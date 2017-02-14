#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

void extractInitials(const char*);

// more comfortable
int main(void)
{
    const char* s = get_string();
    if (s != NULL)
        extractInitials(s);
    return 0;
}

// Extract initials from giving string
void extractInitials(const char* p)
{
    bool canPrint = true;
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // The first letter can be printed
        if (isalpha(p[i])) {
            if (canPrint) {
                printf("%c", toupper(p[i]));
                canPrint = false; 
            }
        }
        // The first letter after non-letter symbol can be printed
        else
            canPrint = true;
    }
    printf("\n");
}