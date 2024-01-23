/**
 * CAN TEST
 */
#include <msp430g2553.h>
#include "main.h"
#include "can.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    _DINT();                                    // Disables interrupts

    io_init();
    delay();

    clock_init();                               // Configure HF and LF clocks
    delay();

    timerB_init();
    delay();

    canspi_init();
    can_init();
    can_DC_rcv_count = 0;
    old_DC_rcv_count = 0;

    _EINT();                                    // Enable global interrupts

	return 0;
}

/*
* Initialise Timer A
*   - Provides timer tick timebase at 100 Hz
*/
void timera_init( void )
{
  TBCTL = CNTL_0 | TBSSEL_1 | ID_3 | TBCLGRP_0;     // ACLK/8, clear TBR
  TBCCR0 = (ACLK_RATE/8/TICK_RATE);             // Set timer to count to this value = TICK_RATE overflow
  TBCCTL0 = CCIE;                               // Enable CCR0 interrrupt
  TBCTL |= MC_1;                                // Set timer to 'up' count mode
}

/*
* Timer A CCR0 Interrupt Service Routine
*   - Interrupts on Timer A CCR0 match at 10Hz
*   - Sets Time_Flag variable
*/
/*
* GNU interropt symantics
* interrupt(TIMERB0_VECTOR) timer_b0(void)
*/
#pragma vector = TIMERA0_VECTOR
__interrupt void timer_a0(void)
{
    static unsigned int status_count = STATUS_COUNT;
    static unsigned int cancomm_count = CAN_COMMS_COUNT;
    static unsigned int qsec_count = QSEC_COUNT;

    // Primary System Heartbeat
    status_count--;
    if( status_count == 0 )
    {
        status_count = STATUS_COUNT;
        status_flag = TRUE;
    }

    qsec_count--;
    if( qsec_count == 0 )
    {
        qsec_count = QSEC_COUNT;
        qsec_flag = TRUE;
    }

    // Periodic CAN Satus Transmission
    if(send_can) cancomm_count--;
    if( cancomm_count == 0 )
    {
        cancomm_count = CAN_COMMS_COUNT;
        cancomm_flag = TRUE;
    }
}

