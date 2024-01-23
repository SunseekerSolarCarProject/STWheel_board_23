/*
 * Battery Protection Software for BPS PCB Development
 * Originally Written for BPS_V1 2012
 *
 * Modified for BPS_V2 2015 by Scott Haver
 * WMU Sunseeker 2015
 *
 *  I/O Initialization
 */

// Include files
#include "main.h"

/*
 * Initialise I/O port directions and states
 * Drive unused pins as outputs to avoid floating inputs
 *
 */
void io_init( void )
{
	/******************************PORT 1**************************************/
	P1OUT = 0x00;		   				                    // Pull pins low
  	P1DIR = LED0 | CAN_CSn| CAN_SIMO | CAN_SCLK | CAN_RSTn | P1_UNUSED;	//set to output
    P1DIR &= ~(CAN_SOMI | CAN_INTn);
    P1OUT |= LED0 | CAN_CSn | CAN_SIMO | CAN_SCLK | CAN_RSTn;

    P1SEL = CAN_SIMO | CAN_SOMI | CAN_SCLK;

    delay();
    P1OUT &= ~(CAN_RSTn);          // Pull pins low
    delay();
    P1OUT |= (CAN_RSTn);           // Pull pins high

	/*Interrupts Enable*/
	//    P1SEL = ;
    //    P1IE  = ;
    //    P1IE  |=;
    delay();

	/******************************PORT 2**************************************/
	P2OUT = 0x00;			// Pull pins low
    P2DIR = P2_UNUSED;      //set to output
    P2DIR &= ~(Horn | Left | Right | Regen | Cruise);      //set to output
    /*Interrupts Enable */
    P2OUT |= (CAN_RSTn);           // Pull pins low

    //    P2SEL = ; //Interrupts
	//    P2IE  = ; // Enable Interrupts
	//    P2SEL |= ;
	//    P2IES |= ;
	//	  P2IE  |= ;
    P2IFG = 0x00;       				//Clears all interrupt flags on Port 2
    delay();

}


