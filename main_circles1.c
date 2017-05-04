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
#include "Serial.h"
#include "CRIS_UTILS.h"

#define __FI        1                        /* Font index 16x24               */

volatile unsigned short lcd_colors[] = { // 16 colors
    Black,Navy,DarkGreen,DarkCyan,Maroon,Purple,Olive,
    LightGrey,DarkGrey,Blue,Green,Cyan,Red,Magenta,Yellow,White};
volatile unsigned short last_color = Yellow;
volatile int last_x0=0, last_y0=0, last_r=1;
volatile int should_i_plot = 1; // think about it;

int main (void) 
{
    // (0) Initializations of GLCD and SER;
    //SER_Init();                              /* UART Initialization           */
    GLCD_Init();                             /* Initialize graphical LCD      */

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

    // (3) More one-time deals;  
    LPC_TIM0->TCR |= 1 << 0; // Start timer 
    LPC_SC->PCONP |= ( 1 << 15 ); // Power up GPIO 
    LPC_GPIO2->FIODIR |= 1 << 1; // Put P1.29 into output mode. LED is connected to P1.29

    // (4) loop forever;
    while (1) {
        last_x0 = rand() % 320 + 1; // last_x0 in the range 1-320
        last_y0 = rand() % 240 + 1; // last_r in the range 1-240
        last_r = rand() % 16 + 4; // last_r in the range 4-20
        last_color = lcd_colors[ rand() % 16 ];
        if ( should_i_plot == 1 ) { // that's the question
            GLCD_SetTextColor(last_color);
            CRIS_draw_circle(last_x0, last_y0, last_r);
            //CRIS_draw_circle_full(last_x0, last_y0, last_r);
            should_i_plot = 0;
        }
    }
}

// Here, we describe what should be done when the interrupt on Timer 0 is handled;
// We do that by writing this function, whose address is “recorded” in the vector table
// from file startup_LPC17xx.s under the name TIMER0_IRQHandler;
void TIMER0_IRQHandler(void)
{
    if ( (LPC_TIM0->IR & 0x01) == 0x01 ) // if MR0 interrupt 
    {
        LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag 
        // toggle the P0.29 LED;
        LPC_GPIO2->FIOPIN ^= 1 << 1; 
        // what does it do?
        should_i_plot = 1;
    }
}
