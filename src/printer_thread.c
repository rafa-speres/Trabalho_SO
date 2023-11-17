#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "printer_thread.h"
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void clearTerminal()
{
  printf("\033[2J\033[H");
}

void *thread_state_printer(void *arg)
{
  Context *context = (Context *)arg;

  while (isFinished(context->passageiro_list) == false)
  {
    for (int idx = 0; idx < context->pontos_de_onibus_list->length; idx++)
    {
      PontoDeOnibus *ponto_de_onibus = context->pontos_de_onibus_list->items[idx];

      printf("\nPonto %d)\n", ponto_de_onibus->id);
      printf("  Onibus: %d\n", ponto_de_onibus->onibus_ocupando);
      printf("  Passageiros: %d\n", ponto_de_onibus->passageiros_list->length);
    }

    sleep(50);
    clearTerminal();
  }

  free(context);
  pthread_exit(NULL);
  return NULL;
}