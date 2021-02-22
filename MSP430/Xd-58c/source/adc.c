/*
 *   @adc.h
 *   @brief adc10 Configuration File
 *   @date 22-Feb-2021
 *   @version 1.0
 *
 */

/*
 *  Created on: Feb 22, 2021
 *      Author: marco
 */

#include <msp430g2553.h>
#include "adc.h"
#include <stdint.h>


/* SourceId : ADC_SourceId_001 */
/* DesignId : ADC_DesignId_001 */
/*
*   @fn adcInit(void)
*   @brief Initializes the ADC Driver
*
*   This function initializes the ADC10 module.
*/
void adcInit(void)
{
    ADC10CTL0 &= ~ENC;

    ADC10CTL1 = INCH_0 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0 | CONSEQ_0;

    ADC10AE0 = BIT0;

    ADC10CTL0 = SREF_0 | ADC10SHT_0 | ADC10ON;
}

/* SourceId : ADC_SourceId_002 */
/* DesignId : ADC_DesignId_002 */
/*
*   @fn adcInit(void)
*   @brief Read single channel 
*
*   This function initializes the ADC10 module.
*/
uint16_t readSingChanAdc(void)
{
    uint16_t data_raw;

    ADC10CTL0 |= ENC | ADC10SC;
    data_raw = ADC10MEM;
    ADC10CTL0 &= ~ENC | ~ADC10SC;
    return data_raw;

}
