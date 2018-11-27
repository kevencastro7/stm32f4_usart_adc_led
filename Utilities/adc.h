/*
 * adc.h
 *
 *  Created on: 25 de set de 2018
 *      Author: kevencastro7
 */

#ifndef ADC_H_
#define ADC_H_
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4_discovery.h"


void adc_init();
uint16_t adc_read();
uint16_t adc_read_samples(uint16_t n);

#endif /* ADC_H_ */
