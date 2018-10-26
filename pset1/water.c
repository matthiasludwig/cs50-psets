#include <cs50.h>
#include <stdio.h>

int main(void) {
    int length;
    
    printf("minutes: ");
    length = get_int();
    printf("bottles: %i\n", length * 12);
}