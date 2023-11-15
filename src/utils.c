#include <time.h>
#include <stdlib.h>

// min e max são inclusos
int rand_int(int min, int max)
{
  return min + (rand() % (max - min + 1));
}

// limit não incluso
int next_circular_idx(int current, int limit) {
  return (current + 1) % limit;
}