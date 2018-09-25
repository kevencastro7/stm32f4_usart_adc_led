/*
 * port.c
 *
 *  Created on: Mar 21, 2018
 *      Author: jmorais
 */

#include <port.h>

void port_init(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq (&RCC_Clocks);
	(void) SysTick_Config (RCC_Clocks.HCLK_Frequency / (3132));
}

void SysTick_Handler (void)
{
	millis++;
}

uint32_t port_millis( void )
{
	return millis;
}

void port_sleep_ms( uint32_t delay )
{
	uint32_t start = millis;
	while((millis - start) <= delay);
}

