//
// Created by Marcelo on 2019-05-21.
//

#include "../inc/PR_Entradas.h"
#include "shared_memory.h"
#include <stdio.h>

#define IN_SIZE 3
#define IN(i) (8 + i)

char* data = NULL;
/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
uint8_t LeerEntrada ( uint8_t nEntrada ) {
    int shmid;
    if (nEntrada < 0 || nEntrada >= IN_SIZE) return OFF;

    if (!data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return OFF;
        }
        data = shmat(shmid, NULL, 0);
    }

    uint8_t in = data[IN(nEntrada)];
    return in;
}
