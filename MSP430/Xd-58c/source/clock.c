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

#include "clock.h"
#include <stdint.h>

/* SourceId : CLOCK_SourceId_001 */
/* DesignId : CLOCK_DesignId_001 */
/*
*   @fn clockInit(void)
*   @brief Clock Driver
*
*   This function set clock register at selected value.
* 
*/

void clockInit(unsigned char dco_reg)
{
    uint8_t *DCO_ADDRESS = 0x0056;
}
