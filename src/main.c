/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485
*/
#include "factories.h"

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
    Onibus **onibus_list = create_many_Onibus(C, A);
    Passageiro **passageiros_list = create_many_Passageiro(P);

    // pthread_t S_handle[S], C_handle[C], P_handle[P];

    // for (int i = 0; i < S; i++)
    // { // criando threads de pontos
    //   // deve funcionar como fila circular
    // }

    // for (int i = 0; i < C; i++)
    // { // criando threads de carros
    //   // começam em pontos aleatorios (devem estar disponiveis)
    // }

    // for (int i = 0; i < P; i++)
    // { // criando threads de passageiros
    // }

    return 0;
}