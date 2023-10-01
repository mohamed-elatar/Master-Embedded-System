/***********************************************
 * @file           : FIFO.c						*
 * @author         : mohamed elatar             *
 * @Data           : 26/9/2023                  *
 ************************************************/

/************* Circular QUEUE *****************/
#include "fifo.h"

/************************
 *   global variable    *
 ************************/
uint32_t id , roll , i , j;
uint8_t f_name[20] , l_name[20] , arr_roll[50];
float GPA;



FIFO_STATUS FiFO_Init (FIFO_BUF_t * FIFO_buf , element_type * buf , uint32_t length)
{
	// check null
	if(!FIFO_buf) return FIFO_NULL;

	//initialize
	else
	{
		FIFO_buf->base = buf;
		FIFO_buf->head = buf;
		FIFO_buf->tail = buf;
		FIFO_buf->length = length;
		FIFO_buf->counter = 0;

		return FIFO_NO_ERROR;
	}
}

void FIFO_enqueue_student(FIFO_BUF_t * FIFO_buf)
{
	//check null
	if(!FIFO_buf->base) {DPRINT("[ERROR] not exist buffer \n");}


	//check full
	else if(FIFO_buf->counter == FIFO_buf->length ) {DPRINT("[ERROR] buffer full \n");}

	//enqueue
	else
	{
		if(FIFO_buf->head == ( (FIFO_buf->base) + ( (FIFO_buf->length)*sizeof(element_type))))
			FIFO_buf->head = FIFO_buf->base;
		else
			FIFO_buf->head++;
		FIFO_buf->counter++;
	}
}

void FIFO_dequeue_student(FIFO_BUF_t * FIFO_buf)
{
	//check null
	if(!FIFO_buf->base) {DPRINT("[ERROR] not exist buffer \n");}

	//check empty
	else if(FIFO_buf->counter == 0) {DPRINT("[ERROR] buffer empty \n");}

	//dequeue
	else
	{
		if(FIFO_buf->tail == ( (FIFO_buf->base) + ( (FIFO_buf->length)*sizeof(element_type))))
			FIFO_buf->tail = FIFO_buf->base;
		else
			FIFO_buf->tail++;
		FIFO_buf->counter--;
		print_message(FIFO_buf , dequeue_success);
	}
}


void add_student_by_manually(FIFO_BUF_t * FIFO_buf)
{
	DPRINT("Add the students details\n");
	DPRINT("----------------------------\n");
	DPRINT("Enter the roll number : ");
	scanf("%d" , &roll);

	if(roll <= size_buffer)
	{
		if(check_roll(roll) == not_exist_roll)
		{
			arr_roll[roll] = 1;
			FIFO_buf->head->roll = roll;

			DPRINT("Enter the first name of student :");
			fgets(f_name , 20 , stdin);
			strcpy( FIFO_buf->head->first_name ,f_name);

			DPRINT("Enter the last name of student :");
			fgets(l_name , 20 , stdin);
			strcpy( FIFO_buf->head->last_name ,l_name);

			DPRINT("Enter the GPA you obtained : ");
			scanf("%f" , &GPA);
			FIFO_buf->head->gpa = GPA;

			DPRINT("Enter the course id of each course \n");
			for(i=0 ; i<max_courses ; ++i)
			{
				DPRINT("course %d id : " , i+1);
				scanf("%d" , &id);
				FIFO_buf->head->course_id[i] = id;
			}

			FIFO_enqueue_student(FIFO_buf);
			print_message(FIFO_buf , enqueue_success);
		}
		else
		{
			DPRINT("[ERROR] roll number %d is already taken \n" , roll);
			DPRINT("----------------------------\n");
		}
	}
	else
	{
		DPRINT("[ERROR] The number rolled must be less than or equal to \n\t the size of the database's roll numbers [%d] \n", size_buffer);
	}
}


