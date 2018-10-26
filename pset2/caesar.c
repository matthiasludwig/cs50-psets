#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

char decode(char cipher, int k);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    int k = (atoi(argv[1]) % 26);
    
    printf("plaintext: ");
    string ciphertext = get_string();
    
    printf("ciphertext: ");
    for (int i = 0, j = strlen(ciphertext); i < j; i++) {
        char temp = decode(ciphertext[i], k);
        printf("%c", temp);
    }
    printf("\n");
    return 0;
}

char decode(char cipher, int k) {
    int sum = (cipher + k);
    
    if (cipher >= 'A' && cipher <= 'Z') {
        sum = (cipher + k);
        if (sum > 90) {
            return (sum % 90) + 64;
        }
        else {
            return sum;
        }
    }
    else if (cipher >= 'a' && cipher <= 'z') {
        sum = (cipher + k);
        if (sum > 122) {
            return (sum % 122) + 96;
        }
        else {
            return sum;
        }
    }
    else {
        return cipher;
    }
}