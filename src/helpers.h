#include <stdbool.h>
#include <factories.h>

#ifndef HELPERS
#define HELPERS

bool isFinished(PassageiroList * passageiro_list);
DynamicList *getLandingPassageiros(Onibus *onibus, PontoDeOnibus *ponto_de_onibus);

#endif