void add_student_from_file(FIFO_BUF_t * FIFO_buf)
{
	FILE * pfile = NULL ;
	char buffer[100];
	int flag_check = 0;
	DPRINT("Add the students from file\n");
	DPRINT("----------------------------\n");

	pfile = fopen("info.txt" , "r");
	if(!pfile)
	{
		DPRINT("[ERROR] opening file \n");
	}
	else
	{
		if(fgets(buffer, 100, pfile))
		{
			rewind(pfile);
			while(!feof(pfile))
			{
				fscanf(pfile , "%d" , &roll);
				if(check_roll(roll) == exist_roll)
				{
					DPRINT("[ERROR] roll number %d is already taken \n" , roll);
					fscanf(pfile , "%*[^\n]");
					continue;
				}
				arr_roll[roll] = 1;
				FIFO_buf->head->roll = roll;
				fscanf(pfile , "%s" , FIFO_buf->head->first_name);
				strcat(FIFO_buf->head->first_name , "\n");
				fscanf(pfile , "%s" , FIFO_buf->head->last_name);
				strcat(FIFO_buf->head->last_name , "\n");
				fscanf(pfile , "%f" , &FIFO_buf->head->gpa);
				for(i=0 ; i<max_courses ; ++i)
				{
					fscanf(pfile , "%d" , &FIFO_buf->head->course_id[i]);
				}
				DPRINT("[INFO]  roll number %d saved successfully \n" , roll);
				FIFO_enqueue_student(FIFO_buf);
				flag_check = 1;
			}
			if(flag_check) print_message(FIFO_buf , enqueue_success);
		}
		else
		{
			DPRINT("[ERROR] can't read from empty file \n");
			DPRINT("----------------------------\n");
		}
	}
	fclose(pfile);

}

void find_student_by_roll_num(FIFO_BUF_t * FIFO_buf)
{
	Student_t * student;
	if(check_buffer_counter(FIFO_buf))
	{
		DPRINT("----------------------------\n");
		DPRINT("Enter the roll number of the student :");
		scanf("%d" , &roll);
		DPRINT("----------------------------\n");

		if(roll <= size_buffer)
		{
			if(check_roll(roll) == exist_roll)
			{
				student = return_student_roll(FIFO_buf , roll);
				DPRINT("the student details are :\n");
				DPRINT("----------------------------\n");
				DPRINT("the first name is : %s" , student->first_name);
				DPRINT("the last  name is : %s" , student->last_name);
				DPRINT("the GPA is : %.1f \n", student->gpa);
				DPRINT("id of each course \n");
				for(j=0 ; j<max_courses ; ++j)
				{
					DPRINT("the course id %d \n", student->course_id[j]);
				}
				DPRINT("----------------------------\n");
				DPRINT("[INFO] student details is find successfully \n");
				DPRINT("----------------------------\n");
			}
			else
			{
				DPRINT("[ERROR] roll number %d not found \n" , roll);
				DPRINT("----------------------------\n");
			}
		}
		else
		{
			DPRINT("[ERROR] The number rolled must be less than or equal to \n\t the size of the database's roll numbers [%d] \n", size_buffer);
		}
	}
}

void find_student_by_first_name(FIFO_BUF_t * FIFO_buf)
{
	uint32_t flag_check_find = 0;
	element_type * student = FIFO_buf->tail;

	if(check_buffer_counter(FIFO_buf))
	{
		DPRINT("Enter the first name of the student :");
		fgets(f_name,20,stdin);
		DPRINT("----------------------------\n");
		DPRINT("the students details are :\n");
		DPRINT("----------------------------\n");
		for(i=0 ; i < FIFO_buf->counter ; ++i , ++student)
		{
			if(stricmp(student->first_name , f_name) == 0)
			{

				DPRINT("the first name is : %s" , student->first_name);
				DPRINT("the last  name is : %s" , student->last_name );
				DPRINT("the roll number is %d \n" , student->roll);
				DPRINT("the GPA is : %.1f \n", student->gpa);
				DPRINT("id of each course \n");
				for(j=0 ; j<max_courses ; ++j)
				{
					DPRINT("the course id %d \n", student->course_id[j]);
				}
				DPRINT("----------------------------\n");
				flag_check_find = 1;
			}
		}
		if(!flag_check_find)
		{
			DPRINT("[ERROR] first name %s not found \n" , f_name);
			DPRINT("----------------------------\n");
		}
	}
}

