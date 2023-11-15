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
    int origem; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int qtd_pontos;
} Onibus;

typedef struct
{
    int id;
    int origem; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
    int destino; // pontos estão indexados em 0, i.e, o primeiro ponto é o 0
} Passageiro;

// Funcoes ponto de onibus
PontoDeOnibus **create_many_PontoDeOnibus(int size);
Onibus **create_many_Onibus(int size, int qtd_assentos, int qtd_pontos);
Passageiro **create_many_Passageiro(int size, int qtd_pontos);
void print_PontoDeOnibus(PontoDeOnibus *p);

#endif