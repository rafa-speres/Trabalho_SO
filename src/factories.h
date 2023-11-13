#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int onibus_ocupando; // -1 se tiver vazio
    int id;
} PontoDeOnibus;

typedef struct {
    int ocupacao; // -1 se tiver vazio
    int id_onibus;
} AssentoOnibus;

typedef struct {
    int id;
    AssentoOnibus** assentos;
} Onibus;

typedef struct {
    int id;
} Passageiro;

// Funcoes ponto de onibus
PontoDeOnibus **create_many_PontoDeOnibus(int size);
Onibus **create_many_Onibus(int size, int num_assentos);
Passageiro **create_many_Passageiro(int size);
void print_PontoDeOnibus(PontoDeOnibus *p);
