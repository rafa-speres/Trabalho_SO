#include <time.h>
#include <stdlib.h>
#include "utils.h"

// ms em milisegundos
void sleep_ms(unsigned int ms)
{
  struct timespec sleep_time;

  sleep_time.tv_sec = 0;
  sleep_time.tv_nsec = 1000000 * ms;

  nanosleep(&sleep_time, NULL);
}

void busy_wait_ms(unsigned long ms) {
    clock_t start_time = clock();
    clock_t elapsed_time;

    clock_t wait_ticks = (clock_t)(ms * CLOCKS_PER_SEC / 1000);

    do {
        elapsed_time = clock() - start_time;
    } while (elapsed_time < wait_ticks);
}

// min e max são inclusos
int rand_int(int min, int max)
{
  return min + (rand() % (max - min + 1));
}

// limit não incluso
int next_circular_idx(int current, int limit)
{
  return (current + 1) % limit;
}