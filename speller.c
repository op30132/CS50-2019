#include <stdbool.h>
#include "dictionary.h"
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 16384;

// Hash table
node *table[N];

int word_num = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    char copy[n + 1];
    copy[n] = '\0';
    for(int i = 0; i < n; i++)
    {
        copy[i] = tolower(word[i]);
    }

    int index = hash(copy) % N;
    node* cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, copy) == 0){
            return true;
        }
        cursor = cursor->next;
    }
    return false;

    // char copy[strlen(word) + 1];
    // strcpy(copy, word);
    // char *p = copy;
    // for ( ; *p; ++p) *p = tolower(*p);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned long hash = 5381;

    int c;
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->word, word);
        new_node->next = NULL;

        int index = hash(word) % N;

        if (table[index] != NULL)
        {
            new_node->next = table[index];
        }

        table[index] = new_node;

        word_num++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_num;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node* cursor = table[i];

        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
