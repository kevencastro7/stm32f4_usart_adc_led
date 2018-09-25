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
#include <stdio.h>

int main ( void )
{
		port_init();
		debug_init();
		led_init();
		adc_init();
        uint16_t data;
        uint16_t adc ;
		debug_write("Iniciando Programa");
	    while (1)
	    {
	    	data = debug_read();
	    	adc = adc_read_samples(100);
	        led_write(LED5_PIN,1);
	        if (data == '1')
	        {
	    		debug_write_int(adc);
	    		led_write(LED3_PIN,1);
	        }
	        else if (data == '0')
	        {
	    		debug_write("");
	    		led_write(LED3_PIN,0);
	        }
	    }
		return 0;
}
