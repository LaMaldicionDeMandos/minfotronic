//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/PR_Relays.h"
#include "shared_memory.h"

#define STATE(b) b ? "ON" : "OFF"
#define RELAY(i) relays[11 + i]

#define RELAYS 4

char* relays = NULL;

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
void Relays( uint8_t nRelay , uint8_t estado ) {
    int shmid;
    if (!relays) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return;
        }
        relays = shmat(shmid, NULL, 0);
    }

    if (nRelay < 0 || nRelay >= RELAYS) return;

    RELAY(nRelay) = estado;

}
