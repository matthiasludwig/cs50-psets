#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main (int argc, char* argv[])
{
    string name = GetString();
    
    if (name != NULL) // check if the input is valid
    {
    
    printf("%c", toupper(name[0])); // Print the first char upperspace
    
        for (int i = 0, j = strlen(name); i < j; i++) // Go through all chars
            {
                if (name[i] == ' ')                   // And search for any spaces
                    printf("%c", toupper(name[i+1])); // Take the character after the space and print it uppercase
            }
            printf("\n");
    }
    
    
    return 0;
}
