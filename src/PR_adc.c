//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_adc.h"
#include "shared_memory.h"

#define THERMOMETER_LOW thermometer_data[15]
#define THERMOMETER_HIGH thermometer_data[16]

#define ZERO_CELCIUS 2730
uint8_t* thermometer_data = NULL;

typedef union {
    uint16_t value;
    uint8_t  bytes[2];
} THERMOMETER_TYPE;

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
int16_t Temperatura() {
    int shmid;
    if (!thermometer_data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return 0;
        }
        thermometer_data = shmat(shmid, NULL, 0);
    }

    THERMOMETER_TYPE thermometer;
    thermometer.bytes[0] = THERMOMETER_LOW;
    thermometer.bytes[1] = THERMOMETER_HIGH;
    return thermometer.value - ZERO_CELCIUS;
}
