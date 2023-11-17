#include <time.h>
#include <stdlib.h>
#include "utils.h"

// ms em milisegundos
void sleep(int ms)
{
  struct timespec sleep_time;

  sleep_time.tv_sec = 0;
  sleep_time.tv_nsec = 1000000 * ms;

  nanosleep(&sleep_time, NULL);
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