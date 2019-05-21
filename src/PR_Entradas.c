//
// Created by Marcelo on 2019-05-21.
//

#include "../inc/PR_Entradas.h"
#include "shared_memory.h"

#define IN_SIZE 3
#define IN(i) (8 + i)

char* data;
/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
uint8_t GetKey ( void ) {

    for (int i = 0; i < KEY_SIZE; i++) {
        if (data[KEY(i)] == ON){
            data[KEY(i)] = OFF;
            return i;
        }
    }

    return NO_KEY;

}


uint8_t LeerEntrada ( uint8_t nEntrada ) {
    int shmid;
    if (nEntrada < 0 || nEntrada >= IN_SIZE) return OFF;

    return IN(nEntrada);
}
