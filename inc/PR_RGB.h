/*******************************************************************************************************************************//**
 *
 * @file		DR_RGB.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		16 de nov. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PRIMITIVAS_INC_PR_RGB_H_
#define PRIMITIVAS_INC_PR_RGB_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_Infotronic.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		ROJO		2
#define		VERDE		1
#define		AZUL		0

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void LedsRGB( uint8_t led , uint8_t estado );

#endif /* PRIMITIVAS_INC_PR_RGB_H_ */
