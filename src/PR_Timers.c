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
    uint64_t time; //In milliseconds
    uint8_t base;
}Params;

typedef struct {
    pthread_t thread;
    Params* params;
    uint64_t init_time;
    uint8_t is_stopped;
    uint64_t stopped_time;
    int is_running;
}Timer;

Timer timers[N_TIMERS];

//--------------- executor ------------------------//
void thread_executor(const void* params);

//--------------- time manipulation ------------------------//
uint32_t get_multiplier(uint8_t base);
uint64_t to_milliseconds(uint64_t time, uint8_t base);
uint64_t now_in_milliseconds();
uint64_t milliseconds_to_base(uint64_t milliseconds, uint8_t base);

//--------------- behaviour ------------------------//
void start_in_milliseconds(uint8_t event, uint64_t time, Timer_Handler handler , uint8_t base );
void pause_timer(Timer timer);
void resume_timer(Timer timer);
void stop_timer(Timer timer);


//--------------- API ------------------------//
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base ) {
    start_in_milliseconds(event, to_milliseconds(time, base), handler, base);
}

void SetTimer( uint8_t event, uint32_t time ) {
    Timer timer = timers[event];
    if (timer.is_running) {
        pthread_cancel(timer.thread);
        uint64_t rest_time = to_milliseconds(time, timer.params->base) - (now_in_milliseconds() - timer.init_time);
        if (rest_time <= 0) {
            thread_executor(timer.params);
        } else {
            uint8_t base = timer.params->base;
            Timer_Handler handler = timer.params->handler;
            free(timer.params);
            start_in_milliseconds(event, rest_time, handler, base);
        }

    }
}

void TimerClose(void) {
    for (int i = 0; i < N_TIMERS; i++) {
        stop_timer(timers[i]);
    }
}

uint32_t GetTimer( uint8_t event ) {
    Timer timer = timers[event];
    if (!timer.is_running) return 0;
    uint32_t now = now_in_milliseconds();
    uint32_t time = now - timer.init_time;
    long rest_time = timer.params->time - time;
    return milliseconds_to_base(rest_time, timer.params->base);
}

void StandByTimer( uint8_t event , uint8_t accion) {
    Timer timer = timers[event];
    if (accion == PAUSE) {
        pause_timer(timer);
    } else {
        resume_timer(timer);
    }
}

//--------------- executor ------------------------//
void thread_executor(const void* args) {
    Params* params = (Params*)args;
    usleep(params->time * get_multiplier(MIL));
    timers[params->event].is_running = FALSE;
    Timer_Handler handler = params->handler;
    timers[params->event].params = NULL;
    free(params);
    handler();
}

//--------------- behaviour ------------------------//
void pause_timer(Timer timer) {
    if (timer.is_running && !timer.is_stopped) {
        pthread_cancel(timer.thread);
        timer.stopped_time = now_in_milliseconds();
        timer.is_stopped = TRUE;
        printf("pause_time: %lld, ----> stopped: %d\n", timer.stopped_time, timer.is_stopped);
    }
}

void resume_timer(Timer timer) {
    printf("Resume library, stopped: %d\n", timer.is_stopped);
    if (timer.is_running && timer.is_stopped) {
        printf("Efectivamente resume\n");
        uint64_t time = timer.params->time + timer.init_time - timer.stopped_time;
        uint8_t event = timer.params->event;
        uint8_t base = timer.params->base;
        Timer_Handler handler = timer.params->handler;
        free(timer.params);
        start_in_milliseconds(event, time, handler, base);
    }
}

void start_in_milliseconds(uint8_t event, uint64_t time, Timer_Handler handler , uint8_t base ) {
    Params* params = malloc(sizeof(Params));
    params->event = event;
    params->base = base;
    params->handler = handler;
    params->time = time;

    timers[event].params = params;
    timers[event].init_time = now_in_milliseconds();
    timers[event].is_stopped = FALSE;
    timers[event].is_running = TRUE;
    printf("init_time: %lld\n", timers[event].init_time);
    printf("at  %lld\n", timers[event].params->time);
    pthread_t thread;
    if (pthread_create(&thread, NULL, (void *(*)(void *))thread_executor, params)) {
        perror("Error creating thread\n");
        exit(1);
    }
    timers[event].thread = thread;
}

void stop_timer(Timer timer) {
    pthread_cancel(timer.thread);
    if (timer.is_running) {
        timer.is_running = FALSE;
        free(timer.params);
        timer.params = NULL;
    }
}

//--------------- time manipulation ------------------------//
uint32_t get_multiplier(uint8_t base) {
    if (base == DEC) return DEC_M;
    if (base == MIN) return MIN_M;
    if (base == MIL) return MIL_M;
    return SEC_M;
}

uint64_t to_milliseconds(uint64_t time, uint8_t base) {
    if (base == DEC) return time * 100;
    if (base == MIN) return time * 60000;
    if (base == MIL) return time;
    return time * 1000;
}

uint64_t now_in_milliseconds() {
    struct timeb time;
    ftime(&time);
    return time.time*1000 + time.millitm;
}

uint64_t milliseconds_to_base(uint64_t milliseconds, uint8_t base) {
    uint64_t multiplier;
    switch (base) {
        case MIL: multiplier = 1;break;
        case DEC: multiplier = 100;break;
        case SEG: multiplier = 1000;break;
        case MIN: multiplier = 60000;break;
    }
    return milliseconds/multiplier;
}
