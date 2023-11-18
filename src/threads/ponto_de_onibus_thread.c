#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"

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

    DynamicList *landing_passageiros_list = getLandingPassageiros(onibus, this);

    if (landing_passageiros_list->length > 0)
    {

      for (int idx = 0; idx < landing_passageiros_list->length; idx++)
      {
        Passageiro *passageiro = (Passageiro *)landing_passageiros_list->items[idx];

        pthread_cond_signal(passageiro->passageiro_lock);
        sem_wait(this->landing_passageiros_semaphore);
      }
    }

    while (onibus->passageiros_list->length < onibus->qtd_assentos && this->passageiros_list->length > 0)
    {
      appendList(onibus->passageiros_list, shiftList(this->passageiros_list));
    }

    busy_wait_ms(500);

    // printf("PONTO %d ENTREGOU %d\n", this->id, this->onibus_ocupando);

    pthread_cond_signal(this->onibus_management_lock);
    pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
  }

  sem_destroy(this->landing_passageiros_semaphore);

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}
