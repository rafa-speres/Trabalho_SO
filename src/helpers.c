#include <stdbool.h>
#include "helpers.h"
#include "factories.h"

bool isFinished(Context *ctx)
{
  for (int idx = 0; idx < ctx->passageiro_list->length; idx++) {
    if (ctx->passageiro_list->items[idx]->finalizado == false) {
      return false;
    }
  }

  return true;
}