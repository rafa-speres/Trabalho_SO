/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Sleep, Busy Wait, valores rand, index circular, e tempo
*/
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