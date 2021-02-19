/*
 *   @uart.h
 *   @brief UART Driver Definition File
 *   @date 18-Feb-2021
 *   @version 1.0
 *
 */

 /*
 *  Created on: Feb 18, 2021
 *      Author: marco
 */

#ifndef UART_H_
#define UART_H_
#pragma once

#include <stdint.h>

/*
*   @enum clockSource
*   @brief Source clock Definitions
*
*   Used with uartInit()
*/
enum clockSource
{
    UCLK = 0x00,
    ACLK = 0x40,
    SMCLK = 0x80,
};

/*
*   @enum regOptions
*   @brief register values Definitions
*
*   Used with uartInit()
*/
enum regOptions
{
    PARITY_DISABLE = 0X00,
    PARITY_ENABLE = 0X80,
    ODD_PARITY = 0X00,
    EVEN_PARITY = 0X40,
    LSB_FIRST = 0X00,
    MSB_FIRST = 0X20,
    DATA_8_BIT = 0X00,
    DATA_7_BIT = 0X10,
    ONE_STOP_BIT = 0X00,
    TWO_STOP_BIT = 0X08,
};


typedef struct uart_settings
{
    uint8_t parity_enable;
    uint8_t parity;
    uint8_t msb_or_lsb;
    uint8_t length_data;
    uint8_t stop_bit;
    uint8_t clk_source;
}uart_reg;

/* Define port bit*/
#define RX 0x01;
#define TX 0x02; 

/* UART Interface Functions */
void uartInit(uart_reg *uart);
void sendCharacter(uint8_t);
void sendString(uint8_t);





#endif /* UART_H_ */
