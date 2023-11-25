/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Lista
*/
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dynamic_list.h"

#define INITIAL_CAPACITY 8

DynamicList *createList()
{
  DynamicList *list = (DynamicList *)malloc(sizeof(DynamicList));
  list->items = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
  assert(list != NULL);
  assert(list->items != NULL);

  list->capacity = INITIAL_CAPACITY;
  list->length = 0;

  return list;
}

void appendList(DynamicList *list, void *item)
{
  if (list->length == list->capacity)
  {
    list->capacity *= 2;
    list->items = (void **)realloc(list->items, list->capacity * sizeof(void *));

    assert(list->items != NULL);
  }

  list->items[list->length++] = item;
}

void *shiftList(DynamicList *list)
{
  if (list->length == 0)
    return NULL;

  void *item = list->items[0];

  for (int idx = 1; idx < list->length; idx++)
  {
    list->items[idx - 1] = list->items[idx];
  }

  list->length--;

  return item;
}

void removeFromList(DynamicList *list, void *item)
{
  if (list->length == 0) return;

  int idx = 0;

  while (idx < list->length) {
    if (list->items[idx] == item) {
      list->items[idx] = NULL;
      break;
    }
    
    idx++;
  }

  for (int i = idx; i < list->length; i++) {
    list->items[i] = list->items[i + 1];
  }

  list->length--;
}