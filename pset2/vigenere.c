#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool checkInput(string k);
char decode(char cipher, int k);

int main(int argc, string argv[]) {
    //checks if k was passed in
    if (argc != 2) {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    //checks if all characters are letters
    if (!(checkInput(argv[1]))) {
        printf("Usage ./vigenere k\n");
        return 1;
    }
    // save the key in k
    string k = argv[1];
    int klength = strlen(k);
    int counter = 0;
    //ask a user for plaintext
    printf("plaintext: ");
    string plaintext = get_string();
    string ciphertext = plaintext;
    
    // Encrypt the input
    for (int i = 0, j = strlen(plaintext); i < j; i++) {
        if ((plaintext[i] >= 'a' && plaintext[i] <= 'z') || (plaintext[i] >= 'A' && plaintext[i] <= 'Z')) {
            int ktemp = tolower(k[counter % klength]);
            ciphertext[i] = decode(plaintext[i], ktemp);
            counter++;
        }
        else {
            ciphertext[i] = plaintext[i];
        }
        
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}


bool checkInput(string k) {
    for (int i = 0, j = strlen(k); i < j; i++) {
        if (!isalpha(k[i])) {
            return false;
        }
    }
    return true;
}

char decode(char cipher, int k) {
    if (cipher >= 'A' && cipher <= 'Z') {
        int sum = ((cipher % 65) + (k % 97)) % 26;
        return sum + 65;
    }
    else if (cipher >= 'a' && cipher <= 'z') {
        int sum = ((cipher % 97) + (k % 97)) % 26;
        return sum + 97;
    }
    return -1;
}