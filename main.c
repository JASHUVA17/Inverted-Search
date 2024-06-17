#include "header.h"

int main(int argc, char * argv[])  			// Main function with argument count and argument vector
{
    invert *head = NULL;           			// Initialize head of invert list to NULL
    hash arr[28];                  			// Declare an array of hash nodes with size 28
    for(int i = 0; i < 28; i++)    			// Loop to initialize the hash array
    {
	arr[i].index = i;          			// Set the index of hash node to i
	arr[i].link = NULL;        			// Initialize link of hash node to NULL
    }
    if(argc == 1)                  			// Check if no command-line arguments are provided
    {
	fprintf(stdout, "Error : please pass proper commands\n"); 	// Print error message
	return 0;                  
    }
    else
    {
	if(argc > 1)               			// Check if there are command-line arguments
	{
	    int i = 1;             			// Initialize i to 1 for argv iteration
	    while(argv[i] != NULL) 			// Iterate through command-line arguments
	    {
		char* cmp;         			// Declare a pointer for comparing file extension
		cmp = strstr(argv[i], "."); 		// Find the dot in the filename
		if(strcmp(cmp, ".txt") != 0) 		// Check if the file is not a .txt file
		{
		    printf("-------------------------------------------------------\n");
		    printf("Error : %s is not a '.txt file\n", argv[i]); 			// Print error message
		    printf("-------------------------------------------------------\n");
		}
		else
		{
		    FILE * fptr = fopen(argv[i], "r"); 	// Open the file in read mode
		    if(fptr == NULL) 			// Check if the file opening failed
		    {
			printf("-------------------------------------------------------\n");
			fprintf(stdout, "Error :%s File is not present\n", argv[i]); 		// Print error message
			printf("-------------------------------------------------------\n");
		    }
		    else
		    {
			fseek(fptr, 0, SEEK_END); 	// Move the file pointer to the end
			int size = ftell(fptr); 	// Get the size of the file
			if(size == 0) 			// Check if the file is empty
			{
			    printf("-------------------------------------------------------\n");
			    printf("Error : %s File is Empty \n", argv[i]); 			// Print error message
			    printf("-------------------------------------------------------\n");
			}
			else

			    if(check(head, argv[i]) == SUCCESS) 			// Check if the file is not a duplicate
			    {
				if(insert_list(&head, argv[i]) == SUCCESS) 		// Insert the file into the list
				{
				    printf("File is Inserted %s\n", argv[i]); 		// Print success message
				}
				else
				{
				    printf("File is not Inserted\n"); 			// Print failure message
				}
			    }
			    else
			    {
				printf("-------------------------------------------------------\n");
				printf("Error : Duplicate data found in the list for %s\n", argv[i]); // Print error message
				printf("-------------------------------------------------------\n");
			    }
		    }
		}
		i++; 								// Increment the index for the next command-line argument
	    }
	}	
	int choice, flag = 0; 							// Declare choice and flag variables
	while(1) 								// Infinite loop for menu
	{
	    printf("1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update Database\n6.Exit\nEnter your Choice :");									      // Print menu options
	    scanf("%d", &choice);						// Read user's choice
	    switch(choice) 							// Switch statement to handle user choice
	    {
		case 1 :
		    if (flag == 0) 						// Check if the database hasn't been created yet
		    {
			printf("You entered create database\n"); 		// Print message
			if(create(arr, head) == SUCCESS) 			// Create the database
			{
			    flag = 1; 						// Set the flag to indicate database creation
			    printf("-------------------------------------------------------\n");
			    printf("DATABASE CREATED SUCCESSFULLY\n"); 					// Print success message
			    printf("-------------------------------------------------------\n");
			}
			else
			{
			    printf("Creation failed\n"); 			// Print failure message
			}
		    }
		    else

		    {
			printf("-------------------------------------------------------\n");
			printf("DATABASE CREATED SUCCESSFULLY\n"); 					// Print success message
			printf("-------------------------------------------------------\n");
		    }
		    break;
		case 2:
		    printf("You entered Display database\n"); 			// Print message
		    if(display(arr) == SUCCESS) 				// Display the database
		    {
			printf("-------------------------------------------------------\n");
			printf("DATABASE DISPLAYED SUCCESSFULLY\n"); 					// Print success message
			printf("-------------------------------------------------------\n");
		    }
		    else
		    {
			printf("Display is failed\n"); 				// Print failure message
		    }
		    break;
		case 3:
		    printf("You entered Search database\n"); 			// Print message
		    char user[20]; 						// Declare a variable for user input
		    printf("Enter the word to search : "); 			// Prompt for word to search
		    scanf("%s", user); 						// Read the word
		    if(search(arr, user) == SUCCESS) 				// Search the word in the database
		    {
			printf("Searching is done\n"); 				// Print success message
		    }
		    else
		    {
			printf("Searching failed\n"); 				// Print failure message
		    }
		    break;
		case 4:
		    printf("You entered Save database\n"); 			// Print message
		    char file[20], *cmp; 					// Declare variables for file name and comparison
		    printf("Enter the filename to save : "); 			// Prompt for file name
		    scanf("%s", file); 						// Read the file name
		    cmp = strstr(file, "."); 					// Find the dot in the file name
		    if(strcmp(cmp, ".txt") == 0) 				// Check if the file has a .txt extension
		    {
			FILE *fptr = fopen(file, "w"); 				// Open the file in write mode
			if(save(arr, fptr) == SUCCESS) 				// Save the database to the file
			{
			    printf("-------------------------------------------------------\n");
			    printf("Saving of file is done\n"); 					// Print success message
			    printf("-------------------------------------------------------\n");
			}
			else
			{
			    printf("Saving of file is failure\n"); 		// Print failure message
			}
		    }
		    else
		    {
			printf("Enter file in a '.txt' format\n"); 		// Print error message for incorrect file format
		    }
		    break;
		case 5:
		    if (flag == 0) 						// Check if the database hasn't been created yet
		    {
			printf("You Entered Update database\n"); 		// Print message
			printf("Enter the file name : "); 			// Prompt for file name
			getchar(); 						// Consume any leftover newline character
			scanf("%[^\n]", file); 					// Read the file name
			cmp = strstr(file, ".txt"); 				// Find the dot in the file name
			if(strcmp(cmp, ".txt") == 0) 				// Check if the file has a .txt extension
			{
			    FILE *fptr = fopen(file, "r"); 			// Open the file in read mode
			    if(update(fptr, arr, &head) == SUCCESS) 		// Update the database from the file
			    {
				flag = 1; 					// Set the flag to indicate database update
				printf("Updating of file is Done\n"); 		// Print success message
			    }
			    else
			    {
				printf("Updating of file is Failure\n"); 	// Print failure message
			    }
			}
			else
			{
			    printf("Please pass the '.txt' file\n"); 		// Print error message for incorrect file format
			}
		    }
		    else
		    {
			printf("Updating of file is Done\n"); 			// Print success message
		    }
		    break;
		case 6:
		    return 0; 
		default :
		    printf("Enter the valid Choice\n"); 			// Print error message for invalid choice
	    }
	}
    }
    return 0; 									// Return success from main function
}
