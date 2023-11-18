#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void *thread_Onibus(void *arg)
{
  OnibusContext *ctx = (OnibusContext *)arg;
  Onibus *this = ctx->this;
  // printf("Onibus %d | origem: %d | destino: %d\n", ctx->this->id, ctx->this->origem, ctx->this->destino);

  while (isFinished(ctx->passageiro_list) == false)
  {
    this->destino = next_circular_idx(this->origem, ctx->pontos_de_onibus_list->length);

    busy_wait_ms(rand_int(500, 1000));

    while (pthread_mutex_trylock(ctx->pontos_de_onibus_list->items[this->destino]->ponto_de_onibus_mutex) != 0)
    {
      this->destino = next_circular_idx(this->destino, ctx->pontos_de_onibus_list->length);
      busy_wait_ms(rand_int(500, 1000));
    }

    PontoDeOnibus *ponto_de_onibus = ctx->pontos_de_onibus_list->items[this->origem];
    this->origem = this->destino;
    this->destino = -1;
    ponto_de_onibus->onibus_ocupando = this->id;

    // printf("ONIBUS %d ENTROU EM %d\n", this->id, ponto_de_onibus->id);

    pthread_mutex_lock(ponto_de_onibus->onibus_management_mutex);

    // printf("ONIBUS %d ENTROU EM %d (MANAGEMENT AREA)\n", this->id, ponto_de_onibus->id);

    pthread_cond_signal(ponto_de_onibus->ponto_de_onibus_management_lock);
    pthread_cond_wait(ponto_de_onibus->onibus_management_lock, ponto_de_onibus->onibus_management_mutex);

    ponto_de_onibus->onibus_ocupando = -1;

    pthread_mutex_unlock(ponto_de_onibus->onibus_management_mutex);
    pthread_mutex_unlock(ponto_de_onibus->ponto_de_onibus_mutex);

    // printf("ONIBUS %d SAIU DE %d\n", this->id, ponto_de_onibus->id);
  }

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}

void *thread_PontoDeOnibus(void *arg)
{
  PontoDeOnibusContext *ctx = (PontoDeOnibusContext *)arg;
  PontoDeOnibus *this = ctx->this;

  while (isFinished(ctx->passageiro_list) == false)
  {
    pthread_mutex_lock(this->ponto_de_onibus_management_mutex);
    pthread_cond_wait(this->ponto_de_onibus_management_lock, this->ponto_de_onibus_management_mutex);

    // printf("PONTO %d RECEBEU %d\n", this->id, this->onibus_ocupando);

    Onibus *onibus = ctx->onibus_list->items[this->onibus_ocupando];

    DynamicList* landing_passageiros_list = extractLandingPassageiros(onibus, this);

    for (int idx = 0; idx < landing_passageiros_list->length; idx++) {
      Passageiro * passageiro = (Passageiro *) landing_passageiros_list->items[idx]; 
      
      passageiro->finalizado = true;
    }

    while (onibus->passageiros_list->length < onibus->qtd_assentos && this->passageiros_list->length > 0)
    {
      appendList(onibus->passageiros_list, shiftList(this->passageiros_list));
    }

    busy_wait_ms(2000);

    // printf("PONTO %d ENTREGOU %d\n", this->id, this->onibus_ocupando);

    pthread_cond_signal(this->onibus_management_lock);
    pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
  }

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}

void *thread_Passageiro(void *arg)
{
  PassageiroContext *passageiroCtx = (PassageiroContext *)arg;
  // printf("Passageiro %d | origem: %d | destino: %d\n", passageiroCtx->this->id, passageiroCtx->this->origem, passageiroCtx->this->destino);

  free(passageiroCtx);
  pthread_exit(NULL);
  return NULL;
}