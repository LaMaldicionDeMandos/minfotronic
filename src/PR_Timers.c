//
// Created by Macbook pro Retina on 2019-05-18.
//
#include "../inc/PR_Timers.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

#define MIL 3

#define MIL_M 1000
#define DEC_M 100000
#define SEC_M 1000000
#define MIN_M 60000000

#define FALSE 0
#define TRUE 1

typedef struct{
    uint8_t event;
    Timer_Handler handler;
    uint32_t time;
    uint8_t base;
}Params;

typedef struct{
    pthread_t thread;
    Params* params;
    uint32_t init_time;
    int running;
}Timer;

Timer timers[N_TIMERS];

void thread_executor(const void* params);
int get_multiplier(uint8_t base);
uint32_t get_time_in_milliseconds(uint32_t time, uint8_t base);
uint32_t get_now_in_milliseconds();

void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base ) {
    Params* params = malloc(sizeof(Params));
    params->event = event;
    params->base = base;
    params->handler = handler;
    params->time = time;

    timers[event].params = params;
    timers[event].init_time = get_now_in_milliseconds();
    timers[event].running = TRUE;

    pthread_t thread;
    if (pthread_create(&thread, NULL, (void *(*)(void *))thread_executor, params)) {
        perror("Error creating thread\n");
        exit(1);
    }
    timers[event].thread = thread;
}

void SetTimer( uint8_t event, uint32_t time ) {
    if (timers[event].running) {
        pthread_cancel(timers[event].thread);
        long rest_of_milliseconds = get_time_in_milliseconds(time, timers[event].params->base) - (get_now_in_milliseconds() - timers[event].init_time);
        if (rest_of_milliseconds <= 0) {
            thread_executor(timers[event].params);
        } else {
            Timer_Handler handler = timers[event].params->handler;
            free(timers[event].params);
            TimerStart(event, rest_of_milliseconds, handler, MIL);
        }

    }
}

void TimerClose(void) {
    for (int i = 0; i < N_TIMERS; i++) {
        pthread_cancel(timers[i].thread);
        if (timers[i].running) {
            timers[i].running = FALSE;
            free(timers[i].params);
            timers[i].params = NULL;
        }
    }
}

int get_multiplier(uint8_t base) {
    if (base == DEC) return DEC_M;
    if (base == MIN) return MIN_M;
    if (base == MIL) return MIL_M;
    return SEC_M;
}

uint32_t get_time_in_milliseconds(uint32_t time, uint8_t base) {
    if (base == DEC) return time * 100;
    if (base == MIN) return time * 60000;
    if (base == MIL) return time;
    return time * 1000;
}

void thread_executor(const void* args) {
    Params* params = (Params*)args;
    usleep(params->time * get_multiplier(params->base));
    timers[params->event].running = FALSE;
    Timer_Handler handler = params->handler;
    timers[params->event].params = NULL;
    free(params);
    handler();
}

uint32_t get_now_in_milliseconds() {
    struct timeb time;
    ftime(&time);
    return time.time * time.millitm;
}
