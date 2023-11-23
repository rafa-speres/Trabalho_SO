#include <sys/time.h>

#ifndef UTILS
#define UTILS

int rand_int(int min, int max);
int next_circular_idx(int current, int limit);
void sleep_ms(unsigned int ms);
void busy_wait_ms(unsigned long ms);
void get_current_tm(struct tm *result);
void get_current_timeval(struct timeval *time);
void get_incremented_timeval(struct timeval *refTime, struct timeval *resultTime, int usec);

#endif