/*
 * Message_Queue_FreeRTOS.c
 *
 * Created: 2/9/2024 4:24:14 AM
 *  Author: mohamed_elatar
 */ 

#include "lcd.h"
#include "Keybad.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h" 

void keypad(void *pv);
void LCD(void *pv);

QueueHandle_t my_queue ; //Void Pointer
int main(void)
{
    Keypad_vinit();
    LCD_vinit();

    // Create Tasks
    xTaskCreate(keypad,"Handle_1",100,NULL,2,NULL); // High Priority Task
    xTaskCreate(LCD,"Handle_2",100,NULL,1,NULL);    // Low Priority  Task

    // Create Queue With 5_Item (5Byte)
    my_queue=xQueueCreate(5,sizeof(uint8_t));

    //Start scheduler
    vTaskStartScheduler();
    
    while(1)
    {
        // Will Ignore Clear Screen As Run in High Priority For Tasks
        LCD_vClearScreen();
    }
}

//TASK_1
void keypad(void *pv)
{
    uint8_t Data_Keyapd;
    while(1)
    {
        // Read From Keypad
        Data_Keyapd=Keypad_u8read();
        if(Data_Keyapd!=NOT_PRESSED)
        {
            // wait for 1s in wait_state if queue full
            xQueueSend(my_queue,&Data_Keyapd,1000);
            // exit from run_state to wait_state until .3s
            vTaskDelay(300);
        }
    }
}

//TASK_2
void LCD(void *pv)
{
    uint8_t Display_Data;
    while(1)
    {
        // wait for 1s in wait_state if queue empty
        xQueueReceive(my_queue,&Display_Data,1000);
        LCD_vsend_number(Display_Data);
    }
}