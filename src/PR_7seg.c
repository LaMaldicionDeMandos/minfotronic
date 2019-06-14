//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_7seg.h"
#include "shared_memory.h"
#include <stdio.h>
#include <unistd.h>

uint8_t* seg7_data = NULL;

#define DISPLAY(i, j) seg7_data[21 + i*4 + j]

typedef union {
    u_int32_t value;
    u_int8_t  bytes[4];
} AD_X2_TYPE;

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/
uint8_t* init_data() {
    int shmid;
    if (!seg7_data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return 0;
        }
        seg7_data = shmat(shmid, NULL, 0);
    }
    return seg7_data;
}
/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
void Display(unsigned int value,unsigned char dsp) {
    seg7_data = init_data();
    AD_X2_TYPE data;
    data.value = value;
    for (int i = 0; i < 4; i++) {
        DISPLAY(dsp, i) = data.bytes[i];
    }
}