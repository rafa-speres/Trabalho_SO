#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "factories.h"
#include "utils.h"

PontoDeOnibus *create_PontoDeOnibus(int id, PassageiroList *passageiros_list)
{
    PontoDeOnibus *ponto_de_onibus = (PontoDeOnibus *)malloc(sizeof(PontoDeOnibus));
    ponto_de_onibus->passageiros_list = (PassageiroList *)malloc(sizeof(PassageiroList *));
    assert(ponto_de_onibus != NULL);
    assert(ponto_de_onibus->passageiros_list != NULL);

    int passageiros_count = 0;

    for (int idx = 0; idx < passageiros_list->length; idx++)
    {
        if (passageiros_list->items[idx]->origem == id)
        {
            passageiros_count++;
        }
    }

    ponto_de_onibus->id = id;
    ponto_de_onibus->onibus_ocupando = -1;
    ponto_de_onibus->passageiros_list->items = (Passageiro **)malloc(passageiros_count * sizeof(Passageiro *));
    ponto_de_onibus->passageiros_list->length = passageiros_count;

    for (int fromIdx = 0, toIdx = 0; fromIdx < passageiros_list->length; fromIdx++)
    {
        if (passageiros_list->items[fromIdx]->origem == id)
        {
            ponto_de_onibus->passageiros_list->items[toIdx++] = passageiros_list->items[fromIdx];
        }
    }

    return ponto_de_onibus;
}

AssentoOnibus *create_AssentoOnibus(int ocupacao, int id_onibus)
{
    AssentoOnibus *a = (AssentoOnibus *)malloc(sizeof(AssentoOnibus));
    assert(a != NULL);

    a->ocupacao = ocupacao;
    a->id_onibus = id_onibus;

    return a;
}

Onibus *create_Onibus(int onibus_id, int qtd_assentos, PontoDeOnibusList *ponto_de_onibus_list)
{
    Onibus *o = (Onibus *)malloc(sizeof(Onibus));
    assert(o != NULL);

    o->id = onibus_id;
    o->assentos = (AssentoOnibus **)malloc(qtd_assentos * sizeof(AssentoOnibus *));
    o->qtd_assentos = qtd_assentos;
    o->origem = rand_int(0, ponto_de_onibus_list->length - 1);
    while (ponto_de_onibus_list->items[o->origem]->onibus_ocupando != -1)
        o->origem = rand_int(0, ponto_de_onibus_list->length - 1);
    o->destino = -1;

    ponto_de_onibus_list->items[o->origem]->onibus_ocupando = o->id;

    assert(o->assentos != NULL);

    for (int i = 0; i < qtd_assentos; i++)
    {
        o->assentos[i] = create_AssentoOnibus(-1, onibus_id);
        o->assentos[i]->ocupacao = -1;
        o->assentos[i]->id_onibus = onibus_id;
    }

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
