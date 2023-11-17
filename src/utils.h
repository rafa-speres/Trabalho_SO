#ifndef UTILS
#define UTILS

int rand_int(int min, int max);
int next_circular_idx(int current, int limit);
void sleep_ms(unsigned int ms);
void busy_wait_ms(unsigned long ms);

#endif