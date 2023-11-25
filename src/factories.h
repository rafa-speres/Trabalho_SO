/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Create e Context
*/
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include "dynamic_list.h"

#ifndef FACTORIES
#define FACTORIES

typedef struct
{
    int id;
    DynamicList *passageiros_list;
    int qtd_assentos;
    int origem;  // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    struct timeval *data_saida;
    struct timeval *data_chegada; 
} Onibus;

typedef struct
{
    int id;
    int origem;  // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    struct tm *data_inicio;
    struct tm *data_saida;
    struct tm *data_chegada;
    bool finalizado;
    pthread_mutex_t *passageiro_mutex;
    pthread_cond_t *passageiro_lock;
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
    sem_t *landing_passageiros_semaphore; // como não sabemos quantos passageiros desembarcarão com o auxílio do sem, a inicialização é feita dentro da thread
    bool finalizado;
} PontoDeOnibus;

typedef struct
{
    PontoDeOnibus **items;
    int length;
} PontoDeOnibusList;

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
OnibusList *create_many_Onibus(int length, int qtd_assentos);
PassageiroList *create_many_Passageiro(int length, int qtd_pontos);
PontoDeOnibusContext *create_PontoDeOnibusContext(PontoDeOnibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
OnibusContext *create_OnibusContext(Onibus *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
PassageiroContext *create_PassageiroContext(Passageiro *this, PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);
Context *create_Context(PontoDeOnibusList *pontos_de_onibus_list, OnibusList *onibus_list, PassageiroList *passageiro_list);

void print_PontoDeOnibus(PontoDeOnibus *p);

#endif