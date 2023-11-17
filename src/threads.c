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