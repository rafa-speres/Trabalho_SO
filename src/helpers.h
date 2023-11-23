#include <stdbool.h>

#include <factories.h>

#ifndef HELPERS
#define HELPERS

bool isFinished(PassageiroList *passageiro_list);
DynamicList *getLandingPassageiros(Onibus *onibus, PontoDeOnibus *ponto_de_onibus);
void savePassageiroData(int passageiro_id, struct tm *data_inicio, struct tm *data_saida, struct tm *data_chegada, int ponto_destino_id);

#endif