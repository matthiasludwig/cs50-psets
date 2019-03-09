// Prints a Pyramide from the game Mario
#include <cs50.h>
#include <stdio.h>

int get_Input(string prompt);
void build_Pyramide(int height);
void print_Blocks(int floor, int height, bool bricks);

int main(void)
{
    int height = get_Input("Height: ");

    build_Pyramide(height);

    return 0;
}

int get_Input(string prompt)
{
    // Initialize height to use later in the do-while loop
    int height;
    // repeat until requirements from while part are satisfied
    do
    {
        height = get_int("%s", prompt);
    }
    while (!(height >= 1 && height <= 8)); // check if input is between 1 and 8 (inclusive)
    return height;
}

void build_Pyramide(int height)
{
    // iterate over the total height
    for (int i = 1; i <= height; i++)
    {
        print_Blocks(i, height, false);
        print_Blocks(i, height, true);

        printf("  ");

        print_Blocks(i, height, true);
        printf("\n");
    }
}

void print_Blocks(int floor, int height, bool bricks)
{
    // Depending if bricks or spaces are printed set print_n for the loop
    int print_n = (bricks) ? floor : (height - floor);
    // Actually print blocks or white space
    for (int k = 0; k < print_n; k++)
    {
        bricks ? printf("#") : printf(" ");
    }
}