#include "header.h"
status check(invert *head, char *str)  			// Function to check for duplicate files in the list		
{
    if(head == NULL) 					// If the list is empty
    {
        return SUCCESS; 				// No duplicate, return SUCCESS
    }
    else
    {
        invert *temp = head; 				// Temporary pointer to traverse the list
        while(temp != NULL) 				// Traverse until the end of the list
        {
            if(strcmp(temp -> arr, str) == 0) 		// Check if the file name matches
            {
                return FAILURE; 			// Duplicate found, return FAILURE
            }
            temp = temp -> link; 			// Move to the next node
        }
        return SUCCESS; 				// No duplicate found, return SUCCESS
    }
}

status insert_list(invert **head, char *str) 	// Function to insert a file into the list
{
    invert *new = malloc(sizeof(invert)); 	// Allocate memory for a new node
    if(new == NULL) 				// Check if memory allocation failed
    {
        return FAILURE; 			// Return FAILURE if allocation failed
    }
    strcpy(new -> arr, str); 			// Copy the file name into the new node
    new -> link = NULL; 			// Set the new node's link to NULL
    if(*head == NULL) 				// If the list is empty
    {
        *head = new; 				// Make the new node the head
        return SUCCESS; 			// Return SUCCESS
    }
    invert *temp = *head; 			// Temporary pointer to traverse the list
    while(temp->link != NULL) 			// Traverse until the end of the list
    {
        temp = temp->link; 			// Move to the next node
    }
    temp->link = new; 				// Insert the new node at the end
    return SUCCESS; 				// Return SUCCESS
}

