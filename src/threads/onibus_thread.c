#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "factories.h"
#include "helpers.h"
#include "debug.h"
#include "utils.h"

void travel(Onibus *onibus)
{
  getCurrentTimeMs(onibus->data_saida);
  int waitTimeMs = rand_int(2000, 3000);
  getIncrementedTimeval(onibus->data_saida, onibus->data_chegada, waitTimeMs * 1000);
  busy_wait_ms(waitTimeMs);
}

bool runUntilLockBusStop(OnibusContext *ctx)
{
  Onibus *onibus = ctx->this;

  if (onibus->origem == -1)
    onibus->destino = rand_int(0, ctx->pontos_de_onibus_list->length - 1);
  else
    onibus->destino = next_circular_idx(onibus->origem, ctx->pontos_de_onibus_list->length);

  travel(onibus);

  while (pthread_mutex_trylock(ctx->pontos_de_onibus_list->items[onibus->destino]->ponto_de_onibus_mutex) != 0)
  {
    onibus->destino = next_circular_idx(onibus->destino, ctx->pontos_de_onibus_list->length);

    travel(onibus);
  }

  return true;
}

void *thread_Onibus(void *arg)
{
  OnibusContext *ctx = (OnibusContext *)arg;
  Onibus *this = ctx->this;

  while (runUntilLockBusStop(ctx) && isFinished(ctx->passageiro_list) == false)
  {
    this->origem = this->destino;
    this->destino = -1;
    PontoDeOnibus *ponto_de_onibus = ctx->pontos_de_onibus_list->items[this->origem];
    ponto_de_onibus->onibus_ocupando = this->id;

    debug_printf("ONIBUS %d ENTROU EM %d\n", this->id, ponto_de_onibus->id);

    pthread_mutex_lock(ponto_de_onibus->onibus_management_mutex);

    pthread_cond_signal(ponto_de_onibus->ponto_de_onibus_management_lock);
    pthread_cond_wait(ponto_de_onibus->onibus_management_lock, ponto_de_onibus->onibus_management_mutex);

    ponto_de_onibus->onibus_ocupando = -1;

    pthread_mutex_unlock(ponto_de_onibus->onibus_management_mutex);
    pthread_mutex_unlock(ponto_de_onibus->ponto_de_onibus_mutex);

    debug_printf("ONIBUS %d SAIU DE %d\n", this->id, ponto_de_onibus->id);
  }

  debug_printf("ONIBUS %d FINALIZOU\n", this->id);

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}