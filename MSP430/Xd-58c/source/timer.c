/*
 *   @timer.h
 *   @brief TimerA Configuration File
 *   @date 22-Feb-2021
 *   @version 1.0
 *
 */

/*
 *  Created on: Feb 22, 2021
 *      Author: marco
 */

#include <msp430g2553.h>
#include <stdint.h>
#include "timer.h"

/* SourceId : TIMER_SourceId_001 */
/* DesignId : TIMER_DesignId_001 */
/*
*   @fn timerAInit(void)
*   @brief Clock Driver
*
*   This function set timer register.
* 
*/
void timerAInit(uint32_t delay)
{
    double period = 7.27; /* period in us*/
    uint16_t timer_ratio = (uint16_t) (delay / period);

    TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR; /* TASSEL_2 -> SMCLK */
                                             /* ID_3 -> Source clock divided by 8 */
                                             /* MC_1 -> Up mode */
                                             /* TACLR -> timer clear */
    TACCR0 = timer_ratio - 1;                /* count of Timer_A */
    CCTL0 = CCIE;                            /* Capture/compare interrupt enable. */

}
