#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    string name = get_string();
    
    if (name != NULL) {
        // Test the first letter if it is a space or not
        if (name[0] != ' ') {
            printf("%c", toupper(name[0]));
            
        }
        //Loop through the rest of the name and check if there are spaces
        for (int i = 0, j = strlen(name); i < j; i++) {
            if (name[i] == ' ' && name[i+1] != ' ' && name[i+1] != '\0') {
                printf("%c", toupper(name[i + 1]));   
            }
        }
        printf("\n");
        return 0;
    }
    else {
        return 1;
    }
}