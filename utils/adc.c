/*
 * adc.c
 *
 *  Created on: 25 de set de 2018
 *      Author: kevencastro7
 */

#include "adc.h"

int ConvertedValue = 0;

																	//------------------COMENTÁRIOS-------------------//

void adc_init()														// Inicialização
{
	 ADC_InitTypeDef ADC_init_structure;							// Struct do ADC
	 GPIO_InitTypeDef GPIO_initStructre;							// Struct da GPIO
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//-------------Configuração do Clock--------------//
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);			// Ativar clock no ADC
	 RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);			// Ativar clock na GPIO
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//------------------------------------------------//

	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//--------Configuração do Pino Analógico----------//
	 GPIO_initStructre.GPIO_Pin = GPIO_Pin_0;						// Utilizar o Pino 1
	 GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN;					// Modo de operação analógico
	 GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL;				// Sem Pull-up/Pull-down
	 GPIO_Init(GPIOC,&GPIO_initStructre);							// Incialização da GPIO
	 	 	 	 													//------------------------------------------------//

	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//---------Configuração da sctruct do adc---------//
	 ADC_DeInit();
	 ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;		// Alinhamento de dados na direita
	 ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;		// Resolução de 12 bits
	 ADC_init_structure.ADC_ContinuousConvMode = ENABLE;			// Modo de Conversão contínua
	 ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	 ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	 ADC_init_structure.ADC_NbrOfConversion = 1;					// Número de conversões
	 ADC_init_structure.ADC_ScanConvMode = DISABLE;					// Apenas um canal
	 ADC_Init(ADC1,&ADC_init_structure);							// Inicialização do ADC
																	//------------------------------------------------//

	 //Enable ADC conversion
	 ADC_Cmd(ADC1,ENABLE);											// Habilitar conversão do ADC
	 //Select the channel to be read from
	 ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_3Cycles); // Canal Utilizado e 3 ciclos de clocks/amostra
}
uint16_t adc_read()													// Leitura do ADC
{
	 ADC_SoftwareStartConv(ADC1);									// Iniciar a Conversão
	 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));					// Espera acabar a conversão
	 return ADC_GetConversionValue(ADC1);							// Retorna oa valor convertido
}

uint16_t adc_read_samples(uint16_t n)								// Leitura de N amostras
{
	uint16_t result = 0;
	for (int i = 0; i < n;i++)										// Repete N vezes
	{
		result += adc_read();										// Acrescenta a leitura
	}
	result /= n;													// Faz a média
	return result;													// Retorna a média
}
