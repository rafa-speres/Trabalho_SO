#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "factories.h"
#include "helpers.h"
#include "debug.h"
#include "utils.h"

void runUntilLockBusStop(OnibusContext *ctx)
{
  Onibus *onibus = ctx->this;

  if (onibus->origem == -1)
    onibus->destino = rand_int(0, ctx->pontos_de_onibus_list->length - 1);
  else
    onibus->destino = next_circular_idx(onibus->origem, ctx->pontos_de_onibus_list->length);

  busy_wait_ms(rand_int(500, 1000));

  while (pthread_mutex_trylock(ctx->pontos_de_onibus_list->items[onibus->destino]->ponto_de_onibus_mutex) != 0)
  {
    onibus->destino = next_circular_idx(onibus->destino, ctx->pontos_de_onibus_list->length);
    busy_wait_ms(rand_int(500, 1000));
  }

  return;
}

void *thread_Onibus(void *arg)
{
  OnibusContext *ctx = (OnibusContext *)arg;
  Onibus *this = ctx->this;

  while (isFinished(ctx->passageiro_list) == false)
  {
    runUntilLockBusStop(ctx);

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