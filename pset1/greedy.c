/*
 *  greedy.c
 *
 *  Himanshu singh
 *  himanshux101@gmail.com
 *
 *  this is a greedy algorithm that replicates the algorithm that is used in ATM matchines nowdays
 */


#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float number;
    do{
        printf("O hai! How much change is owed?\n");
        number = GetFloat();
    }while(number<0);
    
    int counter = 0;
    int bar = (int)(number);  //places before decimal
    counter = bar * 4;
    float foo = number - bar;
    foo = foo * 100;
    foo = round(foo);         // final value on which conditions work 
    
    while(foo>=25)
    {
        foo = foo - 25;
        counter++;
    }
     while(foo>=10)
    {
        foo = foo - 10;
        counter++;
    }
     while(foo>=5)
    {
        foo = foo - 5;
        counter++;
    }
     while(foo>=1)
    {
        foo = foo - 1;
        counter++;
    }
    printf("%d\n",counter);
}
