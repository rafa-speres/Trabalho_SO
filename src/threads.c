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
  printf("Onibus %d | partida: %d | chegada: %d\n", onibus->id, onibus->ponto_partida, onibus->ponto_chegada);
  pthread_exit(NULL);
  return NULL;
}

void *thread_Passageiro(void *arg)
{
  Passageiro *passageiro = (Passageiro *)arg;
  printf("Passageiro %d | partida: %d | chegada: %d\n", passageiro->id, passageiro->ponto_partida, passageiro->ponto_chegada);
  pthread_exit(NULL);
  return NULL;
}