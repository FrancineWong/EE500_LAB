// simple RL-RTX application to blink an LED and
// to display 0-9 in a round robin fashion on LCD
// display of MCB1700 board
// this is meant to be a "hello world" example for
// RTX application development;

#include <stdio.h>
#include <LPC17xx.h>
#include <RTL.h>
#include "GLCD.h"
#include "LED.h"

#define __FI 1 // Use font index 16x24

// global counters will count 60 seconds up and down;
int g_counter1 = 0, g_counter2 = 60;  
char text_buffer[8];

int gpio2tmp;

// displays 0-9 in a round robin fashion
__task void task1(void)
{
    int i = 0;
		gpio2tmp = LPC_GPIO2->FIOPIN;
    //GLCD_DisplayString(3, 0, 1, "Task 1:");
		GLCD_DisplayString(3, 0, "Task 1:");
		//LPC_GPIO2->FIOPIN &= 0x00FF;
    LPC_GPIO2->FIOPIN = gpio2tmp;
    for (;;i++) {
        //GLCD_DisplayChar(3, 7, 1, i+'0');
				gpio2tmp = LPC_GPIO2->FIOPIN;
				GLCD_DisplayChar(3, 7, i+'0');
				//LPC_GPIO2->FIOPIN &= 0x00FF;
				LPC_GPIO2->FIOPIN = gpio2tmp;
        os_dly_wait(100);
        // Note1: The Delay function pauses the calling task by the amount 
        // of ticks passed as the argument. Control will switch to the 
        // next task ready else passes to the idle demon. After the 
        // specified number of ticks has expired, the calling task will 
        // be placed in the ready state. The delay does not use up 
        // processing time with a loop.        
        if (i == 9) {
            i = -1;
        }
				//LPC_GPIO2->FIOPIN &= 0xFF00;
				
    }
}

// toggles LED #7 at P2.6 every second
__task void task2(void)
{  
    //GLCD_DisplayString(4, 0, 1, "Task 2:LED");
		gpio2tmp = LPC_GPIO2->FIOPIN;
		GLCD_DisplayString(4, 0, "Task 2:LED");
		LPC_GPIO2->FIOPIN = gpio2tmp;
		//LPC_GPIO2->FIOPIN &= 0x00FF;
    for (;;) {
			
				LED_init();
				LED_on(7);
				//LED_on(0);
        os_dly_wait(60);
        LED_off(7);
				//LED_off(0);
        os_dly_wait(40);
    }
		
		//LPC_GPIO2->FIOPIN &= 0xFF00;
}

// task that keeps incrementing a global counter
__task void task3(void)
{
    //GLCD_DisplayString(5, 0, 1, "Task 3:");
		gpio2tmp = LPC_GPIO2->FIOPIN;
		GLCD_DisplayString(5, 0,  "Task 3:");
		LPC_GPIO2->FIOPIN = gpio2tmp;
		//LPC_GPIO2->FIOPIN &= 0x00FF;
    for (;;) {
        g_counter1++;
        if (g_counter1 == 60) g_counter1 = 0; // reset;
        os_dly_wait(100);
        sprintf(text_buffer, "%d", g_counter1);
        //GLCD_DisplayString(5, 7, __FI, (uint8_t*)text_buffer);
				gpio2tmp = LPC_GPIO2->FIOPIN;
				GLCD_DisplayString(5, 7, (uint8_t*)text_buffer);
				LPC_GPIO2->FIOPIN = gpio2tmp;
				//LPC_GPIO2->FIOPIN &= 0x00FF;
    }
}

// task that keeps decrementing a global counter
__task void task4(void)
{
    //GLCD_DisplayString(6, 0, 1, "Task 4:");
		gpio2tmp = LPC_GPIO2->FIOPIN;
		GLCD_DisplayString(6, 0,  "Task 4:");
		LPC_GPIO2->FIOPIN = gpio2tmp;
		//LPC_GPIO2->FIOPIN &= 0x00FF;
    for (;;) {
        g_counter2--;
        if (g_counter2 == 0) g_counter2 = 60; // reset;
        os_dly_wait(100);
        sprintf(text_buffer, "%d", g_counter2);
        //GLCD_DisplayString(6, 7, __FI, (uint8_t*)text_buffer);
				gpio2tmp = LPC_GPIO2->FIOPIN;
				GLCD_DisplayString(6, 7,  (uint8_t*)text_buffer);
				LPC_GPIO2->FIOPIN = gpio2tmp;
				//LPC_GPIO2->FIOPIN &= 0x00FF;
    }
}

// initialization task that spawns all other tasks
__task void init(void)
{
    os_tsk_create(task1, 1);  // task 1 at priority 1
    os_tsk_create(task2, 1);  // task 2 at priority 1
    os_tsk_create(task3, 1);  // task 3 at priority 1
    os_tsk_create(task4, 1);  // task 4 at priority 1
    os_tsk_delete_self();     // task must delete itself before exiting
}


int main(void)
{
		//int gpio2tmp;
    // (1) initialize the LPC17xx MCU;
    SystemInit(); 

    // (2) initialize GLCD and LED;
    LED_init();  
    GLCD_Init();    
    LED_on(0); // turn on LED #0 at P1.28

		gpio2tmp = LPC_GPIO2->FIOPIN;
	
    GLCD_Clear(Yellow);   
    //GLCD_DisplayString(0, 0, 1, "RTX Hello World! :-)");
		GLCD_DisplayString(0, 0, "RTX Hello World! :-)");
    //LPC_GPIO2->FIOPIN &= 0xFF00;
	//LED_on(0); // turn on LED #0 at P1.28
	
	LPC_GPIO2->FIOPIN = gpio2tmp;
	
    // (3) initilize the OS and start the first task
    os_sys_init( init);
}
