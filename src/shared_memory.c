//
// Created by Macbook pro Retina on 2019-05-18.
//

#include "shared_memory.h"

int shmid = 0;

key_t getKey() {
    key_t key;
    if ((key = ftok("/", 'l')) == -1) {
        perror("ftok fails\n");
        return -1;
    }
    return key;
}

int init_shared_memory() {
    int shmid;

    key_t key;
    if ((key = getKey()) == -1) return -1;

    if ((shmid = shmget(key, MEMORY_SIZE, IPC_CREAT | 0644)) == -1) {
        perror("memory segment creation fails\n");
        return -1;
    }

    return shmid;
}
