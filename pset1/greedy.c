#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    float amount;
    int coins = 0;
    
    do {
        printf("O hai! How much change is owed?\n");
        amount = get_float();
    }
    while (amount < 0);
    
    int cent_amount = round(amount * 100);
    
    while (cent_amount >= 25) {
        cent_amount = cent_amount - 25;
        coins++;
    }
    while (cent_amount >= 10) {
        cent_amount = cent_amount - 10;
        coins++;
    }
    while (cent_amount >= 5) {
        cent_amount = cent_amount - 5;
        coins++;
    }
    while (cent_amount >= 1) {
        cent_amount = cent_amount - 1;
        coins++;
    }
    printf("%d\n", coins);
}