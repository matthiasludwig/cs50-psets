#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int encrypt(char c, int k);

int main (int argc, char* argv[])
{   
    if (!(argc == 2))
    {
       printf("Your entered password was not valid!\n");
       return 1; 
    }

    /*Inital declaration of important variables*/
    int passlength = strlen(argv[1]); //lenght of the passphrase
    int passphrase[passlength];       //Array with the passphrase (int)
    
    string input;                     //Plaintext provided by the user
    int inputlength;                  //Length of the plaintext

    /*Check if the command line passphrase is valid*/
    if (argc == 2)
    {
        /*Taking the passphrase from the command line and adding it
        to an array while typecasting every char as an int*/
        
        for (int i = 0; i < passlength; i++)
        {
            if (!(isalpha(argv[1][i]))) // Checking if passphrase is only alphabetic. If not return error message and the value '1'
            {
                printf("The passphrase has to be alphabet only!\n");
                return 1;
            }
            if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                passphrase[i] = ((int) (argv[1][i] % 65));
            }
            if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
            {
                passphrase[i] = ((int) (argv[1][i] % 97));
            }
        }
    }
    /*End of Validation check*/
    
    /*Get the plaintext from the User*/
    input = GetString();
    inputlength = strlen(input); //Store the plaintext length in the variable 'inputlength'
    int output[inputlength]; //Array output is used to store the encrypted char after it has beedn encrypted

    for (int i = 0, j = 0; i < inputlength; i++)
    {
        if (isalpha(input[i]))
        {
            int wrap = j % passlength;
            output[i] = encrypt(input[i], passphrase[wrap]);
            j++;
        }
        if (!(isalpha(input[i])))
        {
            output[i] = input[i];
        }
    }
    
    //Print the encypted Output
    for (int i = 0; i < inputlength; i++)
    {
        printf("%c", output[i]);
    }
    
    printf("\n");

    return 0; //Signal a bug free run of the program
}




/*encrypt() needs a string and the rotation as input
It checks if the character is upper-/lowercase or a another character*/

int encrypt(char c, int k)
{
    int encryptedchar;
        if (c >= 'a' && c <= 'z')
            {
            ((c + k) > 'z') ? (encryptedchar = (c + k) - 26) : (encryptedchar = (c + k));
            //printf("Unencrypted char: %i, Encrypted char: %i\n", c,encryptedchar);
            return encryptedchar;
            }
            
        if (c >= 'A' && c <= 'Z')
            {
            ((c + k) > 'Z') ? (encryptedchar = (c + k) - 26) : (encryptedchar = (c + k));
            //printf("Unencrypted char: %i, Encrypted char: %i\n", c,encryptedchar);
            return encryptedchar;
            }
            
        /*if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            {
            encryptedchar = c;
            return encryptedchar;
            }*/
            return false; //Should something go wrong within the function return false
}
