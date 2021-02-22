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

/* Memory address */
unsigned char *DCO_ADDRESS = (unsigned char *)0x0056;
unsigned char *BCS1_ADDRESS = (unsigned char *)0x0057;

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
    switch (dco_reg)
    {
    case 1:
        *DCO_ADDRESS = (unsigned char)DCO_16MHZ;
        *BCS1_ADDRESS = (unsigned char)BC1_16MHZ;
        break;
    case 2:
        *DCO_ADDRESS = (unsigned char)DCO_12MHZ;
        *BCS1_ADDRESS = (unsigned char)BC1_12MHZ;
        break;
    case 3:
        *DCO_ADDRESS = (unsigned char)DCO_8MHZ;
        *BCS1_ADDRESS = (unsigned char)BC1_8MHZ;
        break;
    case 4:
        *DCO_ADDRESS = (unsigned char)DCO_1MHZ;
        *BCS1_ADDRESS = (unsigned char)BC1_1MHZ;
        break;

    default:
        *DCO_ADDRESS = (unsigned char)DCO_1MHZ;
        *BCS1_ADDRESS = (unsigned char)BC1_1MHZ;
        break;
    }

}
