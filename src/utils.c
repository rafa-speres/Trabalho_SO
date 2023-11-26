/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Sleep, Busy Wait, valores rand, index circular, e tempo
*/
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

// Dorme por uma quantidade especifica de milissegundos (ms)
void sleep_ms(unsigned int ms)
{
  struct timespec sleep_time;

  sleep_time.tv_sec = 0;
  sleep_time.tv_nsec = 1000000 * ms;

  nanosleep(&sleep_time, NULL);
}

// Espera ocupada por uma quantidade especifica de milissegundos
void busy_wait_ms(unsigned long ms)
{
  clock_t start_time = clock();
  clock_t elapsed_time;

  clock_t wait_ticks = (clock_t)(ms * CLOCKS_PER_SEC / 1000);

  do
  {
    elapsed_time = clock() - start_time;
  } while (elapsed_time < wait_ticks);
}

// Gera um numero aleatorio no intervalo (min e max sao inclusos)
int rand_int(int min, int max)
{
  return min + (rand() % (max - min + 1));
}

// limit não incluso
int next_circular_idx(int current, int limit)
{
  return (current + 1) % limit;
}

// Obtem a hora atual
void get_current_tm(struct tm *result)
{
  time_t currentTime;
  struct tm *localTime;

  time(&currentTime);
  localTime = localtime(&currentTime);

  memcpy(result, localTime, sizeof(struct tm));
}

// Obtem o tempo atual
void get_current_timeval(struct timeval *time)
{
  gettimeofday(time, NULL);
}

void get_incremented_timeval(struct timeval *ref_time, struct timeval *result_time, int usec)
{
  result_time->tv_sec = ref_time->tv_sec + usec / 1000000;
  result_time->tv_usec = ref_time->tv_usec + usec % 1000000;

  // Ajusta o tempo se ultrapassar 1 segundo
  if (result_time->tv_usec >= 1000000)
  {
    result_time->tv_sec++;
    result_time->tv_usec -= 1000000;
  }
}
