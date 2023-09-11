/*
 * database.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mohamed elatar
 */

#include "database.h"
extern S_node_student_t * gPFirst_Student;

void student_Add()
{
    S_node_student_t * PNew_Student;
    S_node_student_t * PLast_Student;
    uint8_t temp_info[20];
    if(gPFirst_Student == NULL)
    {
        //create new node
        PNew_Student =(S_node_student_t*)malloc(sizeof(S_node_student_t));
        if(PNew_Student != NULL)
            gPFirst_Student = PNew_Student;
    }
    else
    {
        //until reache last node
        PLast_Student = gPFirst_Student;
        while(PLast_Student->PNext_Student)
            PLast_Student = PLast_Student->PNext_Student;

        //create new node
        PNew_Student =(S_node_student_t*)malloc(sizeof(S_node_student_t));
        PLast_Student->PNext_Student = PNew_Student;
    }
    //enter data
    DPRINT("Enter ID : ");
    gets(temp_info);
    PNew_Student->data.ID = atoi(temp_info);

    DPRINT("Enter Student Name : ");
    gets(PNew_Student->data.name);

    DPRINT("Enter years : ");
    gets(temp_info);
    PNew_Student->data.years = atof(temp_info);

    DPRINT("Enter height : ");
    gets(temp_info);
    PNew_Student->data.height = atof(temp_info);

    //last node not point anything
    PNew_Student->PNext_Student = NULL;
    DPRINT("\n\t\t-----> Done Add New Student <---- \n");
}

void student_delete()
{
    uint8_t temp_info[20];
    uint16_t select_id;

    DPRINT("\nEnter the student id to be deleted :");
    gets(temp_info); //str
    select_id = atoi(temp_info); // str to int

    if(gPFirst_Student)
    {
        S_node_student_t * PSelect_Student = gPFirst_Student;
        S_node_student_t * PPrevious_Student = NULL;

        // not null
        while(PSelect_Student)
        {
             if(PSelect_Student->data.ID == select_id)
             {
                 if(PPrevious_Student)
                 {
                    //link nodes
                    PPrevious_Student->PNext_Student = PSelect_Student->PNext_Student;
                 }
                 else
                 {
                    //null
                    gPFirst_Student = PSelect_Student->PNext_Student;
                 }
                 free(PSelect_Student);
                 DPRINT("\n\t\t-----> Done Delete That ID <---- \n");
                 break; // terminated while
             }
             else
             {
                 PPrevious_Student = PSelect_Student;
                 PSelect_Student = PSelect_Student->PNext_Student;
                 if(PSelect_Student == NULL)
                 {
                     // if fault ID
                    DPRINT("\n can't found that ID \n");
                 }
             }
        }
    }
    else
    {
        // head linked list point null
        DPRINT("Can't remove from empty database");
    }

}

void students_delete_all()
{
    S_node_student_t * temp_free = NULL;
    if(!gPFirst_Student)
    {
        // head linked list point null
        DPRINT("Empty database");
    }
    else
    {
        // not null
        while(gPFirst_Student)
        {
            temp_free = gPFirst_Student;
            gPFirst_Student = gPFirst_Student->PNext_Student;
            free(temp_free);
        }
        gPFirst_Student = NULL;
        DPRINT("\n\t\t-----> Done Delete All Students <---- \n");
    }
}

void student_view()
{
    S_node_student_t * PCurrent_Student = gPFirst_Student;
    uint16_t counter=1;
    if(!PCurrent_Student)
    {
        // head linked list point null
        DPRINT("Empty database \n");
    }
    else
    {
        while(PCurrent_Student)
        {
            DPRINT("\n\n------------------------------------------\n\n")
            DPRINT("record number %d :\n" , counter++);
            DPRINT("\t ID : %d \n" , PCurrent_Student->data.ID);
            DPRINT("\t name : %s \n", PCurrent_Student->data.name);
            DPRINT("\t age : %.2f years old \n", PCurrent_Student->data.years);
            DPRINT("\t height : %.2f cm\n", PCurrent_Student->data.height);
            // next node
            PCurrent_Student = PCurrent_Student->PNext_Student ;
        }
        DPRINT("\n\t\t-----> Done Display All Students <---- \n");
    }
}

void student_reverse()
{
    S_node_student_t * PCurrent_Node = gPFirst_Student;
    S_node_student_t * PPerv_Node = NULL;
    S_node_student_t * PNext_Node = NULL;
    if(!gPFirst_Student)
    {
        // head linked list point null
        DPRINT("Empty database \n");
    }
    else
    {
        while(PCurrent_Node)
        {
            PNext_Node = PCurrent_Node->PNext_Student;
            PCurrent_Node->PNext_Student = PPerv_Node;
            PPerv_Node = PCurrent_Node;
            PCurrent_Node = PNext_Node;
        }
        gPFirst_Student = PPerv_Node;
        DPRINT("\n\t\t-----> Done reverse All Nodes <---- \n");
    }
}