status create(hash *arr, invert *head) 					// Function to create a hash table from the list of files
{
    char str[50]; 							// Buffer to hold words read from files
    int index; 								// Variable to hold hash index
    invert *temp = head; 						// Temporary pointer to traverse the file list

    while(temp != NULL) 						// Traverse through all files in the list
    {
        FILE *fptr = fopen(temp -> arr, "r"); 				// Open the file in read mode
        while((fscanf(fptr, "%s", str)) != EOF) 			// Read words from the file
        {
            if(str[0] >= '0' && str[0] <= '9') 				// If the word starts with a digit
            {
                index = 26; 						// Assign index for digits
            }
            else if((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')) 	// If the word starts with a letter
            {
                char ch = tolower(str[0]); 				// Convert the letter to lowercase
                index = ch - 97; 					// Calculate index for letters
            }
            else
            {
                index = 27; 						// Assign index for other characters
            }

            if(arr[index].link == NULL) 				// If the hash index is empty
            {
                main_node *mnew = malloc(sizeof(main_node)); 		// Allocate memory for a new main node
                sub_node *snew = malloc(sizeof(sub_node)); 		// Allocate memory for a new sub node
                strcpy(mnew -> word, str); 				// Copy the word to the main node
                mnew -> f_count = 1; 					// Initialize file count to 1
                mnew -> slink = snew; 					// Link sub node to main node
                mnew -> mlink = NULL; 					// Set main node's link to NULL
                snew -> w_count = 1; 					// Initialize word count to 1
                strcpy(snew -> f_name, temp -> arr); 			// Copy the file name to the sub node
                snew -> slink = NULL; 					// Set sub node's link to NULL
                arr[index].link = mnew; 				// Link the main node to the hash index
            }
            else
            {
                main_node *mtemp = arr[index].link; 			// Temporary pointer to traverse main nodes
                main_node *mprev = NULL; 				// Pointer to keep track of previous main node
                int w_flag = 0, f_flag = 0; 				// Flags for word and file presence
                while(mtemp != NULL) 					// Traverse through main nodes
                {
                    mprev = mtemp; 					// Update previous main node
                    if(strcmp(str, mtemp -> word) == 0) 		// If the word matches
                    {
                        f_flag = 0;
                        w_flag = 1; 					// Set word flag to 1
                        sub_node *stemp = mtemp -> slink; 		// Temporary pointer to traverse sub nodes
                        sub_node *sprev = NULL; 			// Pointer to keep track of previous sub node
                        while(stemp != NULL) 				// Traverse through sub nodes
                        {
                            sprev = stemp; 				// Update previous sub node
                            if(strcmp(stemp -> f_name, temp -> arr) == 0) // If the file name matches
                            {
                                stemp -> w_count++; 			// Increment word count
                                f_flag = 1; 				// Set file flag to 1
                                break; 					// Exit loop
                            }
                            else
                            {
                                stemp = stemp -> slink; 		// Move to the next sub node
                            }
                        }
                        if(f_flag == 0) 				// If file not found
                        {
                            sub_node *snew = malloc(sizeof(sub_node)); 	// Allocate memory for a new sub node
                            strcpy(snew -> f_name, temp -> arr); 	// Copy file name to the new sub node
                            snew -> w_count = 1; 			// Initialize word count to 1
                            sprev -> slink = snew; 			// Link new sub node
                            snew -> slink = NULL; 			// Set new sub node's link to NULL
                        }
                    }
                    if(w_flag == 1) 					// If word found
                    {
                        mtemp -> f_count++; 				// Increment file count
                        break; 						// Exit loop
                    }
                    mtemp = mtemp -> mlink; 				// Move to the next main node
                }
                if(w_flag == 0) 					// If word not found
                {
                    main_node *mnew = malloc(sizeof(main_node)); 	// Allocate memory for a new main node
                    sub_node *snew = malloc(sizeof(sub_node)); 		// Allocate memory for a new sub node
                    strcpy(mnew -> word, str); 				// Copy word to the new main node
                    mnew -> f_count = 1; 				// Initialize file count to 1
                    mnew -> slink = snew; 				// Link sub node to main node
                    mnew -> mlink = NULL; 				// Set main node's link to NULL
                    mprev -> mlink = mnew; 				// Link new main node
                    strcpy(snew -> f_name, temp -> arr); 		// Copy file name to the new sub node
                    snew -> w_count = 1; 				// Initialize word count to 1
                    snew -> slink = NULL; 				// Set sub node's link to NULL
                }
            }
        }
        temp = temp -> link; 						// Move to the next file in the list
    }
    return SUCCESS; 							// Return SUCCESS
}

status display(hash *arr) 						// Function to display the hash table
{
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Index\tWord\tFile_count\tWord_count\tfilename\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < 28; i++) 					// Loop through all hash indices
    {
        if(arr[i].link != NULL) 					// If the hash index is not empty
        {
            main_node *prtemp = arr[i].link; 				// Temporary pointer to traverse main nodes
            while(prtemp != NULL) 					// Traverse through main nodes
            {
                printf("[%2d]\t", i); 					// Print index
                printf("%-12s\t", prtemp -> word); 			// Print word
                printf("%-10d\t", prtemp -> f_count); 			// Print file count
                sub_node *sub_temp = prtemp -> slink; 			// Temporary pointer to traverse sub nodes
                while(sub_temp != NULL) 				// Traverse through sub nodes
                {
                    printf("%-10d", sub_temp -> w_count); 		// Print word count
                    printf("%-15s\t", sub_temp -> f_name); 		// Print file name
                    sub_temp = sub_temp -> slink; 			// Move to the next sub node
                }
                prtemp = prtemp -> mlink; 				// Move to the next main node
                printf("\n");
            }
        }
    }
    printf("--------------------------------------------------------------------------------------------\n");
    return SUCCESS; 							// Return SUCCESS
}

status search(hash *arr, char *user) 					// Function to search for a word in the hash table
{
    int index; 								// Variable to hold hash index
    if(user[0] >= '0' && user[0] <= '9') 				// If the word starts with a digit
    {
        index = 26; 							// Assign index for digits
    }
    else if((user[0] >= 'A' && user[0] <= 'Z') || (user[0] >= 'a' && user[0] <= 'z')) 	// If the word starts with a letter
    {
        char ch = tolower(user[0]); 					// Convert the letter to lowercase
        index = ch - 97; 						// Calculate index for letters
    }
    else
    {
        index = 27; 							// Assign index for other characters
    }
    if(arr[index].link != NULL) 					// If the hash index is not empty
    {
        main_node *mtemp = arr[index].link; 				// Temporary pointer to traverse main nodes
        while(mtemp != NULL) 						// Traverse through main nodes
        {
            if(strcmp(mtemp -> word, user) == 0) 			// If the word matches
            {
                printf("\nWord Matched\n"); 				// Print match message
                printf("\nIndex is   : %d\n", index); 			// Print index
                printf("\nFile count : %d\n", mtemp -> f_count); 	// Print file count
                sub_node *stemp = mtemp -> slink; 			// Temporary pointer to traverse sub nodes
                while(stemp != NULL) 					// Traverse through sub nodes
                {
                    printf("\nWord count : %d\n", stemp -> w_count); 	// Print word count
                    printf("\nFile name  : %s\n", stemp -> f_name); 	// Print file name
                    stemp = stemp -> slink; 				// Move to the next sub node
                }
                return SUCCESS; 					// Return SUCCESS
            }
            mtemp = mtemp -> mlink; 					// Move to the next main node
        }
    }
    printf("Word is Not Found\n"); 					// Print not found message
    return FAILURE; 							// Return FAILURE
}

status save(hash *arr, FILE *fptr) 				// Function to save the hash table to a file
{
    for(int i = 0; i < 28; i++) 				// Loop through all hash indices
    {
        main_node *mtemp = arr[i].link; 			// Temporary pointer to traverse main nodes
        if(arr[i].link != NULL) 				// If the hash index is not empty
        {
            while(mtemp != NULL) 				// Traverse through main nodes
            {
                fprintf(fptr, "#%d;", i); 			// Print index
                fprintf(fptr, "%s;", mtemp -> word); 		// Print word
                fprintf(fptr, "%d;", mtemp -> f_count); 	// Print file count
                sub_node *stemp = mtemp -> slink; 		// Temporary pointer to traverse sub nodes
                for(int j = 1; j <= mtemp -> f_count; j++) 	// Loop through sub nodes
                {
                    fprintf(fptr, "%d;", stemp -> w_count); 	// Print word count
                    fprintf(fptr, "%s;", stemp -> f_name); 	// Print file name
                    stemp = stemp -> slink; 			// Move to the next sub node
                }
                mtemp = mtemp -> mlink; 			// Move to the next main node
                fprintf(fptr, "#%s", "\n"); 			// Print new line
            }
        }
    }
    return SUCCESS; 						// Return SUCCESS
}

status update(FILE *fptr1, hash *arr, invert **head)	 	// Function to update the hash table from a file
{
    char word[50], f_name[50], temp[150]; 			// Buffers to hold temporary data
    int i, index = 0, f_count = 0, w_count = 0; 		// Variables for indices and counts
    while(fscanf(fptr1, "%s", temp) != EOF) 			// Read lines from the file
    {
        if(temp[0] == '#') 					// If line starts with '#'
        {
            index = atoi(strtok(temp + 1, ";")); 		// Extract and convert index
            strcpy(word, strtok(NULL, ";")); 			// Extract word
            f_count = atoi(strtok(NULL, ";")); 			// Extract and convert file count
            if(arr[index].link == NULL) 			// If the hash index is empty
            {
                main_node *mnew = malloc(sizeof(main_node)); 	// Allocate memory for a new main node
                if(mnew == NULL) 				// Check if memory allocation failed
                {
                    return FAILURE; 				// Return FAILURE if allocation failed
                }
                else
                {
                    mnew -> f_count = f_count; 			// Set file count
                    strcpy(mnew -> word, word); 		// Copy word to the new main node
                    mnew -> mlink = NULL; 			// Set main node's link to NULL
                    mnew -> slink = NULL; 			// Set sub node's link to NULL
                    for(int i = 0; i < f_count; i++) 		// Loop through file count
                    {
                        sub_node *snew = malloc(sizeof(sub_node)); 	// Allocate memory for a new sub node
                        if(snew == NULL) 				// Check if memory allocation failed
                        {
                            return FAILURE; 				// Return FAILURE if allocation failed
                        }
                        else
                        {
                            snew -> w_count = atoi(strtok(NULL, ";")); 	// Extract and convert word count
                            strcpy(snew -> f_name, strtok(NULL, ";")); 	// Extract file name
                            free_head(head, snew -> f_name); 		// Remove file from the list
                            snew -> slink = NULL; 			// Set sub node's link to NULL
                            if(mnew -> slink == NULL) 			// If sub node's link is empty
                            {
                                mnew -> slink = snew; 			// Link new sub node
                            }
                            else
                            {
                                sub_node *stemp = mnew -> slink; 	// Temporary pointer to traverse sub nodes
                                while(stemp -> slink != NULL) 		// Traverse until the end of sub nodes
                                {
                                    stemp = stemp -> slink; 		// Move to the next sub node
                                }
                                stemp -> slink = snew; 			// Link new sub node
                            }
                        }
                    }
                }
                arr[index].link = mnew; 				// Link new main node to the hash index
            }
            else 
	    {
                main_node *mtemp = arr[index].link, *mprev = NULL; 	// Temporary pointers to traverse main nodes
                main_node *mnew = malloc(sizeof(main_node)); 		// Allocate memory for a new main node
                if(mnew == NULL) 					// Check if memory allocation failed
                {
                    return FAILURE; 					// Return FAILURE if allocation failed
                }
                else
                {
                    mnew -> f_count = f_count; 				// Set file count
                    strcpy(mnew -> word, word); 			// Copy word to the new main node
                    mnew -> mlink = NULL; 				// Set main node's link to NULL
                    mnew -> slink = NULL; 				// Set sub node's link to NULL
                    for(int i = 0; i < f_count; i++) 			// Loop through file count
                    {
                        sub_node *snew = malloc(sizeof(sub_node)); 	// Allocate memory for a new sub node
                        if(snew == NULL) 				// Check if memory allocation failed
                        {
                            return FAILURE; 				// Return FAILURE if allocation failed
                        }
                        else
                        {
                            snew -> w_count = atoi(strtok(NULL, ";")); 	// Extract and convert word count
                            strcpy(snew -> f_name, strtok(NULL, ";")); 	// Extract file name
                            free_head(head, snew -> f_name); 		// Remove file from the list
                            snew -> slink = NULL; 			// Set sub node's link to NULL
                            if(mnew -> slink == NULL) 			// If sub node's link is empty
                            {
                                mnew -> slink = snew; 			// Link new sub node
                            }
                            else
                            {
                                sub_node *stemp = mnew -> slink; 	// Temporary pointer to traverse sub nodes
                                while(stemp -> slink != NULL) 		// Traverse until the end of sub nodes
                                {
                                    stemp = stemp -> slink; 		// Move to the next sub node
                                }
                                stemp -> slink = snew; 			// Link new sub node
                            }
                        }
                    }
                }
                while(mtemp -> mlink != NULL) 				// Traverse through main nodes
                {
                    mtemp = mtemp -> mlink; 				// Move to the next main node
                }
                mtemp -> mlink = mnew; 					// Link new main node
            }
        }
    }
    create(arr, *head); 						// Rebuild the hash table
    return SUCCESS; 							// Return SUCCESS
}

status free_head(invert **head, char *str) 		// Function to remove a file from the list
{
    invert *temp = *head; 				// Temporary pointer to traverse the list
    invert *prev = NULL; 				// Pointer to keep track of previous node
    while(temp != NULL) 				// Traverse through the list
    {
        if(strcmp(temp -> arr, str) == 0) 		// If the file name matches
        {
            invert *back = temp -> link; 		// Pointer to the next node
            free(temp); 				// Free the current node
            if(prev == NULL) 				// If the current node is the head
            {
                *head = back; 				// Update the head
            }
            else
            {
                prev -> link = back; 			// Link previous node to the next node
            }
            return SUCCESS; 				// Return SUCCESS
        }
        prev = temp; 					// Update previous node
        temp = temp -> link; 				// Move to the next node
    }
    return SUCCESS; 					// Return SUCCESS
}
