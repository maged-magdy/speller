// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "ctype.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 1;
# define N 100000

unsigned long words_in_dictionary = 0;

// Hash table
node *table[N] = {NULL};

void insert_node(node** list,char temp_word[])
{
    long x = hash(temp_word);
    if (*list == NULL)
    {
        node* temp = malloc(sizeof(node));
        strcpy(temp->word,temp_word);
        temp->next = NULL;
        *list = temp;
    }
    else
    {
        node* temp = malloc(sizeof(node));
        strcpy(temp->word,temp_word);
        temp->next = *list;
        *list = temp;
    }
}

bool search_list(node* list,const char temp_word[])
{

    for (node* temp = list; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->word,temp_word) == 0)
        {
            return true;
        }
    }
    return false;
}


void destroy_list(node* list)
{
    if (list == NULL)
    {
        return;
    }
    destroy_list(list->next);
    free(list);
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char copy[LENGTH+1];
    for (int i = 0; i < strlen(word)+1; i++)
    {
        copy[i] = tolower(word[i]);
    }
    unsigned long x = hash(copy);
    if (table[x] != NULL)
    {
        return search_list(table[x], copy);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;
    unsigned int c;

    while ((c = *word++) != 0)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char buffer[LENGTH+1];
    FILE *dic = fopen(dictionary,"r");
    if(dic == NULL)
    {
        return false;
    }
    while (fscanf(dic,"%s\n",buffer) != EOF)
    {
        insert_node(&table[hash(buffer)],buffer);
        words_in_dictionary++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N ; i++)
    {
        destroy_list(table[i]);
    }
    return true;
}
