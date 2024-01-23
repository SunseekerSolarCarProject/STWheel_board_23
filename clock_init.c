/*
 * Clock Initialization Code msp430g2955
 * Initialize Clock Source XT @ 16MHz
 *
 * Sunseeker StWheel 2023
 *
  * Main CLK    :  MCLK  = Default     = 1 MHz
 * Sub-Main CLK :  SMCLK = Default     = 1 MHz
 * Aux CLK      :  ACLK  = XT1     =  MCLK/8 MHz
 *
 */

#include "main.h"

void clock_init(void)
{

    //******************************************************************************
    //  MSP430G2xx3 Demo - Basic Clock, Output Buffered clocks with preloaded DCO
    //                     calibration constants for BCSCTL1 and DCOCTL.
    //  Description: Buffer ACLK on P1.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
    //  P1.1. DCO is software selectable to 1, 8, 12, or 16Mhz using calibration
    //  contstants in INFOA.
    //

    volatile unsigned int i;

    //1Mhz
     if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
     {
       while(1);                               // do not load, trap CPU!!
     }
     DCOCTL = 0;                               // Select lowest DCOx and MODx settings
     BCSCTL1 = CALBC1_1MHZ;                    // Set range
     DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation */

   /* //8Mhz
     if (CALBC1_8MHZ==0xFF)                    // If calibration constant erased
     {
       while(1);                               // do not load, trap CPU!!
     }
     DCOCTL = 0;                               // Select lowest DCOx and MODx settings
     BCSCTL1 = CALBC1_8MHZ;                    // Set range
     DCOCTL = CALDCO_8MHZ;                     // Set DCO step + modulation */

    do
    {
      IFG1 &= ~OFIFG;                         // Clear OSCFault flag
      for (i = 0xFF; i > 0; i--);             // Time for flag to set
    }
    while (IFG1 & OFIFG);                     // OSCFault flag still set?

    BCSCTL1 |= DIVA_3;                        // Div A =/8
    BCSCTL2 |= SELM_0 | DIVM_0;                        // MCLK = LFXT1 (safe)

}


