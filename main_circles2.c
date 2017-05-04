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
//#include "Serial.h"
#include "CRIS_UTILS.h"

#define __FI        1                        /* Font index 16x24               */


//volatile int Cannon_Pos=145;//x position of cannon
//int Cannon_Vert=195;//y position of cannon
//volatile int Bullet_yPos;
//volatile int Bullet_xPos;
volatile int Cannon_Pos=145;//x position of cannon
int Cannon_Vert=195;//y position of cannon
volatile int Bullet_yPos;
volatile int Bullet_xPos;
char moveCannon = 0;
char moveLeft=0;
int Fire=0;
void Draw_Cannon(int x0, int y0)
{
    GLCD_SetTextColor(Green);
    Draw_Rect(x0,y0,100,50);
    Draw_Rect(x0+10,y0-10,80,10);
	  Draw_Rect(x0+10,y0+50,80,10);
}
void Draw_Bullet(void)
{
	Bullet_yPos=179;
	GLCD_SetTextColor(White);
	Bullet_xPos=Cannon_Pos;
	Draw_Rect(Cannon_Pos+40,Bullet_yPos+10,20,20);
	Draw_Rect(Cannon_Pos+45,Bullet_yPos,10,10);
}

volatile unsigned short lcd_colors[] = { // 16 colors
   // Black,Navy,DarkGreen,DarkCyan,Maroon,Purple,Olive,
  //  LightGrey,DarkGrey,Blue,Green,Cyan,Red,Magenta,Yellow,White
	Blue};
volatile unsigned short last_color = Yellow;
//volatile int last_x0=0, last_y0=0, last_r=1;


int main (void) 
{
	 unit8_t joystickVal;
    // (0) Initializations of GLCD and SER;
    //SER_Init();                              /* UART Initialization           */
    GLCD_Init();                             /* Initialize graphical LCD      */
	  //Initialize Joystick
    LPC_GPIO1->FIODIR   &= ~((1<<25)|(1<<26)|(1<<27)|(1<<28)|(1<<29));  
	
    GLCD_Clear(Black); // Clear graphical LCD display
    GLCD_SetTextColor(last_color);
    
    // (1) Timer 0 configuration 
    LPC_SC->PCONP |= 1 << 1; // Power up Timer 0 
    LPC_SC->PCLKSEL0 |= 1 << 2; // Clock for timer = CCLK, i.e., CPU Clock (
    LPC_TIM0->MR0 = 1 << 24; // 24: give a value suitable for the LED blinking 
                             // frequency based on the clock frequency 
    LPC_TIM0->MCR |= 1 << 0; // Interrupt on Match 0 compare 
    LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0    
    LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer 0 (forced); 
    LPC_TIM0->TCR &= ~(1 << 1); // Stop resetting the timer 

    // (2) Enable timer interrupt; 
    NVIC_EnableIRQ(TIMER0_IRQn);
		
		//set external pushbutton
		LPC_GPIOINT->IO2IntEnr|=1<<10;
		NVIC_EnableIRQ(EINT3_IRQn);
		GLCD_Clear(Black);
		Draw_Cannon(145,150);

    // (3) More one-time deals;  
    
//    LPC_SC->PCONP |= ( 1 << 15 ); // Power up GPIO 
//    LPC_GPIO2->FIODIR |= 1 << 1; // Put P1.29 into output mode. LED is connected to P1.29

    // (4) loop forever;
    while (1) {
			LPC_TIM0->TCR |= 1 << 0; // Start timer 
			joystickVal=(LPC_GPIO1->FIOPIN>>25)&0x1F;
			if((joystickVal&0x02)==0)
			{
			Draw_Cannon(Cannon_Pos, Cannon_Vert);
				if(cannon_position-20<0)
				{}
					else
					{
					cannon_position-=4;
					}
					Draw_Cannon(Cannon_Pos, 0);
			}
			if((jotstickVal&0x10)==0)
			{
			Draw_Cannon(Cannon_Pos, 1);
				if(Cannon_Pos+20>320)
				{}
					else
					{
					Cannon_Pos+=4;
					}
					Draw_Cannon(Cannon_Pos, 0);
			}
			LPC->TIM0->TCR|=1;
			for(k=0;k<500000;k++);
//			if (JOYSTICK_GetKeys ()==JOYSTICK_LEFT) {//Checks to see if joystick left is pressed
//				moveCannon = 1;//Controls movement in timer
//			 }
//			  if (JOYSTICK_GetKeys ()==JOYSTICK_RIGHT) {//Checks to see if joystick right is pressed
//				moveCannon = 2;//Controls movement in timer
//			 }
//			 //Cannon Bullet Fire
//			 if ((JOYSTICK_GetKeys () == JOYSTICK_CENTER) & (Bullet_yPos <= 0)) {//checks to see if joystick center is pressed, can only fire if bullet is not on screen
//				 Draw_Bullet();//Draws bullet
//				 Fire = 1;//Controls movement up in timer
//				 delay(100000);//Delays to ensure that more than one bullet is not fired
//			 }
//			 if (Bullet_yPos>10)//if bullet is on the screen, keep moving it up
//				 Fire=1;//Controls movement upward in timer
//			 else 
//				 Fire=0;//Stops upward movement in timer
//    }
}

// Here, we describe what should be done when the interrupt on Timer 0 is handled;
// We do that by writing this function, whose address is “recorded” in the vector table
// from file startup_LPC17xx.s under the name TIMER0_IRQHandler;
void EINT3_IRQHandler(void)
{
LPC_GPIOINT->IO2IntClr|=1<<10;
	if(Bullet_xPos<0&&Bullet_yPos<0)
	{
	Bullet_xPos=Cannon_Pos;
		Bullet_yPos=180;
	}
}

void TIMER0_IRQHandler(void)
{

    if ( (LPC_TIM0->IR & 0x01) == 0x01 ) // if MR0 interrupt 
    {
        LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag 
        // toggle the P0.29 LED;
        LPC_GPIO2->FIOPIN ^= 1 << 1;
			if(Bullet_xPos>0&&Bullet_yPos>0)
			{
			Draw_Bullet(Bullet_xPos, Bullet_yPos);
				Bullet_yPos-=10;
				if(Bullet_yPos==0)
				{
				Bullet_yPos=-10;
					return;
				}
				Draw_Bullet(Bullet_xPos, Bullet_yPos);
			}
			  while(1) {//Play controls each life
            
	 }
	 
			  
					}
			 
    }
}
