/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Impressao
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "threads.h"
#include "factories.h"
#include "helpers.h"
#include "utils.h"

Onibus *getOnibusIfCan(OnibusList *onibus_list, int idx)
{
  if (idx >= onibus_list->length)
    return NULL;

  return onibus_list->items[idx];
}

double getElapsedTimePercent(Onibus *onibus)
{
  struct timeval *now = (struct timeval *)malloc(sizeof(struct timeval));

  get_current_timeval(now);

  long total = (onibus->data_chegada->tv_sec * 1000000 + onibus->data_chegada->tv_usec) - (onibus->data_saida->tv_sec * 1000000 + onibus->data_saida->tv_usec);
  long elapsed = (now->tv_sec * 1000000 + now->tv_usec) - (onibus->data_saida->tv_sec * 1000000 + onibus->data_saida->tv_usec);
  double percent = (double)elapsed / total;

  free(now);

  return percent;
}

void printOnibusMovementStatus(Onibus *onibus)
{
  if (onibus->origem == -1)
  {
    printf("Inicializando...");
    return;
  }
  else if (onibus->destino == -1)
  {
    printf("Estacionado em %d", onibus->origem);
    return;
  }

  double elapsedTimePercent = getElapsedTimePercent(onibus);

  int filledSpaces = elapsedTimePercent * 20;

  printf("Percorrendo: %d [", onibus->origem);
  for (int idx = 0; idx < 20; idx++)
  {
    if (idx < filledSpaces)
      printf("-");
    else
      printf(" ");
  }
  printf("] %d", onibus->destino);
}

void printPontoDeOnibus(PontoDeOnibus *ponto_de_onibus, OnibusList *onibus_list)
{
  printf("\nPonto %d)\n", ponto_de_onibus->id);
  printf("  Onibus: %d", ponto_de_onibus->onibus_ocupando);
  if (ponto_de_onibus->onibus_ocupando != -1)
  {
    printf(" | Passageiros: %d", onibus_list->items[ponto_de_onibus->onibus_ocupando]->passageiros_list->length);
  }
  printf("\n");
  printf("  Passageiros: %d\n", ponto_de_onibus->passageiros_list->length);
}

void printPontoDeOnibusAndOnibus(PontoDeOnibus *ponto_de_onibus, Onibus *onibus, OnibusList *onibus_list)
{
  printf("\nPonto %d)                                         Onibus %d)\n", ponto_de_onibus->id, onibus->id);
  if (ponto_de_onibus->onibus_ocupando != -1)
  {
    printf("  Onibus: %d | Passageiros: %d                      ", ponto_de_onibus->onibus_ocupando, onibus_list->items[ponto_de_onibus->onibus_ocupando]->passageiros_list->length);
    printOnibusMovementStatus(onibus);
  }
  else
  {
    printf("  Onibus: -1                                      ");
    printOnibusMovementStatus(onibus);
  }
  printf("\n");
  printf("  Passageiros: %d\n", ponto_de_onibus->passageiros_list->length);
}

void clearTerminal()
{
  printf("\033[2J\033[H");
}

void *thread_state_printer(void *arg)
{
  Context *ctx = (Context *)arg;

#if DEBUG
  free(ctx);
  pthread_exit(NULL);
  return NULL;
#endif

  int pontos_len = ctx->pontos_de_onibus_list->length;

  while (isFinished(ctx->passageiro_list) == false)
  {
    for (int idx = 0; idx < pontos_len; idx++)
    {
      PontoDeOnibus *ponto_de_onibus = ctx->pontos_de_onibus_list->items[idx];
      Onibus *onibus = getOnibusIfCan(ctx->onibus_list, idx);

      if (onibus == NULL)
        printPontoDeOnibus(ponto_de_onibus, ctx->onibus_list);
      else
        printPontoDeOnibusAndOnibus(ponto_de_onibus, onibus, ctx->onibus_list);
    }

    sleep_ms(200);
    clearTerminal();
  }

  printf("FIM\n");

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}