/*
 * delay.h
 *
 *  Created on: 25 de set de 2018
 *      Author: kevencastro7
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stm32f4xx_tim.h>
#include <stm32f4xx_rcc.h>

#define DELAY_TIM_FREQUENCY_US 1000000		/* = 1MHZ -> timer runs in microseconds */
#define DELAY_TIM_FREQUENCY_MS 1000			/* = 1kHZ -> timer runs in milliseconds */


/*
 *   Declare Functions
 */
void _init_us();
void _init_ms();
void _stop_timer();
extern void Delay_ms(uint32_t nTime);
extern void Delay_us(uint32_t nTime);



#endif /* DELAY_H_ */
