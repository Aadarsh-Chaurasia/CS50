// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (26 * 26);

// Hash table
node *table[N];
// table->next = NULL;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    // iterating inside linked list at index 'index' of table.
    for (node *ptr = cursor; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int h = 0;
    if (strlen(word) == 1)
    {
        h = 26 * (tolower(word[0]) - 'a');
    }
    else
    {
        h = 26 * (tolower(word[0]) - 'a') + (tolower(word[1]) - 'a');
    }
    // A =0, aa = 0, ab = 2, az = 25, ba = 26 etc... kind of base 26.
    return h;
}

int word_count = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opening file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        // error in loading file.
        return false;
    }

    // Read each word in file
    char current_word[LENGTH + 1];
    while (fscanf(file, "%s", current_word) != EOF)
    {
        word_count++;

        // creating a new node for the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, current_word);
        new_node->next = NULL;

        int index = hash(current_word);

        // if no node in that hash index, make it first node.
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        // If node already exist, add new node in front.
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        // Reset the table[i] pointer to NULL after freeing all nodes in the list
        table[i] = NULL;
    }

    return true;
}
