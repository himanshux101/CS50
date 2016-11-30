typedef uint8_t BYTE
#define BLOCKSIZE 512


int main(int argc, char* argv[])    
{
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
        {
            printf("Could not open %s.\n", file);
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
        
        if (fread(&block ,sizeof(block) ,BLOCKSIZE ,file) < 512 )
        {
            fclose(file);
            fclose(outp);
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
            
            if ((outp = fopen(filename, "w")) == NULL)
            {
                printf("Could not write image.\n");
                return 1;
            }
            fwrite(&block[0], sizeof (BYTE), BLOCKSIZE, outfile);
        }
        else if (outfile != NULL) 
        {
            fwrite(&block[0], sizeof (BYTE), BLOCKSIZE, outfile);
        }
        
    }
    
    fclose(file);
    return 0;
}