#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{    
    //Initial declaration of the variables used for the DollarAmount and later for the amount of coins calculated
    float DollarAmount = 0;
    int CoinAmount = 0;

    do {
        
        printf("O hai! How much change is owed?\n");
        DollarAmount = GetFloat(); //Assign the input as a float to the variable DollarAmount

        }
    while (!(DollarAmount >= 0)); //Prompt the user again if the input is negative
    
    int CentAmount = round(DollarAmount * 100); //Make a cents amount out of the Input and use round() to round it to a decimal number. Then Typecast the numbers as int so the decimal places are trunkated 
   
    while (CentAmount >= 25) //First check if Quarters can be used
    {
        CentAmount -= 25;   //If yes reduce the total amount by 25 and
        CoinAmount++;       //count +1 for the variable that counts how many coins we use
    }
    while (CentAmount >= 10)//Analog to the quarter while() loop
    {
        CentAmount -= 10;
        CoinAmount++;
    }
    while (CentAmount >= 5)//Analog to the quarter while() loop
    {
        CentAmount -= 5;
        CoinAmount++;
    }
    while (CentAmount >= 1)//Analog to the quarter while() loop
    {
        CentAmount -= 1;
        CoinAmount++;
    }
    printf("%i\n", CoinAmount);//At the end return the amount of coins used
}
