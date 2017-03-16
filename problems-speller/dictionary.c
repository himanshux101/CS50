/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <strings.h>

#include "dictionary.h"
#define MAXH 145709

int total_words = 0;

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}node;

node *hashtable[MAXH];

// djb2 by Dan Bernstein
unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % MAXH;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
    int key = ( hash((unsigned char *)word)  );
    
    node* cursor = NULL;
    cursor = hashtable[key];
    
    if (hashtable[key] == NULL)
    {
        return false;
    }
    
    while ( cursor != NULL )
    {
        if ( (strcasecmp(word,cursor->word)) == 0 )
            return true;
        
        cursor = cursor->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    node* temp;
    
    FILE* dict = fopen(dictionary, "r");
    if(!dict)
    {
		printf("NOT ENOUGH MEMORY");
		return false;
    }	
	
	unload();
	total_words = 0;
    
    while (fscanf(dict,"%s",word)!=EOF)
    {
        temp = (node*) malloc(sizeof(node));
        if (temp == NULL)
        {
            unload();
            return false;
        }
        
        strcpy(temp->word,word);
        
        int key = ( hash((unsigned char *)word) );
        
        if(!hashtable[key])
            {
                temp->next = NULL;
                hashtable[key] = temp;
            }
        else    
            {
                temp->next = hashtable[key];
                hashtable[key] = temp;
            }
        
        total_words++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return total_words;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for ( int i = 0; i < MAXH; i++)
    {
        
        node* cursor = hashtable[i];
        
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
