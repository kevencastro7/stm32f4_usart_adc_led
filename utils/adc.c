/*
 * adc.c
 *
 *  Created on: 25 de set de 2018
 *      Author: kevencastro7
 */

#include "adc.h"

int ConvertedValue = 0;


void adc_init()
{
	 ADC_InitTypeDef ADC_init_structure;
	 GPIO_InitTypeDef GPIO_initStructre;
	 //Clock configuration
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);
	 //Analog pin configuration
	 GPIO_initStructre.GPIO_Pin = GPIO_Pin_0;
	 GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN;
	 GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOC,&GPIO_initStructre);
	 //ADC structure configuration
	 ADC_DeInit();
	 ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;
	 ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;
	 ADC_init_structure.ADC_ContinuousConvMode = ENABLE;
	 ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	 ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	 ADC_init_structure.ADC_NbrOfConversion = 1;
	 ADC_init_structure.ADC_ScanConvMode = DISABLE;
	 ADC_Init(ADC1,&ADC_init_structure);
	 //Enable ADC conversion
	 ADC_Cmd(ADC1,ENABLE);
	 //Select the channel to be read from
	 ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);
}
uint16_t adc_read()
{
	 ADC_SoftwareStartConv(ADC1);
	 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	 return ADC_GetConversionValue(ADC1);
}

uint16_t adc_read_samples(uint16_t n)
{
	uint16_t result = 0;
	for (int i = 0; i < n;i++)
	{
		result += adc_read();
	}
	result /= n;
	return result;
}
