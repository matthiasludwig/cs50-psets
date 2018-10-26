#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encrypt(string, int k);

int main (int argc, char* argv[])
{
    int k;
    
    /*Get the command line-argument and convert from string to int
    If no argument is provided return 1 and printf error message*/
    
    if (argc == 2)
    {
        k = atoi(argv[1]);
        k = k % 26; // Makes sure that the key is between 0-26
    }
    else
    {
        printf("You have to enter a Rotation key!\n");
        return 1; 
    }   
    //Get the phrase to encrypt and use function encrypt()
    string phrase = GetString();
    encrypt(phrase, k);
    
    return 0;   
}

/*encrypt() needs a string and the rotation as input
It checks if the character is upper-/lowercase or a another character*/

void encrypt(string s, int k)
{
    char encryptedchar;
    for (int i = 0, j = strlen(s); i < j; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            {
            ((s[i] + k) > 'z') ? (encryptedchar = (s[i] + k) - 26) : (encryptedchar = (s[i] + k));
            }
            
        if (s[i] >= 'A' && s[i] <= 'Z')
            {
            ((s[i] + k) > 'Z') ? (encryptedchar = (s[i] + k) - 26) : (encryptedchar = (s[i] + k));
            }
            
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
            {
            encryptedchar = s[i];
            }
            
    printf("%c", encryptedchar); // Print the char every loop after it went through the if loopsls
    
    }
    printf("\n");
}
