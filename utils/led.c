/*
 * led.c
 *
 *  Created on: 24 de set de 2018
 *      Author: kevencastro7
 */
#include "led.h"

void led_init ( void )
{
		GPIO_InitTypeDef gpio;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		gpio.GPIO_Pin = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &gpio);

}

void led_write(uint16_t GPIO_Pin, BitAction BitVal)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin, BitVal);
}

