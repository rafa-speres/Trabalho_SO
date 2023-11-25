/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Create e Context
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "factories.h"
#include "utils.h"
#include "dynamic_list.h"

PontoDeOnibus *create_PontoDeOnibus(int id, PassageiroList *passageiros_list)
{
    PontoDeOnibus *ponto_de_onibus = (PontoDeOnibus *)malloc(sizeof(PontoDeOnibus));
    
    assert(ponto_de_onibus != NULL);
    
    ponto_de_onibus->passageiros_list = createList();
    ponto_de_onibus->ponto_de_onibus_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->onibus_management_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->onibus_management_lock = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    ponto_de_onibus->ponto_de_onibus_management_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->ponto_de_onibus_management_lock = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    ponto_de_onibus->landing_passageiros_semaphore = (sem_t *)malloc(sizeof(sem_t));

    assert(ponto_de_onibus->passageiros_list != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_mutex != NULL);
    assert(ponto_de_onibus->onibus_management_mutex != NULL);
    assert(ponto_de_onibus->onibus_management_lock != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_management_mutex != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_management_lock != NULL);
    assert(ponto_de_onibus->landing_passageiros_semaphore != NULL);

    pthread_mutex_init(ponto_de_onibus->ponto_de_onibus_mutex, NULL);
    pthread_mutex_init(ponto_de_onibus->onibus_management_mutex, NULL);
    pthread_cond_init(ponto_de_onibus->onibus_management_lock, NULL);
    pthread_mutex_init(ponto_de_onibus->ponto_de_onibus_management_mutex, NULL);
    pthread_cond_init(ponto_de_onibus->ponto_de_onibus_management_lock, NULL);
    sem_init(ponto_de_onibus->landing_passageiros_semaphore, 0, 0);

    ponto_de_onibus->id = id;
    ponto_de_onibus->onibus_ocupando = -1;
    ponto_de_onibus->finalizado = false;

    for (int idx = 0; idx < passageiros_list->length; idx++)
    {
        if (passageiros_list->items[idx]->origem == id)
        {
            appendList(ponto_de_onibus->passageiros_list, passageiros_list->items[idx]);
        }
    }

    return ponto_de_onibus;
}

Onibus *create_Onibus(int onibus_id, int qtd_assentos)
{
    Onibus *o = (Onibus *)malloc(sizeof(Onibus));
    
    assert(o != NULL);
    
    o->data_saida = (struct timeval *)malloc(sizeof(struct timeval));
    o->data_chegada = (struct timeval *)malloc(sizeof(struct timeval));
    
    assert(o->data_saida != NULL);
    assert(o->data_saida != NULL);

    o->id = onibus_id;
    o->passageiros_list = createList();
    o->qtd_assentos = qtd_assentos;
    o->origem = -1;
    o->destino = -1;

    assert(o->passageiros_list != NULL);

    return o;
}

Passageiro *create_Passageiro(int passageiro_id, int qtd_pontos)
{
    Passageiro *passageiro = (Passageiro *)malloc(sizeof(Passageiro));
    
    assert(passageiro != NULL);
    
    passageiro->passageiro_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    passageiro->passageiro_lock = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    passageiro->data_inicio = (struct tm *)malloc(sizeof(struct tm));
    passageiro->data_saida = (struct tm *)malloc(sizeof(struct tm));
    passageiro->data_chegada = (struct tm *)malloc(sizeof(struct tm));
    
    assert(passageiro->passageiro_mutex != NULL);
    assert(passageiro->passageiro_lock != NULL);
    assert(passageiro->data_inicio != NULL);
    assert(passageiro->data_saida != NULL);
    assert(passageiro->data_chegada != NULL);

    pthread_mutex_init(passageiro->passageiro_mutex, NULL);
    pthread_cond_init(passageiro->passageiro_lock, NULL);

    passageiro->id = passageiro_id;
    passageiro->origem = rand_int(0, qtd_pontos - 1);
    passageiro->destino = rand_int(0, qtd_pontos - 1);
    passageiro->finalizado = false;

    while (passageiro->origem == passageiro->destino)
        passageiro->destino = rand_int(0, qtd_pontos - 1);

    return passageiro;
}

PontoDeOnibusList *create_many_PontoDeOnibus(int length, PassageiroList *passageiros_list)
{
    PontoDeOnibusList *list = (PontoDeOnibusList *)malloc(sizeof(PontoDeOnibusList));
    list->items = malloc(length * sizeof(PontoDeOnibus *));

    assert(list != NULL);
    assert(list->items != NULL);

    list->length = length;

    for (int i = 0; i < length; i++)
    {
        list->items[i] = create_PontoDeOnibus(i, passageiros_list);
    }

    return list;
}

OnibusList *create_many_Onibus(int length, int qtd_assentos)
{
    OnibusList *list = (OnibusList *)malloc(sizeof(OnibusList));
    list->items = (Onibus **)malloc(length * sizeof(Onibus *));

    assert(list != NULL);
    assert(list->items != NULL);

    list->length = length;

    for (int i = 0; i < length; i++)
    {
        list->items[i] = create_Onibus(i, qtd_assentos);
    }

    return list;
}

PassageiroList *create_many_Passageiro(int length, int qtd_pontos)
{
    PassageiroList *list = (PassageiroList *)malloc(sizeof(PassageiroList));
    list->items = (Passageiro **)malloc(length * sizeof(Passageiro *));

    assert(list != NULL);
    assert(list->items != NULL);

    list->length = length;

    for (int i = 0; i < length; i++)
    {
        list->items[i] = create_Passageiro(i, qtd_pontos);
    }

    return list;
}

PontoDeOnibusContext *create_PontoDeOnibusContext(PontoDeOnibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list)
{
    PontoDeOnibusContext *context = (PontoDeOnibusContext *)malloc(sizeof(PontoDeOnibusContext));

    context->this = this;
    context->pontos_de_onibus_list = pontos_de_onibus_list;
    context->onibus_list = onibus_list;
    context->passageiro_list = passageiro_list;

    return context;
}

OnibusContext *create_OnibusContext(Onibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list)
{
    OnibusContext *context = (OnibusContext *)malloc(sizeof(OnibusContext));

    context->this = this;
    context->pontos_de_onibus_list = pontos_de_onibus_list;
    context->onibus_list = onibus_list;
    context->passageiro_list = passageiro_list;

    return context;
}

PassageiroContext *create_PassageiroContext(Passageiro *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list)
{
    PassageiroContext *context = (PassageiroContext *)malloc(sizeof(PassageiroContext));

    context->this = this;
    context->pontos_de_onibus_list = pontos_de_onibus_list;
    context->onibus_list = onibus_list;
    context->passageiro_list = passageiro_list;

    return context;
}

Context *create_Context(PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list)
{
    Context *context = (Context *)malloc(sizeof(Context));

    context->pontos_de_onibus_list = pontos_de_onibus_list;
    context->onibus_list = onibus_list;
    context->passageiro_list = passageiro_list;

    return context;
}

void print_PontoDeOnibus(PontoDeOnibus *p)
{
    printf("\nPonto de Onibus %d\n", p->id);
    if (p->onibus_ocupando != -1)
    {
        printf("Ocupacao: %d\n\n", p->onibus_ocupando);
    }
    else
    {
        printf("Ocupacao: Vazio\n\n");
    }
}
