#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Delaring of the variable height that will be used to print the pyramide
    int height;    
    
    do {
    //Ask the user for an integer
    printf("Height: ");
    height = GetInt();
    }
    while (!(height >= 0 && height < 24)); //The input has to be between 0 and 23 (inclusive). If not prompt the user again.
    
    
    for (int row = 0; row < height; row++) //We have to have one less rows then what the user inputed. For example height 8 = 7 rows.
    { 
        for (int spaces = height - 1; spaces - row > 0; spaces--) //To align the pyramide on the right we use spaces.
        {
            printf(" ");
        }
        for (int column = 2; column + row > 0; column--) //Then we print the pyramide. We start with two '#'
        {
            printf("#");
        } 
    printf("\n"); //Afer each row is printed we go to the next line and start the space and column loop again
    }
}
