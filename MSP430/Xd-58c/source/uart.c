
/*
*   @file uart.c 
*   @brief UART Driver Implementation File
*   @date 18-Feb-2021
*   @version 1.0
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

#include <msp430g2553.h>
#include "uart.h"


/* SourceId : UART_SourceId_001 */
/* DesignId : UART_DesignId_001 */
/*
*   @fn uartInit(void)
*   @brief Initializes the SCI Driver
*
*   This function initializes the SCI module.
* 
*   Steps to initializes and set UART module
        *1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1)
        *2. Initialize all USCI registers with UCSWRST = 1 (including UCAxCTL1) 
        *3. Configure ports.
        *4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCAxCTL1) 
        *5. Enable interrupts (optional) via UCAxRXIE and/or UCAxTXIE 
*/
void uartInit(uart_reg *uart)
{


    /* #1 */
    UCA0CTL1 = UCSWRST;

    /* #2 */

    UCA0CTL1 |= uart->clk_source;

    /* #3 */
    UCA0CTL0 = 0;
    UCA0CTL0 |= uart->parity_enable | uart->parity | uart->msb_or_lsb | uart->length_data | uart->stop_bit;

    /* $4 */
    UCA0CTL1 &= ~UCSWRST;

    /* #5 */
    IE2 |= UCA0RXIE;
}
