#include "threads.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "factories.h"
#include "dynamic_list.h"
#include "helpers.h"
#include "utils.h"

PontoDeOnibus *getPassageiroPontoDeOnibus(PassageiroContext *ctx)
{
  return ctx->pontos_de_onibus_list->items[ctx->this->destino];
}

Onibus *getPassageiroOnibus(PassageiroContext *ctx)
{
  return ctx->onibus_list->items[ctx->pontos_de_onibus_list->items[ctx->this->destino]->onibus_ocupando];
}

void *thread_Passageiro(void *arg)
{
  PassageiroContext *ctx = (PassageiroContext *)arg;
  Passageiro *this = ctx->this;
  // printf("Passageiro %d | origem: %d | destino: %d\n", ctx->this->id, ctx->this->origem, ctx->this->destino);

  pthread_mutex_lock(this->passageiro_mutex);
  pthread_cond_wait(this->passageiro_lock, this->passageiro_mutex);

  PontoDeOnibus *ponto_de_onibus = getPassageiroPontoDeOnibus(ctx);
  Onibus *onibus = getPassageiroOnibus(ctx);

  removeFromList(onibus->passageiros_list, this);

  busy_wait_ms(500);

  this->finalizado = true;

  sem_post(ponto_de_onibus->landing_passageiros_semaphore);
  pthread_mutex_unlock(this->passageiro_mutex);

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}