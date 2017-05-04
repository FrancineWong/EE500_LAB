//
// Cris, Feb. 2013
// this is a simple example, which draws randomly circles
// of different colors at different locations and of different 
// sizes;
//

#include <stdio.h>
#include <stdlib.h>
#include "LPC17xx.H"                         /* LPC17xx definitions           */
#include "GLCD.h"
#include "joystick.h"
#include "CRIS_UTILS.h"

#define __FI        1                        /* Font index 16x24               */
//volatile int Cannon_Pos=145;//x position of cannon
//int Cannon_Vert=195;//y position of cannon
//volatile int Bullet_yPos;
//volatile int Bullet_xPos;

int Fire;
int playshoot;
char moveCannon = 0;
char moveLeft=0;




//volatile unsigned short lcd_colors[] = { // 16 colors
//   // Black,Navy,DarkGreen,DarkCyan,Maroon,Purple,Olive,
//  //  LightGrey,DarkGrey,Blue,Green,Cyan,Red,Magenta,Yellow,White
//	Blue};
//volatile unsigned short last_color = Yellow;
//volatile int last_x0=0, last_y0=0, last_r=1;


int main (void) 
{   // (0) Initializations of GLCD and SER;
    //SER_Init();                              /* UART Initialization           */
	  SystemInit();
	    LPC_PINCON->PINSEL1 &=~((0x03<<18)|(0x03<<20));  
      /* P0.25, A0.0, function 01, P0.26 AOUT, function 10 */
      LPC_PINCON->PINSEL1 |= ((0x01<<18)|(0x02<<20));
    GLCD_Init();                             /* Initialize graphical LCD      */
	
	//initialize Joystick
    LPC_GPIO1->FIODIR   &= ~((1<<25)|(1<<26)|(1<<27)|(1<<28)|(1<<29));
	
    GLCD_Clear(Black); // Clear graphical LCD display
    //GLCD_SetTextColor(last_color);
    
//    // (1) Timer 0 configuration 
//    LPC_SC->PCONP |= 1 << 1; // Power up Timer 0 
//    LPC_SC->PCLKSEL0 |= 1 << 2; // Clock for timer = CCLK, i.e., CPU Clock (
//    LPC_TIM0->MR0 = 1 << 24; // 24: give a value suitable for the LED blinking 
//                             // frequency based on the clock frequency 
//    LPC_TIM0->MCR |= 1 << 0; // Interrupt on Match 0 compare 
//    LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0    
//    LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer 0 (forced); 
//    LPC_TIM0->TCR &= ~(1 << 1); // Stop resetting the timer 
//    // (2) Enable timer interrupt; 
//    NVIC_EnableIRQ(TIMER0_IRQn);

//    // (3) More one-time deals;  
//    LPC_TIM0->TCR |= 1 << 0; // Start timer 
//    LPC_SC->PCONP |= ( 1 << 15 ); // Power up GPIO 
//    LPC_GPIO2->FIODIR |= 1 << 1; // Put P1.29 into output mode. LED is connected to P1.29


 //Set up timer 1 
    LPC_SC->PCONP |= 1 << 2; // Power up Timer 1
    LPC_SC->PCLKSEL0 |= 1 << 4; // Clock for timer = CCLK, i.e., CPU Clock 
	  LPC_TIM1->MR0 = 1 << 18;  // Give a value suitable for the LED blinking 
                             // frequency based on the clock frequency 
    LPC_TIM1->MCR |= 1 << 0; // Interrupt on Match 1 compare 
	  LPC_TIM1->MCR |= 1 << 1; // Reset timer on Match 0 
	  LPC_TIM1->TCR |= 1 << 1; // Manually Reset Timer 1 (forced); 
    LPC_TIM1->TCR &= ~(1 << 1); // Stop resetting the timer 
	  //NVIC_SET_PRIORITY(TIMER1_IRQn, 2);
    NVIC_EnableIRQ(TIMER1_IRQn); // enable timer1 interrupt source
    LPC_TIM1->TCR |= 1 << 0; // Start timer
    
    

    // (4) loop forever;
    while (1) {
			  
			  Draw_Cannon(150,180);
			if (JOYSTICK_GetKeys ()==JOYSTICK_LEFT) {//Checks to see if joystick left is pressed
				moveCannon = 1;//Controls movement in timer
			 }
			  if (JOYSTICK_GetKeys ()==JOYSTICK_RIGHT) {//Checks to see if joystick right is pressed
				moveCannon = 2;//Controls movement in timer
			 }
				if ((JOYSTICK_GetKeys () == JOYSTICK_CENTER) & (Bullet_yPos <= 0)) {//checks to see if joystick center is pressed, can only fire if bullet is not on screen
						//GLCD_SetTextColor(last_color); 
						Draw_Bullet();//Draws bullet
						Fire = 1;//Controls movement up in timer
						delay(100000);//Delays to ensure that more than one bullet is not fired
						}
					if (Bullet_yPos>0)//if bullet is on the screen, keep moving it up
						Fire=1;//Controls movement upward in timer
					else 
						Fire=0;//Stops upward movement in timer
					if (moveCannon == 1)
						Move_Cannon_Left();
					if (moveCannon== 2)
						Move_Cannon_Right();
					moveCannon = 0;
    }
}

// Here, we describe what should be done when the interrupt on Timer 0 is handled;
// We do that by writing this function, whose address is “recorded” in the vector table
// from file startup_LPC17xx.s under the name TIMER0_IRQHandler;

void TIMER1_IRQHandler(void) 
	{
    LPC_TIM1->IR |= 1 << 0; // Clear MR0 interrupt flag
	if (1) {

 //****************Cannon Movement**************
		if (moveCannon == 1)
			Move_Cannon_Left();
		if (moveCannon== 2)
			Move_Cannon_Right();
		moveCannon = 0;
        //***************************************        
   //***************Bullets************************* 
        if (Fire==1)
			Move_Bullet_Up();

	//****************************************************
 
			}
		}

//void TIMER0_IRQHandler(void)
//{
//    if ( (LPC_TIM0->IR & 0x01) == 0x01 ) // if MR0 interrupt 
//    {
//        LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag 
//        // toggle the P0.29 LED;
//        LPC_GPIO2->FIOPIN ^= 1 << 1;
//			
//			  while(1) {
//					
//					if (Fire==1)
//						Move_Bullet_Up();
//					
//    }
//}
//}
