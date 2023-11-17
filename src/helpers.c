#include <stdbool.h>
#include "helpers.h"
#include "factories.h"

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