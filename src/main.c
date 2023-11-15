/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include "factories.h"
#include "threads.h"

void create_threads(
    PontoDeOnibus **pontos_de_onibus_list,
    Onibus **onibus_list,
    Passageiro **passageiros_list,
    pthread_t ponto_de_onibus_threads_list[],
    pthread_t onibus_threads_list[],
    pthread_t passageiros_threads_list[],
    int qtd_pontos,
    int qtd_onibus,
    int qtd_passageiros)
{

    for (int i = 0; i < qtd_pontos; i++)
    {
        if (pthread_create(&ponto_de_onibus_threads_list[i], NULL, thread_PontoDeOnibus, pontos_de_onibus_list[i]) != 0)
        {
            perror("pthread_create(thread_PontoDeOnibus) error");
            exit(1);
        }
    }

    for (int i = 0; i < qtd_onibus; i++)
    {
        if (pthread_create(&onibus_threads_list[i], NULL, thread_Onibus, onibus_list[i]) != 0)
        {
            perror("pthread_create(thread_Onibus) error");
            exit(1);
        }
    }

    for (int i = 0; i < qtd_passageiros; i++)
    {
        if (pthread_create(&passageiros_threads_list[i], NULL, thread_Passageiro, passageiros_list[i]) != 0)
        {
            perror("pthread_create(thread_Passageiro) error");
            exit(1);
        }
    }
}

void join_threads(
    PontoDeOnibus **pontos_de_onibus_list,
    Onibus **onibus_list,
    Passageiro **passageiros_list,
    pthread_t ponto_de_onibus_threads_list[],
    pthread_t onibus_threads_list[],
    pthread_t passageiros_threads_list[],
    int qtd_pontos,
    int qtd_onibus,
    int qtd_passageiros)
{
    for (int i = 0; i < qtd_pontos; i++)
    {
        if (pthread_join(ponto_de_onibus_threads_list[i], NULL) != 0)
        {
            perror("pthread_join(thread_PontoDeOnibus) error");
            exit(3);
        }
    }

    for (int i = 0; i < qtd_onibus; i++)
    {
        if (pthread_join(onibus_threads_list[i], NULL) != 0)
        {
            perror("pthread_join(thread_Onibus) error");
            exit(3);
        }
    }

    for (int i = 0; i < qtd_passageiros; i++)
    {
        if (pthread_join(passageiros_threads_list[i], NULL) != 0)
        {
            perror("pthread_join(thread_Passageiro) error");
            exit(3);
        }
    }
}

int main()
{

    // int i;
    int S, C, P, A;

    // INPUT -- S
    printf("\n- INPUT: Digite o numero de pontos de onibus: ");
    scanf("%d", &S);

    // INPUT -- C
    printf("\n- INPUT: Digite o numero de onibus: ");
    scanf("%d", &C);

    // INPUT -- P
    printf("\n- INPUT: Digite o numero de passageiros: ");
    scanf("%d", &P);
    while (P <= C)
    {
        printf("\n-- ERRO: O numero de passageiros deve ser maior que o numero de onibus.\n-- Digite outro numero: ");
        scanf("%d", &P);
    }

    // INPUT -- A
    printf("\n- INPUT: Digite o numero de assentos em cada onibus: ");
    scanf("%d", &A);
    while ((A <= C) || (A >= P))
    {
        printf("\n-- ERRO: O numero de assentos deve ser maior que o numero de onibus e menor que o numero de passageiros.\n-- Digite outro numero: ");
        scanf("%d", &A);
    }

    PontoDeOnibus **pontos_de_onibus_list = create_many_PontoDeOnibus(S);
    Onibus **onibus_list = create_many_Onibus(C, A, S);
    Passageiro **passageiros_list = create_many_Passageiro(P, S);
    pthread_t ponto_de_onibus_threads_list[S], onibus_threads_list[C], passageiros_threads_list[P];

    create_threads(pontos_de_onibus_list, onibus_list, passageiros_list, ponto_de_onibus_threads_list, onibus_threads_list, passageiros_threads_list, S, C, P);
    join_threads(pontos_de_onibus_list, onibus_list, passageiros_list, ponto_de_onibus_threads_list, onibus_threads_list, passageiros_threads_list, S, C, P);

    return 0;
}