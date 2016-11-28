/*
 *  ceaser.c
 *
 *  Himanshu singh
 *  himanshux101@gmail.com
 *
 *  This program Encripts the message for you and all you need is the key to it.
 */


#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,string argv[])
{
    
    if (argc != 2)
    {   
        printf("Try again Please");
        return 1;
    }
    printf("Give me a string please : \n");
    string plain = GetString();
    int key = atoi(argv[1]); 
    
    int i=0,n=0;
    
    for (i=0,n=strlen(plain);i<n;i++)
    {
            if(isalpha(plain[i]))
            {
                if (isupper(plain[i]))
                {
                    printf("%c", (((plain[i] - 'A') + key )%26 + 'A'));
                    // big A start from 65
                }
                if (islower(plain[i]))
                {
                    printf("%c", (((plain[i] - 'a') + key )%26 + 'a'));
                    // small a starts from 92
                }
                
            }
            else    // for spaces
            {
                    printf("%c", plain[i]);
            }
    }
    printf("\n");
}
