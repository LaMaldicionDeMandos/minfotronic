//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_RGB.h"
#include "shared_memory.h"

#define STATE(b) b ? "ON" : "OFF"
#define LED(i) 5 + i

#define LED_0 0

uint8_t* leds = NULL;

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
void LedsRGB( uint8_t led , uint8_t estado ){
    int shmid;
    if (!leds) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return;
        }
        leds = shmat(shmid, NULL, 0);
    }
    if (led == ROJO) {
        leds[LED(LED_0)] = estado;
    }

}
