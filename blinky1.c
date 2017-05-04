// blinky1.c
// Dr. Praveen Meduri, SUNY at Buffalo, 2013
// this program turns on and off the second LED from the group
// of 8 LED on the board;

// from the board's EM-LPC1700_User_Manual.pdf, LEDs on 
// the PowerAvr nxp lpc1768 board are as follows; this info is also written 
// on the actual PCB of the board itself, 
// next to each LED;

// 66 P2.7  I/O LED <---- last LED on the Board
// 67 P2.6  I/O LED
// 68 P2.5  I/O LED
// 69 P2.4  I/O LED
// 70 P2.3  I/O LED
// 73 P2.2  I/O LED
// 74 P2.1  I/O LED
// 75 P2.0  I/O LED <-- 1st LED on the Board

#include "LPC17xx.H" // LPC17xx definitions

// we'll use delay() as a software delay function; it should produce 
// about a second or so of delay depending on CCLK; a volatile variable 
// 'temp' is updated each time in the loop so that the compiler will not 
// optimize away the loop;
volatile uint32_t temp;
void delay( uint32_t del)
{
	uint32_t i;
	for ( i=0; i<del; i++)
		temp = i;
}

int main (void) 
{
	// to use any of the LPC1768 peripherals, the general steps to be followed are:
	// 1. Power Up the peripheral to be used
	// 2. Set the Clock Rate for the peripheral
	// 3. Connect necessary pins using Pin Connect Block
	// 4. Initialize the registers of the peripheral

	// (1) power up GPIO
	// in chapter 4: Clocking and Power Control of the LPC17xx manual
	// look for register Power Control for Peripherals register (PCONP);
	// it's on page 63; bit 15 is PGPIO; setting the bit to 1 should 
	// power up the GPIO ports; NOTE: that the default value is 1, 
	// which means GPIO is powered up by default on reset; but the 
	// start up code may modify this and it's good practice to make
	// sure we take care of things;
	LPC_SC->PCONP |= ( 1 << 15 );
	
	// (2) give the right clock to the peripheral
	// in the same chapter 4, look for Peripheral Clock Selection register ( PCLKSEL1 );
	// it's on page 57; bits 3:2 set the clock divider for GPIO; since we're not 
	// using interrupts, we wont change the default value. 
	// NOTE: PCLK refers to Peripheral Clock and CCLK refers to CPU Clock;
	// PCLK is obtained by dividing CCLK; see table 42 on page 57 of the manual;
	
	// (3) by default, GPIO pins are connected to the external pins;
	// so there is no need to change settings in the pin connect block;
	
	// (4) to see how to initialize ports, goto chapter 9 GPIO (on page 122);
	// set the corresponding bit of the register to make P2.0 an output pin;
	//LPC_GPIO2->FIODIR |= 1 << 0;
	// NOTE: with the above, the operation will be with all the other LEDs
	// being turned-on, which may be distracting to the eye; to have all LEDs
	// off, we could use alternatively:
	LPC_GPIO2->FIODIR = 0x000000FF; // P2.0, P2.1,...P2.7 pins/LEDs on port2 set as output
	
	// (5) turn on/off the LED driven by P2.0; 
	// NOTE: turning the LED on/off could also be achieved via FIOSET and FIOCLR;
	// in fact, using FIOSET and FIOCLR is the recommended method (as done in
	// blinky3.s example);
	while ( 1) {
        LPC_GPIO2->FIOPIN |= 1 << 0; // make P2.0 high 
		// to make pin P2.7 or 8th LED high we could use LPC_GPIO2->FIOPIN |= 1 << 7;
        delay( 1 << 24 ); // delay of about 1 s implemented in "software";
        LPC_GPIO2->FIOPIN &= ~( 1 << 0 ); // make P2.0 low
        delay( 1 << 24 );
  }
}
