// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// total number of words: 143k
// chosen N: 150% of total words
const unsigned int N = 215500;

// Hash table
node *table[N];

// Size function
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    unsigned int hash_val = hash(word);

    // access linked list at that index in the hash table
    node *ptr = table[hash_val];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
// hash function (djb2) adapted from: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // const char *dictionary is pointer to a file
    FILE *src = fopen(dictionary, "r");
    if (src == NULL)
    {
        return false;
    }

    char scanned_word[LENGTH + 1];
    while (fscanf(src, "%s", scanned_word) != EOF)
    {
        node *n = malloc(sizeof(node)); // n is a node
        if (n == NULL)
        {
            fclose(src);
            return false;
        }
        strcpy(n->word, scanned_word); // destionation_ src_

        // fix this yet
        unsigned int index = hash(scanned_word);

        // inserting the word into the linked list
        n->next = table[index];
        table[index] = n;

        word_counter++;
    }

    fclose(src);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_counter > 0)
    {
        return word_counter;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // if the bucket was not used
        if (table[i] == NULL)
        {
            continue;
        }

        // point a cursor to a linked list
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // temporary node assigned as cursor->next
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
