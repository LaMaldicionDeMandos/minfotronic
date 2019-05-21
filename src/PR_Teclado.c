//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_Teclado.h"
#include "shared_memory.h"

#define KEY_SIZE 5
#define KEY(i) i

char* data = NULL;
/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
uint8_t GetKey ( void ) {
    int shmid;
    if (!data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return NO_KEY;
        }
        data = shmat(shmid, NULL, 0);
    }

    for (int i = 0; i < KEY_SIZE; i++) {
        if (data[KEY(i)] == ON){
            data[KEY(i)] = OFF;
            return i;
        }
    }

    return NO_KEY;

}
