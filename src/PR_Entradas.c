//
// Created by Marcelo on 2019-05-21.
//

#include "../inc/PR_Entradas.h"
#include "shared_memory.h"
#include <stdio.h>

#define IN_SIZE 3
#define IN(i) (8 + i)

uint8_t* inputs = NULL;
/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
uint8_t LeerEntrada ( uint8_t nEntrada ) {
    int shmid;
    if (nEntrada < 0 || nEntrada >= IN_SIZE) return OFF;

    if (!inputs) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return OFF;
        }
        inputs = shmat(shmid, NULL, 0);
    }

    uint8_t in = inputs[IN(nEntrada)];
    return in;
}
