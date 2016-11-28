/**
*   water.c
*  
*   Himanshu singh
*   himanshux101@gmail.com
*
*   water.c will tell you how many bootles of water you consume during shower.
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int bottles = 0;
    printf("Minutes : ");
    int minutes = get_int();
    bottles = minutes * (192/16);
    printf("Bottles : %i \n ",bottles);
}
