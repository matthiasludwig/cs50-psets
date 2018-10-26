/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0) {
        return false;
    }

    // Linear search
    // for (int i = 0; i < n; i++) {
    //     if (values[i] == value) {
    //         return true;
    //     }
    // }
    // return false;


    // Binary Search

    int start = 0;
    int end = n - 1;
    int middle;

    while ((end - start + 1)!= 0) {
        middle = (start + end) / 2;

        if (values[middle] == value) {
            return true;
        }
        if (values[middle] > value) {
            end = middle - 1;
        }
        else if (values[middle] < value) {
            start = middle + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // SELECTION SORT
    int smallest;

    for (int i = 0; i < n; i++) {
        // Define outer counter as the smallest item
        smallest = i;
        for (int j = i; j < n; j++) {
            // Check the smallest item with all following. If a smaller one is found, change the smallest item and continue searching
            if (values[j] < values[smallest]) {
                smallest = j;
            }
        }
        // After all values are checked swap the smallest item with the outer Loop (i) position
        swap(values, i, smallest);
    }
}

// swaps a with b in the array that is passed
void swap(int array[], int a, int b) {
    if (a == b) {
        return;
    }
    int temp = array[b];
    array[b] = array[a];
    array[a] = temp;
}
