//
// Created by Macbook pro Retina on 2019-05-18.
//

#ifndef TPC3_SHARED_MEMORY_H
#define TPC3_SHARED_MEMORY_H

#include "../inc/DR_tipos.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

#define DATA_SIZE 61
#define MEMORY_SIZE sizeof(uint8_t) * DATA_SIZE

extern char* data;

key_t getKey();

int init_shared_memory();
#endif //TPC3_SHARED_MEMORY_H
