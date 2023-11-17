#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "printer_thread.h"
#include "factories.h"
#include "helpers.h"

void clearTerminal()
{
  printf("\033[2J\033[H");
}

void sleep(int ms)
{
  struct timespec sleep_time;

  sleep_time.tv_sec = 0;
  sleep_time.tv_nsec = 1000000 * ms;

  nanosleep(&sleep_time, NULL);
}

void *thread_state_printer(void *arg)
{
  Context *context = (Context *)arg;

  while (isFinished(context) == false)
  {
    for (int i = 0; i < context->pontos_de_onibus_list->length; i++)
    {
      PontoDeOnibus *ponto_de_onibus = context->pontos_de_onibus_list->items[i];
      int passageiros_count = 0;

      for (int j = 0; j < context->passageiro_list->length; j++)
      {
        if (context->passageiro_list->items[j]->origem == ponto_de_onibus->id)
        {
          passageiros_count++;
        }
      }

      printf("\nPonto %d)\n", ponto_de_onibus->id);
      printf("  Onibus: %d\n", ponto_de_onibus->onibus_ocupando);
      printf("  Passageiros: %d\n", passageiros_count);
    }

    sleep(50);
    clearTerminal();
  }

  free(context);
  pthread_exit(NULL);
  return NULL;
}