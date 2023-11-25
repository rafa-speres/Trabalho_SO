/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para auxilio geral (passageiros e lista de passageiros)
*/
#include <stdbool.h>

#include <factories.h>

#ifndef HELPERS
#define HELPERS

bool isFinished(PassageiroList *passageiro_list);
DynamicList *getLandingPassageiros(Onibus *onibus, PontoDeOnibus *ponto_de_onibus);
void savePassageiroData(int passageiro_id, struct tm *data_inicio, struct tm *data_saida, struct tm *data_chegada, int ponto_destino_id);

#endif