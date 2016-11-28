/**
* vigenere.c
* 
* Himanshu singh
* himanshux101@gmai.com
* 
* pset2 solution
* Usage : Encrypts text using vigenere cipher
* Input : take key as command line input
*
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int getKey(int counter, string k);

int main(int argc, string argv[])
{
	// All variables in camle case!!!
	string key = argv[1];
	
	//counter for key to run till the length of text and not for spaces!!
	int counter = 0; 							

	if (argc != 2)  							// not more than one word 
		{
			printf("Try again!!!\n");
			return 1;
		}
	else 
	{
	// Check if k only contains letters
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        if (!isalpha(key[i]))                   //isalpha only works on characters
        {
            printf("Invalid\n");
            return 1;
        }
    }
    }
	
	string text = GetString();

	for ( int i=0, n=strlen(text); i<n ; i++)
	{
		 if (isalpha(text[i]))
		 {
		 	if (isupper(text[i]))
		 		{
		 			printf("%c", ((text[i] - 65) + getKey(counter,key))%26 + 65 );
		 			counter ++;
		 		}
		 	if (islower(text[i]))
		 		{
		 			printf("%c", ((text[i] - 97) + getKey(counter,key))%26 + 97 );
		 			counter ++;
		 		}	
		 }
		 else 
		 	printf("%c", text[i]);				// This else statment is for spaces
	}

	printf("\n");
    return 0;
}

/*
*	A function that takes string and its counter variable as argument 
*	and then return the whole key!!!
*/
int getKey(int counter, string key)
{
    int length = strlen(key);
    return toupper(key[counter % length]) - 65;
}