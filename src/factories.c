#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "factories.h"
#include "utils.h"

PontoDeOnibus *create_PontoDeOnibus(int sent_id)
{
    PontoDeOnibus *p = (PontoDeOnibus *)malloc(sizeof(PontoDeOnibus));
    assert(p != NULL);

    p->id = sent_id;
    p->onibus_ocupando = -1;

    return p;
}

AssentoOnibus *create_AssentoOnibus(int ocupacao, int id_onibus)
{
    AssentoOnibus *a = (AssentoOnibus *)malloc(sizeof(AssentoOnibus));
    assert(a != NULL);

    a->ocupacao = ocupacao;
    a->id_onibus = id_onibus;

    return a;
}

Onibus *create_Onibus(int onibus_id, int qtd_assentos, int qtd_pontos)
{
    Onibus *o = (Onibus *)malloc(sizeof(Onibus));
    assert(o != NULL);

    o->id = onibus_id;
    o->assentos = (AssentoOnibus **)malloc(qtd_assentos * sizeof(AssentoOnibus *));
    o->qtd_assentos = qtd_assentos;
    o->origem = rand_int(0, qtd_pontos - 1);
    o->destino = next_circular_idx(o->origem, qtd_pontos);
    o->qtd_pontos = qtd_pontos;

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

    while (p->origem == p->destino) p->destino = rand_int(0, qtd_pontos - 1);

    return p;
}

PontoDeOnibus **create_many_PontoDeOnibus(int size)
{
    PontoDeOnibus **pontos_de_onibus = malloc(size * sizeof(PontoDeOnibus *));
    assert(pontos_de_onibus != NULL);

    for (int i = 0; i < size; i++)
    {
        pontos_de_onibus[i] = create_PontoDeOnibus(i);
        // print_PontoDeOnibus(pontos_de_onibus[i]);
    }

    return pontos_de_onibus;
}

Onibus **create_many_Onibus(int size, int qtd_assentos, int qtd_pontos)
{
    Onibus **onibus_array = (Onibus **)malloc(size * sizeof(Onibus *));
    assert(onibus_array != NULL);

    for (int i = 0; i < size; i++)
    {
        onibus_array[i] = create_Onibus(i, qtd_assentos, qtd_pontos);
    }

    return onibus_array;
}

Passageiro **create_many_Passageiro(int size, int qtd_pontos)
{
    Passageiro **passageiro_array = (Passageiro **)malloc(size * sizeof(Passageiro *));
    assert(passageiro_array != NULL);

    for (int i = 0; i < size; i++)
    {
        passageiro_array[i] = create_Passageiro(i, qtd_pontos);
    }

    return passageiro_array;
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
