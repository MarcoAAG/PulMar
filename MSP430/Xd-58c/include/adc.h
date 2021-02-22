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


#ifndef ADC_H
#define ADC_H

#include<stdint.h>

/* adc Function */
void adcInit(void);
uint16_t readSingChanAdc(void);
#endif
