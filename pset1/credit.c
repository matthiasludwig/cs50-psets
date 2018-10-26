#include <cs50.h>
#include <stdio.h>

int sumUp(int startingPoint, int multiplier, int cclength, int arr[]);
bool checkSum(int sum);
string checkIssuer(int arr[], int cclength);


int main(void) {
    bool done = false;
    bool valid;
    int numbers[16];
    int cclength = 0;
    string Issuer;
    
    int firstSum = 0;
    int secondSum = 0;
    
    long long creditnumber;

    // Check Input
    do {
        printf("Number: ");
        creditnumber = get_long_long();
    }
    while(creditnumber <= 0);
    
    // Test number: 344242243310003
    while (!done) {
       int temp = creditnumber % 10;
       creditnumber /= 10;
       numbers[cclength] = temp;
       cclength++;
       if (creditnumber == 0) {
            done = true;
        }
    }
    
    // Checks
    firstSum = sumUp(1, 2, cclength, numbers);
    secondSum = sumUp(0, 1, cclength, numbers);
    
    Issuer = checkIssuer(numbers, cclength);
    valid = checkSum(firstSum + secondSum);
    
    if (valid) {
        printf("%s\n", Issuer);
    }
    else {
        printf("INVALID\n");
    }
}
    

int sumUp(int startingPoint, int multiplier, int cclength, int arr[]) {
    int sum = 0;
    while(startingPoint < cclength) {
        int temp = (((arr[startingPoint]) % 10) * multiplier);
        if (!((temp / 10) == 0)) {
            temp = (temp % 10) + (temp / 10);
        }
        sum += temp;
        startingPoint += 2;
    }
    return sum;
}

bool checkSum(int sum) {
    if ((sum % 10) == 0) {
        return true;
    }
    else {
        return false;
    }
}

string checkIssuer(int arr[], int cclength) {
    if (arr[cclength -1] == 4) {
        return "VISA";
    }
    else if (arr[cclength -1] == 5 && (arr[cclength -2] == 1 || arr[cclength -2] == 2 || arr[cclength -2] == 3 || arr[cclength -2] == 4 || arr[cclength -2] == 5)) {
        return "MASTERCARD";
    }
    else if (arr[cclength -1] == 3 && (arr[cclength -2] == 4 || arr[cclength -2] == 7)) {
        return "AMEX";
    }
    else {
        return "INVALID";
    }
}