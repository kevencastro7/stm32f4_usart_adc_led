/*
 * debug.c
 *
 *  Created on: 6 de nov de 2015
 *      Author: ox_jodm_xo
 */

#include "debug.h"
																	//------------------COMENTÁRIOS-------------------//

void Delay ( __IO uint32_t nCount )									// delay
{
		while ( nCount-- )
				;
}

void debug_init ( void )											// Inicialização
{
		GPIO_InitTypeDef GPIO_InitStruct;							// Struct da GPIO
		USART_InitTypeDef USART_InitStruct;							// Struct da USART

	 	 	 	 													//-------------Configuração do Clock--------------//
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE );	// Ativar clock da USART
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB , ENABLE );	// Ativar clock da GPIO
	 	 	 	 													//------------------------------------------------//

	 	 	 	 													//--------------Configuração dos Pinos------------//
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;			// Pinos de TX e RX
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;					// Modo de Operação
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;				// Velocidade da GPIO
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;					// Tipo de saída
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;					// Pull-UP
		GPIO_Init( GPIOB , &GPIO_InitStruct );						// Inicialização da GPIO
	 	 	 	 													//------------------------------------------------//

		GPIO_PinAFConfig( GPIOB , GPIO_PinSource6 , GPIO_AF_USART1 );// TX
		GPIO_PinAFConfig( GPIOB , GPIO_PinSource7 , GPIO_AF_USART1 );// RX

		USART_InitStruct.USART_BaudRate = 115200;					// Baudrate
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;	// Tamanho da palavra
		USART_InitStruct.USART_StopBits = USART_StopBits_1;			// 1 bit de stop
		USART_InitStruct.USART_Parity = USART_Parity_No;			// Sem bit de paridade
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Sem Flow Control
		USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;// Modo de Transmissor e Receptor
		USART_Init( USART1 , &USART_InitStruct );					// Inicialização da USART

		USART_Cmd( USART1 , ENABLE );								// Ativação da USART
}

void debug_write_string ( volatile char *info )						// Enviar String
{
		while ( *info  != 0)										// Enquanto a string não acabar
		{
				// wait until data register is empty
				while ( ! ( USART1->SR & 0x00000040 ) )				// Espera o registrador de dados esvaziar
						;
				USART_SendData( USART1 , *info );					// Enviar 1 byte
				info++;												// Incrementa o ponteiro
		}
}
void debug_write_int_to_string(uint16_t info)						// Enviar inteiro
{
	char str[80];													// String
	sprintf(str, "%u", info);										// Transformar em string
	debug_write_string(str);										// Enviar string

}
void debug_write_protocol_string ( msg_protocol info )				// Enviar protocolo
{
	debug_write_int_to_string(info.ID);								// Enviar ID
	debug_write_int_to_string(info.Tamanho);						// Enviar Tamanho
	debug_write_int_to_string(info.ValorADC);						// Enviar valor do ADC
	debug_write_string(info.fim);									// Enviar fim
}
void debug_write_msg_string(uint8_t ID,uint16_t info)				// Enivar mensagem
{
	msg_protocol msg;												// Cria struct msg_protocol
	msg.ID = ID;													// Atribui o ID
	msg.Tamanho = calc_bytes(info);									// Calcula o tamanho
	msg.ValorADC = info;											// Atribui o valor
	msg.fim = " ";													// Final
	debug_write_protocol_string(msg);								// Enviar protocolo
}
uint8_t calc_bytes(uint16_t info)									// Calcula a quantidade de bytes
{
	uint8_t result;
	if ((info / 100000) >= 1)
	{
		result = 6;
	}
	else if ((info / 10000) >= 1)
	{
		result = 5;
	}
	else if ((info / 1000) >= 1)
	{
		result = 4;
	}
	else if (info / 100 >= 1)
	{
		result = 3;
	}
	else if (info / 10 >= 1)
	{
		result = 2;
	}
	else
	{
		result = 1;
	}
	return result;
}


uint16_t debug_read()												// Leitura de dados
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE))				// Se tiver dados pra receber
    {
    	return USART_ReceiveData(USART1);							// Retorna o valor lido
    }
     return 0;
}
