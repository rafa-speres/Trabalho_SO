#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "threads.h"
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void clearTerminal()
{
  printf("\033[2J\033[H");
}

void *thread_state_printer(void *arg)
{
  Context *ctx = (Context *)arg;

  // free(ctx);
  // pthread_exit(NULL);
  // return NULL;

  while (isFinished(ctx->passageiro_list) == false)
  {
    for (int idx = 0; idx < ctx->pontos_de_onibus_list->length; idx++)
    {
      PontoDeOnibus *ponto_de_onibus = ctx->pontos_de_onibus_list->items[idx];

      printf("\nPonto %d)\n", ponto_de_onibus->id);
      printf("  Onibus: %d", ponto_de_onibus->onibus_ocupando);
      if (ponto_de_onibus->onibus_ocupando != -1) {
        printf(" | Passageiros: %d", ctx->onibus_list->items[ponto_de_onibus->onibus_ocupando]->passageiros_list->length);
      }
      printf("\n");
      printf("  Passageiros: %d\n", ponto_de_onibus->passageiros_list->length);
    }

    sleep_ms(200);
    clearTerminal();
  }

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}