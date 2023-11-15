#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include "factories.h"

void *thread_PontoDeOnibus(void *arg)
{
  PontoDeOnibus *pontoDeOnibus = (PontoDeOnibus *)arg;
  printf("PontoDeOnibus %d\n", pontoDeOnibus->id);
  pthread_exit(NULL);
  return NULL;
}

void *thread_Onibus(void *arg)
{
  Onibus *onibus = (Onibus *)arg;
  printf("Onibus %d | origem: %d | destino: %d\n", onibus->id, onibus->origem, onibus->destino);
  pthread_exit(NULL);
  return NULL;
}

void *thread_Passageiro(void *arg)
{
  Passageiro *passageiro = (Passageiro *)arg;
  printf("Passageiro %d | origem: %d | destino: %d\n", passageiro->id, passageiro->origem, passageiro->destino);
  pthread_exit(NULL);
  return NULL;
}