void student_index_first_data(uint32_t record)
{
    S_node_student_t * pfindstudent = gPFirst_Student;
    uint16_t counter = 1;
    if(!pfindstudent)
    {
        // head linked list point null
        DPRINT("Empty database \n");
    }
    else
    {
        while(pfindstudent)
        {
            if(record == counter)
            {
                DPRINT("\t ID : %d \n" , pfindstudent->data.ID);
                DPRINT("\t name : %s \n", pfindstudent->data.name);
                DPRINT("\t age : %.2f years old \n", pfindstudent->data.years);
                DPRINT("\t height : %.2f cm\n", pfindstudent->data.height);
                DPRINT("\n\t\t-----> Done display That index <---- \n");
                break;
            }
            else
            {
                pfindstudent = pfindstudent->PNext_Student;
                counter++;
                if(!pfindstudent)
                {
                    DPRINT("\n can't found that index \n");
                }
            }
        }
    }
}

void student_index_end_data(uint32_t record)
{
    S_node_student_t * pcurrent = gPFirst_Student;
    S_node_student_t * pmove = gPFirst_Student;
    uint32_t counter=0 ;
    if(!gPFirst_Student)
    {
        // head linked list point null
        DPRINT("Empty database \n");
    }
    else
    {
        if(pcurrent->PNext_Student == NULL)
        {
            // first node
            DPRINT("\t ID : %d \n" , pcurrent->data.ID);
            DPRINT("\t name : %s \n", pcurrent->data.name);
            DPRINT("\t age : %.2f years old \n", pcurrent->data.years);
            DPRINT("\t height : %.2f cm\n", pcurrent->data.height);
            DPRINT("\n-----> Done display That index <---- \n");
        }
        else
        {
            while(pmove)
            {
                // not null yet
                pmove = pmove->PNext_Student;
                counter++;
                if(counter == record)
                {
                    // reach distance among two pointer
                    while(pmove)
                    {
                        pmove = pmove->PNext_Student;
                        pcurrent = pcurrent->PNext_Student;
                    }
                    DPRINT("\t ID : %d \n" , pcurrent->data.ID);
                    DPRINT("\t name : %s \n", pcurrent->data.name);
                    DPRINT("\t age : %.2f years old \n", pcurrent->data.years);
                    DPRINT("\t height : %.2f cm\n", pcurrent->data.height);
                    DPRINT("\n-----> Done display That index <---- \n");
                }
            }
            if(counter != record)
            {
                DPRINT("\n can't found that index \n");
            }
        }
    }
}

uint32_t students_count()
{
    S_node_student_t * PCurrent_Student = gPFirst_Student;
    uint32_t counter=0;
    if(!PCurrent_Student)
    {
        // head linked list point null
        counter = 0;
    }
    else
    {
        while(PCurrent_Student)
        {
            counter++;
            // next node
            PCurrent_Student = PCurrent_Student->PNext_Student ;
        }
    }
    return counter;
}

uint32_t students_middle()
{
    S_node_student_t * Pslow = gPFirst_Student;
    S_node_student_t * Pfast = gPFirst_Student;
    uint32_t mid = 1 ;
    if(!gPFirst_Student)
    {
        // head linked list point null
        mid = 0;
    }
    else
    {
        while(Pfast)
        {
            Pfast = Pfast->PNext_Student;
            // when even not get run time error
            if(Pfast) Pfast = Pfast->PNext_Student;
            else break;
            Pslow = Pslow->PNext_Student;
            mid++;
        }
    }
    return mid;
}

uint32_t students_loop()
{
    S_node_student_t * Pslow = gPFirst_Student;
    S_node_student_t * Pfast = gPFirst_Student;
    uint32_t retval = 1 ;
    if(!gPFirst_Student)
    {
        // head linked list point null
        retval = 0;
    }
    else
    {
        while(Pfast)
        {
            Pfast = Pfast->PNext_Student;
            // when even not get run time error
            if(Pfast) Pfast = Pfast->PNext_Student;
            else break;
            Pslow = Pslow->PNext_Student;
            if(Pfast == Pslow) retval = 1;
        }
    }
    return retval;
}

uint32_t students_count_recursion(S_node_student_t * p)
{
    return ( (!p) ? 0 : 1+students_count_recursion(p->PNext_Student) );
}
