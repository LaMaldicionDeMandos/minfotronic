/*******************************************************************************************************************************//**
 *
 * @file		DR_UART.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		12 de oct. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERLPC_DR_UART1_H_
#define DRIVERLPC_DR_UART1_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define MAX_BUFF_RX1		512
#define MAX_BUFF_TX1		512

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void UART1_Inicializacion ( uint32_t );
void UART1_PushRX( uint8_t dato );
int16_t UART1_PopRX( void );
void UART1_PushTX( uint8_t dato );
int16_t UART1_PopTX( void );

#endif /* DRIVERLPC_DR_UART1_H_ */