void find_course_enroll(FIFO_BUF_t * FIFO_buf)
{
	uint32_t flag_check_find = 0 , counter = 0;
	element_type * student = FIFO_buf->tail;
	if(check_buffer_counter(FIFO_buf))
	{
		DPRINT("Enter the course id :");
		scanf("%d" , &id);
		DPRINT("----------------------------\n");
		DPRINT("the students details are :\n");
		DPRINT("----------------------------\n");
		for(i=0 ; i<FIFO_buf->counter ; ++i , ++student)
		{
			for(j=0 ; j<max_courses ; ++j)
			{
				if(id == student->course_id[j])
				{

					DPRINT("the first name is : %s" , student->first_name);
					DPRINT("the last  name is : %s" , student->last_name);
					DPRINT("the roll number is %d \n" , student->roll);
					DPRINT("the GPA is : %.1f \n", student->gpa);
					flag_check_find = 1;
					counter++;
					DPRINT("----------------------------\n");
				}
			}
		}
		if(flag_check_find)
		{
			DPRINT("[INFO] total number of students enrolled : %d \n" , counter);
			DPRINT("----------------------------\n");
		}
		else
		{
			DPRINT("[ERROR] course id %d not found \n" , id);
			DPRINT("----------------------------\n");
		}
	}
}

void find_total_number_students(FIFO_BUF_t * FIFO_buf)
{
	if(check_buffer_counter(FIFO_buf)) print_message(FIFO_buf , total_students);
}


void delete_student(FIFO_BUF_t * FIFO_buf)
{
	uint32_t flag_check_find = 0 ;
	element_type * student = FIFO_buf->tail;
	if(check_buffer_counter(FIFO_buf))
	{
		DPRINT("Enter the roll number which you want to delete :");
		scanf("%d" , &roll);
		DPRINT("----------------------------\n");
		if(roll <= size_buffer)
		{
			if(check_roll(roll) == exist_roll)
			{
				student = return_student_roll(FIFO_buf , roll);
				move_tail(FIFO_buf , student);
				FIFO_dequeue_student(FIFO_buf);
				arr_roll[roll] = 0;
				flag_check_find = 1;
			}
			if(!flag_check_find)
			{
				DPRINT("[ERROR] this roll number %d not found \n" , roll);
				DPRINT("----------------------------\n");
			}
		}
		else
		{
			DPRINT("[ERROR] The number rolled must be less than or equal to \n\t the size of the database's roll numbers [%d] \n", size_buffer);
		}
	}
}

void update_student(FIFO_BUF_t * FIFO_buf)
{
	uint32_t flag_check_find = 0 , flag_wrong_option = 0 , option;
	element_type * student = FIFO_buf->tail;
	if(check_buffer_counter(FIFO_buf))
	{
		DPRINT("Enter the roll number to update the entry :");
		scanf("%d" , &roll);
		DPRINT("----------------------------\n");
		if(roll <= size_buffer)
		{
			if(check_roll(roll) == exist_roll)
			{
				student = return_student_roll(FIFO_buf , roll);
				DPRINT("1. first name\n");
				DPRINT("2. last name\n");
				DPRINT("3. roll number\n");
				DPRINT("4. GPA\n");
				DPRINT("5. courses\n");
				DPRINT("----------------------------\n");
				DPRINT("Enter option to update :");
				scanf("%d" , &option);
				DPRINT("----------------------------\n");
				switch(option)
				{
				case 1:
					DPRINT("Enter new first name :");
					fgets(student->first_name , 20 , stdin);
					break;
				case 2:
					DPRINT("Enter new last name :");
					fgets(student->last_name , 20 , stdin);
					break;
				case 3:
					check_again:
					DPRINT("Enter new roll :");
				scanf("%d" , &roll);
				if(roll <= size_buffer)
				{
					if(roll == student->roll)
					{
						DPRINT("[ERROR] the same current roll number %d\n" , roll);
						DPRINT("----------------------------\n");
						goto check_again;
					}
					else if(check_roll(roll) == not_exist_roll)
					{
						arr_roll[student->roll] = 0;
						student->roll = roll;
						arr_roll[roll] = 1;
					}
					else
					{
						DPRINT("[ERROR] roll number %d is already taken \n" , roll);
						DPRINT("----------------------------\n");
						goto check_again;
					}
				}
				else
				{
					DPRINT("[ERROR] The number rolled must be less than or equal to \n\t the size of the database's roll numbers [%d] \n", size_buffer);
					flag_wrong_option = 1;
				}
				break;
				case 4:
					DPRINT("Enter new GPA :");
					scanf("%f" , &student->gpa);
					break;
				case 5:
					for(j=0 ; j<max_courses ; j++)
					{
						DPRINT("Enter new course %d id : " , j+1 );
						scanf("%d" , &student->course_id[j]);
					}
					break;
				default :
					DPRINT("[ERROR] wrong option to updata \n");
					flag_wrong_option = 1;
				}
				flag_check_find = 1;
			}

			if(flag_check_find && !flag_wrong_option)
			{
				DPRINT("----------------------------\n");
				DPRINT("[INFO] update successfully \n");
				DPRINT("----------------------------\n");
			}
			else if(flag_wrong_option)
			{
				DPRINT("----------------------------\n");
				DPRINT("[ERROR] update failed \n");
				DPRINT("----------------------------\n");
			}
			else
			{
				DPRINT("[ERROR] roll %d not found \n" , roll);
				DPRINT("----------------------------\n");
			}
		}
		else
		{
			DPRINT("[ERROR] The number rolled must be less than or equal to \n\t the size of the database's roll numbers [%d] \n", size_buffer);
		}
	}
}

