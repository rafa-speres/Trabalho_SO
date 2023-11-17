#include <stdlib.h>
#include <assert.h>
#include "dynamic-list.h"

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