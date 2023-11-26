/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Passageiro
*/
#include "threads.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "factories.h"
#include "dynamic_list.h"
#include "helpers.h"
#include "utils.h"
#include "debug.h"

PontoDeOnibus *getPassageiroPontoDeOnibus(PassageiroContext *ctx)
{
  return ctx->pontos_de_onibus_list->items[ctx->this->destino];
}

Onibus *getPassageiroOnibus(PassageiroContext *ctx)
{
  return ctx->onibus_list->items[ctx->pontos_de_onibus_list->items[ctx->this->destino]->onibus_ocupando];
}

void *thread_Passageiro(void *arg)
{
  PassageiroContext *ctx = (PassageiroContext *)arg;
  Passageiro *this = ctx->this;

  // Registro do horário em que "passageiro chegou no ponto"
  get_current_tm(this->data_inicio);

  // Garante que somente essa thread consiga manusear essa struct nesse momento
  pthread_mutex_lock(this->passageiro_mutex);
  // Passageiro espera sinal da ponto_de_onibus_thread para descer no destino
  pthread_cond_wait(this->passageiro_lock, this->passageiro_mutex);

  PontoDeOnibus *ponto_de_onibus = getPassageiroPontoDeOnibus(ctx);
  Onibus *onibus = getPassageiroOnibus(ctx);

  debug_printf("PASSAGEIRO %d DESEMBARCANDO DO ONIBUS %d NO PONTO %d\n", this->id, onibus->id, ponto_de_onibus->id);

  // Passagerio chegou ao ponto de destino e é removido da lista de passageiros
  removeFromList(onibus->passageiros_list, this);
  // Registro do horário de desembarque do passageiro
  get_current_tm(this->data_chegada);

  // Passageiro resolve o que precisa resolver nesse local
  busy_wait_ms(500);

  debug_printf("PASSAGEIRO %d FINALIZANDO\n", this->id);

  // Registro das infromações do passageiro no arquivo de trace
  savePassageiroData(this->id, this->data_inicio, this->data_saida, this->data_chegada, this->destino);
  this->finalizado = true;

  // Passageiro termina desembarque a acorda ponto de onibus
  sem_post(ponto_de_onibus->landing_passageiros_semaphore);
  // Thread libera o "domínio" dessa struct
  pthread_mutex_unlock(this->passageiro_mutex);

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}