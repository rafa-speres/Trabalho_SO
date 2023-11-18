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
    ponto_de_onibus->passageiros_list = createList();
    ponto_de_onibus->ponto_de_onibus_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->onibus_management_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->onibus_management_lock = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    ponto_de_onibus->ponto_de_onibus_management_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    ponto_de_onibus->ponto_de_onibus_management_lock = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));

    assert(ponto_de_onibus != NULL);
    assert(ponto_de_onibus->passageiros_list != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_mutex != NULL);
    assert(ponto_de_onibus->onibus_management_mutex != NULL);
    assert(ponto_de_onibus->onibus_management_lock != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_management_mutex != NULL);
    assert(ponto_de_onibus->ponto_de_onibus_management_lock != NULL);

    pthread_mutex_init(ponto_de_onibus->ponto_de_onibus_mutex, NULL);
    pthread_mutex_init(ponto_de_onibus->onibus_management_mutex, NULL);
    pthread_cond_init(ponto_de_onibus->onibus_management_lock, NULL);
    pthread_mutex_init(ponto_de_onibus->ponto_de_onibus_management_mutex, NULL);
    pthread_cond_init(ponto_de_onibus->ponto_de_onibus_management_lock, NULL);

    ponto_de_onibus->id = id;
    ponto_de_onibus->onibus_ocupando = -1;

    for (int idx = 0; idx < passageiros_list->length; idx++)
    {
        if (passageiros_list->items[idx]->origem == id)
        {
            appendList(ponto_de_onibus->passageiros_list, passageiros_list->items[idx]);
        }
    }

    return ponto_de_onibus;
}

Onibus *create_Onibus(int onibus_id, int qtd_assentos, PontoDeOnibusList *ponto_de_onibus_list)
{
    Onibus *o = (Onibus *)malloc(sizeof(Onibus));
    assert(o != NULL);

    o->id = onibus_id;
    o->passageiros_list = createList();
    o->qtd_assentos = qtd_assentos;
    o->origem = rand_int(0, ponto_de_onibus_list->length - 1);
    while (ponto_de_onibus_list->items[o->origem]->onibus_ocupando != -1)
        o->origem = rand_int(0, ponto_de_onibus_list->length - 1);
    o->destino = -1;

    ponto_de_onibus_list->items[o->origem]->onibus_ocupando = o->id;

    assert(o->passageiros_list != NULL);

        return o;
}

Passageiro *create_Passageiro(int passageiro_id, int qtd_pontos)
{
    Passageiro *p = (Passageiro *)malloc(sizeof(Passageiro));
    assert(p != NULL);

    p->id = passageiro_id;
    p->origem = rand_int(0, qtd_pontos - 1);
    p->destino = rand_int(0, qtd_pontos - 1);
    p->finalizado = false;

    while (p->origem == p->destino)
        p->destino = rand_int(0, qtd_pontos - 1);

    return p;
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

OnibusList *create_many_Onibus(int length, int qtd_assentos, PontoDeOnibusList *ponto_de_onibus_list)
{
    OnibusList *list = (OnibusList *)malloc(sizeof(OnibusList));
    list->items = (Onibus **)malloc(length * sizeof(Onibus *));

    assert(list != NULL);
    assert(list->items != NULL);

    list->length = length;

    for (int i = 0; i < length; i++)
    {
        list->items[i] = create_Onibus(i, qtd_assentos, ponto_de_onibus_list);
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
