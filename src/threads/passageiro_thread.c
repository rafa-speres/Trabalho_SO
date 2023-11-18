#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "factories.h"
#include "helpers.h"
#include "utils.h"

void *thread_Passageiro(void *arg)
{
  PassageiroContext *ctx = (PassageiroContext *)arg;
  // Passageiro *this = ctx->this;
  // printf("Passageiro %d | origem: %d | destino: %d\n", ctx->this->id, ctx->this->origem, ctx->this->destino);

  // while (isFinished(ctx->passageiro_list) == false)
  // {
  //   }

  free(ctx);
  pthread_exit(NULL);
  return NULL;
}