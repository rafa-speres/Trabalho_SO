#include "threads.h"
#include <pthread.h>
#include <stdio.h>

void *thread_PontoDeOnibus(void *arg) {
  printf("thread_PontoDeOnibus\n");
  pthread_exit(NULL);
}

void *thread_Onibus(void *arg) {
  printf("thread_Onibus\n");
  pthread_exit(NULL);
}

void *thread_Passageiro(void *arg) {
  printf("thread_Passageiro\n");
  pthread_exit(NULL);
}