#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "helpers.h"
#include "factories.h"
#include "dynamic_list.h"

DynamicList *getLandingPassageiros(Onibus *onibus, PontoDeOnibus *ponto_de_onibus)
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

void savePassageiroData(int passageiro_id, struct tm *data_inicio, struct tm *data_saida, struct tm *data_chegada, int ponto_destino_id)
{
  char filename[64];
  sprintf(filename, "./traces/passageiro%d.trace", passageiro_id);
  FILE *file = fopen(filename, "w");

  if (file == NULL)
  {
    printf("Error opening file passageiro%d.trace file\n", passageiro_id);
    exit(1);
  }

  fprintf(file, "INÍCIO, SAÍDA, CHEGADA, PONTO_DESTINO\n");
  fprintf(file, "%d:%d, %d:%d, %d:%d, %d",
          data_inicio->tm_min, data_inicio->tm_sec,
          data_saida->tm_min, data_saida->tm_sec,
          data_chegada->tm_min, data_chegada->tm_sec,
          ponto_destino_id);

  fclose(file);
}