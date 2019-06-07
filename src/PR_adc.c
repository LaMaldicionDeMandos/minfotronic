//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_adc.h"
#include "shared_memory.h"

#define THERMOMETER_LOW adc_data[15]
#define THERMOMETER_HIGH adc_data[16]

#define POTENTIOMETER_LOW adc_data[17]
#define POTENTIOMETER_HIGH adc_data[18]

#define ZERO_CELCIUS 2730
uint8_t* adc_data = NULL;

typedef union {
    uint16_t value;
    uint8_t  bytes[2];
} AD_TYPE;

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/
uint8_t* init_data() {
    int shmid;
    if (!adc_data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return 0;
        }
        adc_data = shmat(shmid, NULL, 0);
    }
    return adc_data;
}

AD_TYPE readData(uint8_t first, uint8_t second) {
    adc_data = init_data();

    AD_TYPE data;
    data.bytes[0] = first;
    data.bytes[1] = second;
    return data;
}


/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
int16_t Temperatura() {
    return readData(THERMOMETER_LOW, THERMOMETER_HIGH).value - ZERO_CELCIUS;
}

int16_t Potenciometro ( void ) {
    return readData(POTENTIOMETER_LOW, POTENTIOMETER_HIGH).value;
}
