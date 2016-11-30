/****************************************************************************
* recover.c
*
* Computer Science 50
* Problem Set 4
*
* Recovers JPEGs from a forensic image.
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
#define BLOCKSIZE 512


int main(void)    
{
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
        {
            // printf("Could not open %s.\n", file);
            return 2;
        }
        
    int counter = 0;
    
    FILE* outp;
    //null esures that the file has never been opened
    outp = NULL;

    while (1)
    {
        //this is one whole block
        BYTE block[BLOCKSIZE];
        
        // iterate over each byte in each block until you reach the end of the file
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            // if you reach the end of file, close the file
            if (feof(file))
            {
                fclose(file);
                
                // close previously opened output file pointer if necessary
                if (outp != NULL)
                    fclose(outp);
                    
                return 0;
            }
            
            // read one byte at a time
            fread(&block[i], sizeof (BYTE), 1, file);
        }
        
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            if (outp != NULL)
            {
                //then close
                fclose(outp);
            }
            char title[5];
            
            //naming of file
            sprintf(title ,"%02d.jpeg" ,counter);
            counter++;
            
            if ((outp = fopen(title, "w")) == NULL)
            {
                printf("Could not write image.\n");
                return 1;
            }
            fwrite(&block[0], sizeof (BYTE), BLOCKSIZE, outp);
        }
        else if (outp != NULL) 
        {
            fwrite(&block[0], sizeof (BYTE), BLOCKSIZE, outp);
        }
        
    }
    
    fclose(file);
    return 0;
}