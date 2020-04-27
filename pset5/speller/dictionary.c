#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

//max hashtable size 2^16
#define HASHTABLE_SIZE 65536

//struct for linked list
typedef struct wordnode
{
    char word[LENGTH + 1];
    struct wordnode *next;
}
node;

//define hashtable
node *hashtable[HASHTABLE_SIZE] = {NULL};

//declare empty head
node *head = NULL;

//declare word counter var
int counter = 0;

//hash function
//https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
int hashValue(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //add tolower so it lowers all words in texts so hash values match all dictionary words which are lower
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % HASHTABLE_SIZE;
}

bool check(const char *word)
//passes in word from text to check for it in dictionary

{
    //set up hashing of words in text
    unsigned int hash =  hashValue(word);
    //find bucket word is in
    node *cursor = hashtable[hash];

    while (cursor != NULL)
    {
        //compare strings on every node
        if ((strcasecmp(cursor->word, word)) == 0)
        {
            return true;
        }
        else
        {
            //keep looking
            cursor = cursor->next;
        }
    }
//if word is not found, add to mispelled list
    return false;
}

// Loads dictionary into memory, returning true if successful, false if not
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *inptr = fopen(dictionary, "r");

    //declare temp array for word
    char word[LENGTH + 1];

    //read each word in dictionary til end of file
    while (fscanf(inptr, "%s ", word) != EOF)
    {
        //create a node and allocate memory for each word
        node *new_node = malloc(sizeof(node));

        // memset(new_node, 0, sizeof(node));

        //if empty...
        if (new_node == NULL)
        {
            //speller quits
            unload();
            return false;
        }
        else
        {
            //copy each word into node
            strcpy(new_node->word, word);
            new_node->next = NULL;
            //new_node->word has word to hash

            //declare hashed index of word
            unsigned int hash =  hashValue(word);

            //new_node should point to whatever was previous in list
            // new_node->next = head;
            // head = new_node;
            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;

            //increment counter for each word in dictionary to return in SIZE
            counter++;
        }
    }
    //close dictionary file
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //returns total words counted from load
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //iterate thru entire hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            //free each node
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}