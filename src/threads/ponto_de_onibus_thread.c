/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Ponto de Onibus
*/
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

  // Loop principal que executa enquanto há passageiros a serem atendidos no ponto de ônibus
  while (isFinished(ctx->passageiro_list) == false)
  {
    // Garante que somente essa thread consiga manusear essa struct nesse momento
    pthread_mutex_lock(this->ponto_de_onibus_management_mutex);
    debug_printf("PONTO %d ESTÁ LIVRE PARA RECEBER ONIBUS\n", this->id);
    // Ponto espera ser avisado da chegada de um ônibus
    pthread_cond_wait(this->ponto_de_onibus_management_lock, this->ponto_de_onibus_management_mutex);

    // Ponto foi acordado mas não há ônibus ocupando => não há mais ônibus circulando (programa finalizou) e thread ponto pode finalizar também
    if (this->onibus_ocupando == -1)
    {
      pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
      break;
    }

    debug_printf("PONTO %d RECEBEU ONIBUS %d\n", this->id, this->onibus_ocupando);

    // Ônibus que está ocupando o ponto
    Onibus *onibus = ctx->onibus_list->items[this->onibus_ocupando];
    DynamicList *landing_passageiros_list = getLandingPassageiros(onibus, this);

    // Desembarque dos passageiros
    for (int idx = 0; idx < landing_passageiros_list->length; idx++)
    {
      Passageiro *passageiro = (Passageiro *)landing_passageiros_list->items[idx];

      // Acorda passageiro para que ela faça o desembarque
      pthread_cond_signal(passageiro->passageiro_lock);
      // Dorme até passageiro terminar desembarque
      sem_wait(this->landing_passageiros_semaphore);
    }

    // Embarque de passageiros no ônibus enquanto houver assentos disponíveis
    while (onibus->passageiros_list->length < onibus->qtd_assentos && this->passageiros_list->length > 0)
    {
      Passageiro *passageiro = (Passageiro *)shiftList(this->passageiros_list);

      get_current_tm(passageiro->data_saida);

      debug_printf("PASSAGEIRO %d EMBARCANDO NO ONIBUS %d NO PONTO %d\n", passageiro->id, onibus->id, this->id);

      appendList(onibus->passageiros_list, passageiro);
    }

    busy_wait_ms(5000);

    debug_printf("PONTO %d DESPACHOU ONIBUS %d\n", this->id, this->onibus_ocupando);
    // Avisa o onibus para que ele deixe o ponto
    pthread_cond_signal(this->onibus_management_lock);
    // Thread libera o "domínio" dessa struct
    pthread_mutex_unlock(this->ponto_de_onibus_management_mutex);
  }

  sem_destroy(this->landing_passageiros_semaphore);

  debug_printf("PONTO %d FINALIZOU\n", this->id);

  this->finalizado = true;

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}
