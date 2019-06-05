//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_RGB.h"
#include "shared_memory.h"

#define STATE(b) b ? "ON" : "OFF"
#define LED(i) 5 + i

#define LED_0 0

uint8_t* leds = NULL;

typedef union {
    uint8_t led;
    struct {
        uint8_t red:1;
        uint8_t green:1;
        uint8_t blue:1;
        uint8_t empty:5;
    }bits;
}led_t;

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
    led_t ledColor;
    ledColor.led = leds[LED(LED_0)];

    switch (led) {
        case ROJO: ledColor.bits.red = estado;break;
        case VERDE: ledColor.bits.green = estado;break;
        case AZUL: ledColor.bits.blue = estado;break;
    }

    leds[LED(LED_0)] = ledColor.led;
}
