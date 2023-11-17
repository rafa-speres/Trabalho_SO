#include <stdbool.h>
#include <pthread.h>
#include "dynamic-list.h"

#ifndef FACTORIES
#define FACTORIES

typedef struct
{
    int id;
    DynamicList *passageiros_list;
    int qtd_assentos;
    int origem;  // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
} Onibus;

typedef struct
{
    int id;
    int origem;  // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    bool finalizado;
} Passageiro;

typedef struct
{
    Onibus **items;
    int length;
} OnibusList;

typedef struct
{
    Passageiro **items;
    int length;
} PassageiroList;

typedef struct
{
    int id;
    DynamicList *passageiros_list;
    int onibus_ocupando; // -1 se tiver vazio
    pthread_mutex_t *ponto_de_onibus_mutex;
    pthread_mutex_t *onibus_management_mutex;
    pthread_cond_t *onibus_management_lock;
    pthread_mutex_t *ponto_de_onibus_management_mutex;
    pthread_cond_t *ponto_de_onibus_management_lock;
} PontoDeOnibus;

typedef struct
{
    PontoDeOnibus **items;
    int length;
} PontoDeOnibusList;

typedef struct
{
    void **items;
    int length;
} GenericList;

typedef struct
{
    PontoDeOnibus *this;
    PontoDeOnibusList *pontos_de_onibus_list;
    OnibusList *onibus_list;
    PassageiroList *passageiro_list;
} PontoDeOnibusContext;

typedef struct
{
    Onibus *this;
    PontoDeOnibusList *pontos_de_onibus_list;
    OnibusList *onibus_list;
    PassageiroList *passageiro_list;
} OnibusContext;

typedef struct
{
    Passageiro *this;
    PontoDeOnibusList *pontos_de_onibus_list;
    OnibusList *onibus_list;
    PassageiroList *passageiro_list;
} PassageiroContext;

typedef struct
{
    PontoDeOnibusList *pontos_de_onibus_list;
    OnibusList *onibus_list;
    PassageiroList *passageiro_list;
} Context;

// Funcoes ponto de onibus
PontoDeOnibusList *create_many_PontoDeOnibus(int length, PassageiroList *passageiros_list);
OnibusList *create_many_Onibus(int length, int qtd_assentos, PontoDeOnibusList *ponto_de_onibus_list);
PassageiroList *create_many_Passageiro(int length, int qtd_pontos);
PontoDeOnibusContext *create_PontoDeOnibusContext(PontoDeOnibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
OnibusContext *create_OnibusContext(Onibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
PassageiroContext *create_PassageiroContext(Passageiro *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
Context *create_Context(PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);

void print_PontoDeOnibus(PontoDeOnibus *p);

#endif