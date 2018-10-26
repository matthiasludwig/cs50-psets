/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

unsigned int hash(char *str);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    char *word = malloc(sizeof(char) * 46);
    if (word == NULL) {
        fprintf(stderr, "Could not assign *word\n");
    }
    // Open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        fprintf(stderr, "Could not open dictionary %s.\n", dictionary);
        fclose(dict);
        return false;
    }
    // Read dictionary in and create data structure out of it
    while (fscanf(dict, "%s", word) != EOF) {
        //Create a new Node
        node *node = malloc(sizeof(node));
        //Error checking for the new node
        if (node == NULL){
            fprintf(stderr, "Could not create a new node!\n");
            unload();
            return false;
        }
        int hashValue = hash(word);

        if (hashtable[hashValue] == NULL) {
            printf("I am empty \n");
        }

        printf("word = %s hash(word) = %i \n", word, hash(word));
    }

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

// Helper Functions

// Really bad hash function 'lose lose' from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(char *str) {
    unsigned int hash = 0;
    int c;

    while ((c = *str++))
        hash += c;

	return (hash % 50);
}

node createNode(char *word) {
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Can't create a new Node!\n");
    }
    strcpy(*newNode, word);

    return *newNode;
}