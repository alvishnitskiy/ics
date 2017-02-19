#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

char* getValue(void);
void extractInitials(char*);

// more comfortable
int main(void)
{
    extractInitials(getValue());
    return 0;
}

// Get name from user
char* getValue(void)
{
	char* s = get_string();
    if (s != NULL)
        return s;
	else
	    return "";
}

// Extract initials from giving string
void extractInitials(char* p)
{
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i])) {
            if (i == 0 || !isalpha(p[i - 1])) 
                printf("%c", toupper(p[i]));
        }
    }
    printf("\n");
}