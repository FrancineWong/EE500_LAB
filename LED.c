/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: MCB1700 low level LED functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "LED.h"

//const unsigned long led_mask[] = { 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7 };
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3,
                                   1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };


/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_init (void) {
  
	int ii;
	LPC_GPIO2->FIODIR |= 0x000000FF;                 /* LEDs on PORT2  */
	for(ii=0;ii<8;ii++)
	{
	LPC_GPIO2->FIOPIN &= ~( 1 <<ii );	
	}
}


/*----------------------------------------------------------------------------
  Switch LED on. LED = Bitposition
 *----------------------------------------------------------------------------*/
void LED_on  (unsigned char led) {
  int i;

  //for (i = 0; i < LED_NUM; i++) 
	{
    //if (led & (1<<i)) 
			{
      //LPC_GPIO2->FIOPIN |= led_mask[i];
			LPC_GPIO2->FIOPIN |= led_mask[led];
    }
  }
}

/*----------------------------------------------------------------------------
  Switch Led off. LED = Bitposition
 *----------------------------------------------------------------------------*/
void LED_off (unsigned char led) {
  int i;

  //for (i = 0; i < LED_NUM; i++) 
	{
    //if (led & (1<<i)) 
			{
      //LPC_GPIO2->FIOPIN &= ~led_mask[i];
			LPC_GPIO2->FIOPIN &= ~led_mask[led];
    }
  }
}

/*----------------------------------------------------------------------------
  Output value to LEDs
 *----------------------------------------------------------------------------*/
void LED_out (unsigned char led) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (led & (1<<i)) {
      LPC_GPIO2->FIOPIN |= led_mask[i];
    } else {
      LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}