void display_all_student(FIFO_BUF_t * FIFO_buf)
{
	if(check_buffer_counter(FIFO_buf))
	{
		element_type * temp_tail = FIFO_buf->tail;
		DPRINT("display database students \n");
		for(i=0 ; i < FIFO_buf->counter ; ++i , ++temp_tail)
		{
			DPRINT("----------------------------\n");
			DPRINT("student first name  : %s" , temp_tail->first_name);
			DPRINT("student last name   : %s" , temp_tail->last_name);
			DPRINT("student roll number : %d\n" , temp_tail->roll);
			DPRINT("the GPA is : %.1f \n", temp_tail->gpa);
			for(j=0 ; j<max_courses ; ++j)
			{
				DPRINT("the course id %d is %d \n", i+1 , temp_tail->course_id[j]);
			}
		}
		DPRINT("----------------------------\n");
	}

}


void print_message(FIFO_BUF_t * FIFO_buf , uint32_t val)
{
	switch(val)
	{
	case enqueue_success:
		DPRINT("[INFO]  student details is add successfully \n");
		DPRINT("----------------------------\n");
		DPRINT("[INFO]  the total number of student is %d \n" , FIFO_buf->counter);
		DPRINT("[INFO]  you can add up to %d students \n" , size_buffer);
		DPRINT("[INFO]  you can add %d students \n" , FIFO_buf->length-FIFO_buf->counter);
		DPRINT("----------------------------\n");
		break;

	case dequeue_success:
		DPRINT("[[INFO] the roll number removed successfully \n");
		DPRINT("----------------------------\n");
		if(FIFO_buf->counter)
		{
			DPRINT("[INFO] the total number of student is %d \n" , FIFO_buf->counter);
			DPRINT("[INFO] you can add up to %d students \n" , size_buffer);
			DPRINT("[INFO] you can add %d students \n" , FIFO_buf->length-FIFO_buf->counter);
			DPRINT("----------------------------\n");
		}
		else
		{
			DPRINT("[INFO] you can add up to %d students \n" , size_buffer);
			DPRINT("[INFO] you can add %d students \n" , FIFO_buf->length-FIFO_buf->counter);
			DPRINT("----------------------------\n");
		}

		break;

	case total_students:
		DPRINT("[INFO] the total number of student is %d \n" , FIFO_buf->counter);
		DPRINT("[INFO] you can add up to %d students \n" , size_buffer);
		DPRINT("[INFO] you can add %d students \n" , FIFO_buf->length-FIFO_buf->counter);
		DPRINT("----------------------------\n");
		break;
	}
}

uint32_t check_roll (uint32_t roll)
{
	return (!arr_roll[roll] ? not_exist_roll : exist_roll);
}


element_type* return_student_roll (FIFO_BUF_t * FIFO_buf , uint32_t roll)
{
	Student_t * temp_tail = FIFO_buf->tail;
	for(i=0 ; i < FIFO_buf->counter ; ++i , ++temp_tail)
	{
		if(temp_tail->roll == roll)
			return temp_tail;
	}
}

uint32_t check_buffer_counter(FIFO_BUF_t * FIFO_buf)
{
	if(FIFO_buf->counter == 0)
	{
		DPRINT("[ERROR] not exist database students \n");
		DPRINT("----------------------------\n");
		return 0;
	}
	else return 1;
}

void move_tail(FIFO_BUF_t * FIFO_buf , Student_t * student)
{
	Student_t * temp_tail = student;
	while(temp_tail != FIFO_buf->tail)
	{
		*(temp_tail) = *(temp_tail - 1);
		--temp_tail;
	}
}
