#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/**
* @brief Get the current system time in ms
*/
static inline double get_time_ms(void){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);

    return (double)t.tv_sec * 1000.0 + (double)t.tv_nsec / 1.0e6; //// Convert to milliseconds
}

#endif