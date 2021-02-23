
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
#include <stdint.h>
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
    // UCA0CTL0 = 0;
    UCA0BR0 = 104;      /*  104 From datasheet table- */
    UCA0BR1 = 0;        /* -selects baudrate =9600,clk = SMCLK*/
    UCA0MCTL = UCBRS_6; /* Modulation value = 6 from datasheet*/
    /* $4 */
    UCA0CTL1 &= ~UCSWRST;

    /* #5 */
    IE2 |= UCA0RXIE;
}

/* SourceId : UART_SourceId_002 */
/* DesignId : UART_DesignId_002 */
/*
*   @fn void uartPorts(int tx_bit, int rx_bit)
*   @brief Set TX and RX port bits
*
*   This function set the UART port.
*/
void uartPorts(int tx_bit, int rx_bit)
{
    P1SEL |= tx_bit | rx_bit;
    P1SEL2 |= tx_bit | rx_bit;
}

/* SourceId : UART_SourceId_003 */
/* DesignId : UART_DesignId_003 */
/*
*   @fn void sendCharacter(uint8_t c)
*   @brief send character
*
*   This function sendCharacter.
*/
void sendCharacter(uint8_t c)
{
    while (!(IFG2 & UCA0TXIFG))
        ;
    UCA0TXBUF = c;
}

/* SourceId : UART_SourceId_004 */
/* DesignId : UART_DesignId_004 */
/*
*   @fn void sendString(uint8_t str)
*   @brief send string
*
*/
void sendString(uint8_t *str)
{
    while (*str)
    {
        sendCharacter(*str);
        str++;
    }
}


void sciSendData(uint8_t *text, uint32_t length)
{
    uint8_t txt = 0;
    uint8_t txt1 = 0;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    text = text + (length - 1);
#endif

    while (length--)
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
        txt = *text--;
#else
        txt = *text++;
#endif

        txt1 = txt;

        txt &= ~(0xF0);
        txt1 &= ~(0x0F);
        txt1 = txt1 >> 4;

        if (txt <= 0x9)
        {
            txt += 0x30;
        }
        else if (txt > 0x9 && txt <= 0xF)
        {
            txt += 0x37;
        }
        else
        {
            txt = 0x30;
        }

        if (txt1 <= 0x9)
        {
            txt1 += 0x30;
        }
        else if ((txt1 > 0x9) && (txt1 <= 0xF))
        {
            txt1 += 0x37;
        }
        else
        {
            txt1 = 0x30;
        }
        sendCharacter(txt1);
        sendCharacter(txt);
    };
}