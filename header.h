#ifndef header_h
#define header_h
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node                  // Define a structure named 'node'
{                                    // Start of structure 'node'
    char arr[200];                   // Array of 200 characters
    struct node *link;               // Pointer to the next 'node'
} invert;                            // Alias 'invert' for 'struct node'

typedef enum                         // Define an enumeration 'status'
{                                    // Start of enumeration 'status'
    FAILURE,                         // Enumeration value for failure
    SUCCESS,                         // Enumeration value for success
} status;                            // Alias 'status' for the enum

typedef struct subnode               // Define a structure named 'subnode'
{                                    // Start of structure 'subnode'
    int w_count;                     // Integer for word count
    char f_name[20];                 // Array of 20 characters for a file name
    struct subnode *slink;           // Pointer to the next 'subnode'
} sub_node;                          // Alias 'sub_node' for 'struct subnode'

typedef struct mainnode              // Define a structure named 'mainnode'
{                                    // Start of structure 'mainnode'
    int f_count;                     // Integer for file count
    char word[20];                   // Array of 20 characters for a word
    sub_node *slink;                 // Pointer to the first 'subnode'
    struct mainnode *mlink;          // Pointer to the next 'mainnode'
} main_node;                         // Alias 'main_node' for 'struct mainnode'

typedef struct hashnode              // Define a structure named 'hashnode'
{                                    // Start of structure 'hashnode'
    int index;                       // Integer for the index
    main_node *link;                 // Pointer to the first 'main_node'
} hash;                              // Alias 'hash' for 'struct hashnode'

status check(invert *head, char *str);       		// Function to check the 'invert' list
status insert_list(invert **head, char *str); 		// Function to insert into the 'invert' list
status create(hash *arr, invert *head);      		// Function to create a hash from 'invert'
status display(hash *arr);                   		// Function to display the hash table
status search(hash *arr, char *user);        		// Function to search in the hash table
status save(hash *arr, FILE *fptr);          		// Function to save the hash table to a file
status update(FILE *fptr1, hash *arr, invert **head); 	// Function to update hash table from a file
status free_head(invert **head, char *str);  		// Function to free a node in the 'invert' list

#endif                                      
