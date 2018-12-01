/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "debug.h"
#include "port.h"
#include "led.h"
#include "adc.h"
#include "delay.h"

int main ( void )													//------------------COMENTÁRIOS-------------------//
{
//-------------------------------SETUP------------------------------//

		port_init();												// Temporizador
		debug_init();												// Comunicação Serial
		led_init();													// LEDs
		adc_init();													// Conversor analógico-digital
        uint16_t adc ;												// Variável a receber o valor do adc
        uint32_t count = 0;											// Contador
    	int fs = 1000;												// Frequência de amostragem
    	int adc_burst[4];											// Valores guardados em 1 segundo
    	uint32_t start,sample;										// Valores de tempo
    	port_sleep_ms(100);											// Delay de inicialização
    	led_write(LED4_PIN,1);

//------------------------------------------------------------------//

//-------------------------------LOOP-------------------------------//
	    while (1)
	    {

	    	sample = port_micros();									// Início da amostra
			adc_burst[count] = adc_read();							// Salva amostra
			count++;												// Incremento do contador
	    	if (count == 4)											// Quando salva 4 amostras
	    	{
				debug_write_msg_string("|",&adc_burst[0]);			// Enviar os valores via serial
				count = 0;											// Zerar o contador
	    	}
			while((port_micros() - sample) <= 1000000/fs-1);		// Tempo de uma amostra
	    }
//------------------------------------------------------------------//
		return 0;
}
