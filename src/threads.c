#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void *thread_Onibus(void *arg)
{
  OnibusContext *onibusCtx = (OnibusContext *)arg;
  Onibus *this = onibusCtx->this;
  // printf("Onibus %d | origem: %d | destino: %d\n", onibusCtx->this->id, onibusCtx->this->origem, onibusCtx->this->destino);

  while (isFinished(onibusCtx->passageiro_list) == false)
  {
    this->destino = next_circular_idx(this->origem, onibusCtx->pontos_de_onibus_list->length);

    busy_wait_ms(rand_int(500, 1000));

    while (pthread_mutex_trylock(onibusCtx->pontos_de_onibus_list->items[this->destino]->ponto_de_onibus_mutex) != 0)
    {
      this->destino = next_circular_idx(this->destino, onibusCtx->pontos_de_onibus_list->length);
      busy_wait_ms(rand_int(500, 1000));
    }

    PontoDeOnibus *ponto_de_onibus = onibusCtx->pontos_de_onibus_list->items[this->origem];
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

  free(onibusCtx);
  pthread_exit(NULL);
  return NULL;
}

void *thread_PontoDeOnibus(void *arg)
{
  PontoDeOnibusContext *pontoDeOnibusCtx = (PontoDeOnibusContext *)arg;
  PontoDeOnibus *this = pontoDeOnibusCtx->this;

  while (isFinished(pontoDeOnibusCtx->passageiro_list) == false)
  {
    pthread_mutex_lock(this->ponto_de_onibus_management_mutex);
    pthread_cond_wait(this->ponto_de_onibus_management_lock, this->ponto_de_onibus_management_mutex);
    
    // printf("PONTO %d RECEBEU %d\n", this->id, this->onibus_ocupando);
    
    busy_wait_ms(2000);
    
    // printf("PONTO %d ENTREGOU %d\n", this->id, this->onibus_ocupando);
    
    pthread_cond_signal(this->onibus_management_lock);
    pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
  }

  free(pontoDeOnibusCtx);
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