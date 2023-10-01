/***********************************************
 * @file           : main.c						*
 * @author         : mohamed elatar             *
 * @Data           : 26/9/2023                  *
 ************************************************/

#include "fifo.h"

FIFO_BUF_t Queue;
element_type student[size_buffer];
uint8_t text[10];
uint32_t flag;

int main()
{
	if(FiFO_Init(&Queue , student , size_buffer) == FIFO_NO_ERROR)
	{
		DPRINT("\t\t %s","---> Welcome to the Student Management System <---\n");
		while(!flag)
		{
			DPRINT("\n\n\t----------------------------------------\n");
			DPRINT("\tChoose the task that you want to perform\n");
			DPRINT("\t----------------------------------------\n");
			DPRINT("1. Add the student details manually\n");
			DPRINT("2. Add the student details from text file\n");
			DPRINT("3. Find the student details by roll number\n");
			DPRINT("4. Find the student details by first name\n");
			DPRINT("5. Find the student details by course ID\n");
			DPRINT("6. Find the total number of students\n");
			DPRINT("7. Delete the students details by roll number\n");
			DPRINT("8. Update the students details by roll number\n");
			DPRINT("9. Show all information\n");
			DPRINT("10. Exit\n");
			DPRINT("-------------------------------------------------\n");
			DPRINT("\n\t------------------------------------------\n");
			DPRINT("\tEnter your choice to perform the task: ");
			gets(text);
			DPRINT("\t------------------------------------------\n");
			switch(atoi(text))
			{
			case 1:
				add_student_by_manually(&Queue);
				break;
			case 2:
				add_student_from_file(&Queue);
				break;
			case 3:
				find_student_by_roll_num(&Queue);
				break;
			case 4:
				find_student_by_first_name(&Queue);
				break;
			case 5:
				find_course_enroll(&Queue);
				break;
			case 6:
				find_total_number_students(&Queue);
				break;
			case 7:
				delete_student(&Queue);
				break;
			case 8:
				update_student(&Queue);
				break;
			case 9:
				display_all_student(&Queue);
				break;
			case 10:
				flag = 1;
				break;
			default:
				DPRINT("[ERROR] wrong choice \n");
				DPRINT("----------------------------\n");
			}
		}
	}
	return 0;
}
