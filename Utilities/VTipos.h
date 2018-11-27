
/**************************************************************************************************
  Nome do Arquivo:  VTipos.h
Vers�o: 
  Autor:            Joaci Morais 
  Descri��o:        Cont�m os tipos de vari�veis primitivas do sistema.

**************************************************************************************************/

#ifndef VTIPOS_H
#define VTIPOS_H

#include <stdint.h>

/*************************************************************************************************/
/*                                               TIPOS                                           */
/*************************************************************************************************/

typedef uint16_t (*task_routine_t)( uint16_t Tipo , void *Payload );

typedef enum
{
	OK = 0,
	ERR,
	TIMEOUT
}return_codes_t;

typedef struct
{
	uint8_t ID;
	uint8_t Tamanho;
	uint16_t ValorADC;
	char *fim;
}msg_protocol;

/*************************************************************************************************/
/*                                               DEFINI��ES                                      */
/*************************************************************************************************/


#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#ifndef ZERO
  #define ZERO 0
#endif

#ifndef NULL
  #define NULL 0
#endif


#endif // VTIPOS_H
