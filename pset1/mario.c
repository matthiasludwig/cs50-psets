#include <cs50.h>
#include <stdio.h>

int main(void) {
    int height;
    int row;
    int hashes;
    int spaces;

    do {
        printf("height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    // Drawing the Pyramide
    for (row = 0; row < height; row++) {
        hashes = (1 + row);
        spaces = (height - hashes);
        for (int i = 0; i < spaces; i++) {
            printf(" ");
        }
        for (int i = 0; i < hashes; i++) {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i <= row; i++) {
            printf("#");
        }
        printf("\n");
    }

}