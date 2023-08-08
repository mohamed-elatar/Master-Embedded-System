/*
 * main.c
 *
 *  Created on: Aug 3, 2023
 *      Author: mohamed elatar
 */
#include <stdio.h>
#include <string.h>
struct data
{
    unsigned char  data_1;
    unsigned int   data_2;
    unsigned char  data_3;
    unsigned short data_4;
};
struct data new_data;
void memory_range(char * ptr , int size)
{
    int i=0;
    for(i ; i<size ; i++)
    {
        printf("address %p ==> data %#X \n" , ptr , (unsigned char)*ptr );
        ptr++;
    }
}
int main()
{
    new_data.data_1 = 0x11;
    new_data.data_2 = 0xFFEDCBAA;
    new_data.data_3 = 0x22;
    new_data.data_4 = 0xABCD;
    memory_range(&new_data , sizeof(new_data));

    struct data * ptr = &new_data;
    printf("%X" , ptr->data_3);
    return 0;
}




