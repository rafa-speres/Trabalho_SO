#include <stdbool.h>
#include <stdlib.h>
#include "helpers.h"
#include "factories.h"
#include "dynamic-list.h"

DynamicList *extractLandingPassageiros(Onibus *onibus, PontoDeOnibus *ponto_de_onibus)
{
  DynamicList *landing_passageiros_list = createList();

  for (int idx = 0; idx < onibus->passageiros_list->length; idx++)
  {
    Passageiro *passageiro = (Passageiro *)onibus->passageiros_list->items[idx];

    if (passageiro->destino == ponto_de_onibus->id)
    {
      appendList(landing_passageiros_list, passageiro);
    }
  }

  DynamicList *new_onibus_passageiros_list = filterList(onibus->passageiros_list, landing_passageiros_list);
  free(onibus->passageiros_list);
  onibus->passageiros_list = new_onibus_passageiros_list;

  return landing_passageiros_list;
}

bool isFinished(PassageiroList *passageiro_list)
{
  for (int idx = 0; idx < passageiro_list->length; idx++)
  {
    if (passageiro_list->items[idx]->finalizado == false)
    {
      return false;
    }
  }

  return true;
}