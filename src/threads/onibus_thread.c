/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Onibus
*/
#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "factories.h"
#include "helpers.h"
#include "debug.h"
#include "utils.h"

void travel(Onibus *onibus)
{
  get_current_timeval(onibus->data_saida);
  int waitTimeMs = rand_int(2000, 3000);
  get_incremented_timeval(onibus->data_saida, onibus->data_chegada, waitTimeMs * 1000);
  busy_wait_ms(waitTimeMs);
}

bool runUntilLockBusStop(OnibusContext *ctx)
{
  Onibus *onibus = ctx->this;

  // Programa incializou, alocando uma origem para ônibus
  if (onibus->origem == -1)
    onibus->destino = rand_int(0, ctx->pontos_de_onibus_list->length - 1);
  else
    onibus->destino = next_circular_idx(onibus->origem, ctx->pontos_de_onibus_list->length);

  travel(onibus);

  // Viaja até garantir ponto de ônibus para si
  while (pthread_mutex_trylock(ctx->pontos_de_onibus_list->items[onibus->destino]->ponto_de_onibus_mutex) != 0)
  {
    onibus->destino = next_circular_idx(onibus->destino, ctx->pontos_de_onibus_list->length);
    travel(onibus);
  }

  return true;
}

void *thread_Onibus(void *arg)
{
  OnibusContext *ctx = (OnibusContext *)arg;
  Onibus *this = ctx->this;

  while (runUntilLockBusStop(ctx) && isFinished(ctx->passageiro_list) == false)
  {
    this->origem = this->destino;
    this->destino = -1;
    PontoDeOnibus *ponto_de_onibus = ctx->pontos_de_onibus_list->items[this->origem];
    ponto_de_onibus->onibus_ocupando = this->id;

    debug_printf("ONIBUS %d ENTROU EM %d\n", this->id, ponto_de_onibus->id);

    // Nesse momento, o ônibus e o ponto se "tornam uma coisa só". Esse mutex garante
    // que ou a thread ônibus ou a thread ponto seja executada ao mesmo tempo
    pthread_mutex_lock(ponto_de_onibus->onibus_management_mutex);

    // Ônibus sinaliza para o ponto no qual chegou
    pthread_cond_signal(ponto_de_onibus->ponto_de_onibus_management_lock);
    // Ônibus é avisado que pode sair do ponto
    pthread_cond_wait(ponto_de_onibus->onibus_management_lock, ponto_de_onibus->onibus_management_mutex);

    ponto_de_onibus->onibus_ocupando = -1;

    // Ônibus e ponto "se desassociam"
    pthread_mutex_unlock(ponto_de_onibus->onibus_management_mutex);
    // Ônibus sai do ponto
    pthread_mutex_unlock(ponto_de_onibus->ponto_de_onibus_mutex);

    debug_printf("ONIBUS %d SAIU DE %d\n", this->id, ponto_de_onibus->id);
  }

  // Finalização da thread_Onibus
  debug_printf("ONIBUS %d FINALIZOU\n", this->id);

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}