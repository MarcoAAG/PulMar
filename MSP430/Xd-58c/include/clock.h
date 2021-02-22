/*
 *   @clock.h
 *   @brief Clock Source Configuration File
 *   @date 19-Feb-2021
 *   @version 1.0
 *
 */

/*
 *  Created on: Feb 19, 2021
 *      Author: marco
 */

#ifndef CLOCK_H
#define CLOCK_H

#pragma once

/*
*   @enum setOptions
*   @brief set frecuancy values Definitions
*
*   Used with clockInit()
*/
enum setClock
{
    set_16Mhz = 1,
    set_12Mhz = 2,
    set_8Mhz = 3,
    set_1Mhz = 4,
};

/*
*   @enum clockReg
*   @brief Register value Definitions
*
*   Used with clockInit()
*/
enum clockReg
{
    DCO_16MHZ = 0x10F8,
    BC1_16MHZ = 0x10F9,
    DCO_12MHZ = 0x10FA,
    BC1_12MHZ = 0x10FB,
    DCO_8MHZ = 0x10FC,
    BC1_8MHZ = 0x10FD,
    DCO_1MHZ = 0x10FE,
    BC1_1MHZ = 0x10FF,

};

/* address memory variables */
extern unsigned char *DCO_ADDRESS;
extern unsigned char *BCS1_ADDRESS;

/* clock Function */
void clockInit(unsigned char dco_reg);

#endif
