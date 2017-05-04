// this is adapted from the example:
// C:\Keil\ARM\Boards\Keil\MCB1700\emWin\GUIDemo
// purpose: low level joystick functions
 
#include <LPC17xx.h> 
#include "joystick.h"

//void JOYSTICK_Init (void) {
//    // configure P1.20,23..26 as inputs from Joystick----------MCD1700
//    
//    // P1.20, P1.23..26 is GPIO
//    LPC_PINCON->PINSEL3 &= ~((3<< 8)|(3<<14)|(3<<16)|(3<<18)|(3<<20)); 
//    // P1.25, P1.26..29 is input direction          
//    LPC_GPIO1->FIODIR   &= ~((1<<25)|(1<<26)|(1<<27)|(1<<28)|(1<<29));    
//}


uint32_t JOYSTICK_GetKeys (void) {
    // Get joystick direction keys state
    // Return: joystick directions bitmask
    uint32_t p, val = 0;

    p = (LPC_GPIO1->FIOPIN>>25)&0x1F;
    if ((p & 0x02) == 0) {
        val |= JOYSTICK_LEFT;
    }
    if ((p & 0x10) == 0) {
        val |= JOYSTICK_RIGHT;
    }

    if ((p & 0x01) == 0) {
        val |= JOYSTICK_CENTER;
    }
    return (val);
}
