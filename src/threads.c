#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void *thread_PontoDeOnibus(void *arg)
{
  PontoDeOnibusContext *pontoDeOnibusCtx = (PontoDeOnibusContext *)arg;
  // printf("PontoDeOnibus %d\n", pontoDeOnibusCtx->this->id);

  free(pontoDeOnibusCtx);
  pthread_exit(NULL);
  return NULL;
}

void *thread_Onibus(void *arg)
{
  OnibusContext *onibusCtx = (OnibusContext *)arg;
  // printf("Onibus %d | origem: %d | destino: %d\n", onibusCtx->this->id, onibusCtx->this->origem, onibusCtx->this->destino);

  while (isFinished(onibusCtx->passageiro_list) == false)
  {
    onibusCtx->this->destino = next_circular_idx(onibusCtx->this->origem, onibusCtx->pontos_de_onibus_list->length);

    busy_wait_ms(rand_int(500, 1000));

    while (pthread_mutex_trylock(onibusCtx->pontos_de_onibus_list->items[onibusCtx->this->destino]->cond_lock) != 0)
    {
      onibusCtx->this->destino = next_circular_idx(onibusCtx->this->destino, onibusCtx->pontos_de_onibus_list->length);
      busy_wait_ms(rand_int(500, 1000));
    }

    onibusCtx->this->origem = onibusCtx->this->destino;
    onibusCtx->this->destino = -1;
    onibusCtx->pontos_de_onibus_list->items[onibusCtx->this->origem]->onibus_ocupando = onibusCtx->this->id;

    busy_wait_ms(3000);

    onibusCtx->pontos_de_onibus_list->items[onibusCtx->this->origem]->onibus_ocupando = -1;
    pthread_mutex_unlock(onibusCtx->pontos_de_onibus_list->items[onibusCtx->this->origem]->cond_lock);
  }

  free(onibusCtx);
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