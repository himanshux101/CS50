/*
 *  mario.c
 *
 *  Himanshu singh
 *  himanshux101@gmail.com
 *
 *  it will regenerate the experience of you mario
 */


#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    do
    {
        printf("Height : ");
        height = get_int();
    }
    while( !(height >= 0 && height < 24));
        for (int i=0;i<height;i++)
        {
            for (int j=i;j<height-1;j++)
            {
                printf(" ");
            }
            for (int k=0;k<i+2;k++)
            {
                printf("#");
            }
            printf("\n");
        
    }
}
