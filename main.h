/*
 * main.h
 *
 *  Created on: Mar 31, 2023
 *      Author: ecelab
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <msp430g2553.h>

void io_init(void);
void clock_init(void);

void timerA_init(void);

static inline void delay(void)
{
  volatile int jj;
  volatile int ii;
  for (ii = 0; ii < 4; ii++)
  {
    for (jj = 0; jj < 1000; jj++)
    {
      asm(" nop"); //The space is necessary or else the assembler things nop is a label!
    }
  }
}

// Event timing
#define MCLK_RATE       1000000 // Hz
#define SMCLK_RATE      1000000 // Hz
#define ACLK_RATE        125000 // Hz
#define TICK_RATE           100 // Hz
#define STATUS_COUNT          5 // Number of ticks per event: ~0.1 sec
#define CAN_COMMS_COUNT     100 // Number of ticks per event: 1.0 sec
#define QSEC_COUNT           25 // Number of ticks per event: 1.0 sec

// Constant Definitions
#define TRUE            1
#define FALSE           0

// PORT 1
#define LED0            0x01
#define CAN_SOMI        0x02
#define CAN_SIMO        0x04
#define CAN_CSn         0x08
#define CAN_SCLK        0x10
#define CAN_INTn        0x20
#define CAN_RSTn        0x40
//#define Pin7          0x80
#define P1_UNUSED       0x80

// PORT 2
#define Horn             0x01
#define Left             0x02
#define Right            0x04
#define Regen            0x08
#define Cruise           0x10
//#define                0x20
//#define XTIN           0x40
//#define XTOUT          0x80
#define P2_UNUSED        0x20 | 0x40 | 0x80

#define LED_ERROR_ON        P1OUT |= LED0;
#define LED_ERROR_TOG       P1OUT ^= LED0;
#define LED_ERROR_OFF       P1OUT &= ~LED0;


#endif /* MAIN_H_ */
