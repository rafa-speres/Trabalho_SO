#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"
#include "debug.h"

void *thread_PontoDeOnibus(void *arg)
{
  PontoDeOnibusContext *ctx = (PontoDeOnibusContext *)arg;
  PontoDeOnibus *this = ctx->this;

  while (isFinished(ctx->passageiro_list) == false)
  {
    pthread_mutex_lock(this->ponto_de_onibus_management_mutex);
    debug_printf("PONTO %d ESTÁ LIVRE PARA RECEBER ONIBUS\n", this->id);
    pthread_cond_wait(this->ponto_de_onibus_management_lock, this->ponto_de_onibus_management_mutex);

    if (this->onibus_ocupando == -1)
    {
      pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
      break;
    }

    debug_printf("PONTO %d RECEBEU ONIBUS %d\n", this->id, this->onibus_ocupando);

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
      Passageiro *passageiro = (Passageiro *)shiftList(this->passageiros_list);

      debug_printf("PASSAGEIRO %d ERBACANDO NO ONIBUS %d NO PONTO %d\n", passageiro->id, onibus->id, this->id);

      appendList(onibus->passageiros_list, passageiro);
    }

    busy_wait_ms(500);

    debug_printf("PONTO %d DESPACHOU ONIBUS %d\n", this->id, this->onibus_ocupando);

    pthread_cond_signal(this->onibus_management_lock);
    pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
  }

  sem_destroy(this->landing_passageiros_semaphore);

  debug_printf("PONTO %d FINALIZOU\n", this->id);

  this->finalizado = true;

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}
