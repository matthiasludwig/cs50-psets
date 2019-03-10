// Check credit card numbers and output the issuer or validity
#include <cs50.h>
#include <stdio.h>

long get_Input(string prompt);
bool check_Validity(long number);
void check_Issuer(long number);

int main(void)
{
    long number = get_Input("Number: ");

    bool valid = check_Validity(number);
    if (valid)
    {
        check_Issuer(number);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

long get_Input(string prompt)
{
    long number = 0;
    // repeat until requirements from while part are satisfied
    do
    {
        number = get_long("%s", prompt);
    }
    while (number <= 0); // check if input is positive
    return number;
}

bool check_Validity(long number)
{
    bool valid = false;
    int sum = 0;
    int i = 1;
    while (number > 0)
    {
        int ending = number % 10;  // Get the last digit of the number

        // Multiply every second digit by 2
        if (i % 2 == 0)
        {
            ending *= 2;
            ending = (ending > 9) ? ((ending % 10) + ((ending / 10)) % 10) : ending;
        }
        // Add up the ending to the sum
        sum += ending;
        i++;  // Iterate the loop
        number /= 10;  // Cut off the last digit of the number
    }

    if (sum % 10 == 0 && (number / (10000000000000000) == 0))
    {
        valid = true;
    }

    return valid;
}

void check_Issuer(long number)
{
    int sixteen = number / (1000000000000000);
    int fifteen = number / (100000000000000);
    int fourteen = number / (10000000000000);
    int thirteen = number / (1000000000000);

    if (sixteen == 4 || thirteen == 4)
    {
        printf("VISA\n");
    }
    if (fifteen >= 51 && fifteen <= 55)
    {
        printf("MASTERCARD\n");
    }
    if (fourteen == 34 || fourteen == 37)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
