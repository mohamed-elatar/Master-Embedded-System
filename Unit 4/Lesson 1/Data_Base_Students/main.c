/*
 * main.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#include "database.h"

//global pointer as head linked list
S_node_student_t * gPFirst_Student = NULL;

int main()
{
    uint32_t flag=0;
    uint8_t temp_info[20];
    while(!flag)
    {
        DPRINT("\n\n=========================\n");
        DPRINT("(0)  --> exit \n");
        DPRINT("(1)  --> add_student \n");
        DPRINT("(2)  --> remove_student \n");
        DPRINT("(3)  --> remove_all_student \n");
        DPRINT("(4)  --> display_student \n");
        DPRINT("(5)  --> student_reverse_nodes \n");
        DPRINT("(6)  --> student_index_first_data \n");
        DPRINT("(7)  --> student_index_end_data \n");
        DPRINT("(8)  --> student_count \n");
        DPRINT("(9)  --> student_len \n");
        DPRINT("(10)  --> student_middle \n");
        DPRINT("(11) --> student_loop \n");
        DPRINT("=========================\n\n");

        DPRINT("\n\t\t------------------------------------------\n");
        DPRINT("\t\t\t Enter option number : ");
        gets(temp_info); //str
        DPRINT("\t\t------------------------------------------\n");

        switch(atoi(temp_info))
        {
        case 0:
            flag = 1;
            break;
        case 1:
            student_Add();
            break;
        case 2:
            student_delete();
            break;
        case 3:
            students_delete_all();
            break;
        case 4:
            student_view();
            break;
        case 5:
            student_reverse();
            break;
        case 6:
            DPRINT("\nEnter index student :");
            student_index_first_data(atoi(gets(temp_info)));
            break;
        case 7:
            DPRINT("\nEnter index student :");
            student_index_end_data(atoi(gets(temp_info)));
            break;
        case 8:
            DPRINT("\ncount numbers of nodes is : %d \n" , students_count());
            DPRINT("\n\t\t-----> Done Display All count nodes <---- \n");
            break;
        case 9:
            DPRINT("\nlen numbers of nodes is : %d \n" , students_count_recursion(gPFirst_Student));
            DPRINT("\n\t\t-----> Done Display All len nodes <---- \n");
            break;
        case 10:
            DPRINT("\nmid numbers of nodes is : %d \n" , students_middle());
            DPRINT("\n\t\t-----> Done Display mid nodes <---- \n");
            break;
        case 11:
            if(students_loop())
            {
                DPRINT("\nExist looping in nodes\n");
            }
            else DPRINT("\nNot Exist looping in nodes\n");
            DPRINT("\n\t\t-----> Done detect loop nodes <---- \n");
            break;
        default:
            DPRINT("wrong option number \n");
        }
    }
    return 0;
}
