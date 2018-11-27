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
    	int fs = 120;												// Frequência de amostragem
    	int adc_burst[120];											// Valores guardados em 1 segundo
    	uint32_t start,sample;										// Valores de tempo
    	port_sleep_ms(100);											// Delay de inicialização
    	led_write(LED4_PIN,1);

//------------------------------------------------------------------//

//-------------------------------LOOP-------------------------------//
	    while (1)
	    {
	    	start = port_micros();									// Início da amostragem
	    	while((port_micros() - start) <= 1000000)				// 1 segundo de amostragem
			{
	    		sample = port_micros();								// Início da amostra
				adc = adc_read();									// Leitura do adc
				if (count < fs) adc_burst[count] = adc;				// Segurança do adc_burst
				count++;											// Incremento do contador
				while((port_micros() - sample) <= 1000000/fs-1);	// Tempo de uma amostra
			}

	    	for (int i = 0;i<fs;i++)								// Percorrer o adc_burst
	    	{
				debug_write_msg_string(1,adc_burst[i]);				// Enviar os valores via serial
	    	}
			count = 0;												// Zerar o contador para uma nova amostragem
	    	port_sleep_ms(2000);									// Delay pois o python ainda não está pronto.
	    }
//-----------------------------------------------------------------//
		return 0;
}
