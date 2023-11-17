#include <stdbool.h>

#ifndef FACTORIES
#define FACTORIES

typedef struct
{
    int onibus_ocupando; // -1 se tiver vazio
    int id;
} PontoDeOnibus;

typedef struct
{
    int ocupacao; // -1 se tiver vazio
    int id_onibus;
} AssentoOnibus;

typedef struct
{
    int id;
    AssentoOnibus **assentos;
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
    PontoDeOnibus **items;
    int length;
} PontoDeOnibusList;

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
PontoDeOnibusList *create_many_PontoDeOnibus(int length);
OnibusList *create_many_Onibus(int length, int qtd_assentos, PontoDeOnibusList *ponto_de_onibus_list);
PassageiroList *create_many_Passageiro(int length, int qtd_pontos);
PontoDeOnibusContext *create_PontoDeOnibusContext(PontoDeOnibus* this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
OnibusContext *create_OnibusContext(Onibus* this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
PassageiroContext *create_PassageiroContext(Passageiro* this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
Context *create_Context(PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
void print_PontoDeOnibus(PontoDeOnibus *p);

#endif