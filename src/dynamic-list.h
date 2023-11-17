#ifndef DYNAMIC_LIST
#define DYNAMIC_LIST

typedef struct
{
  void **items;
  int length;
  int capacity;
} DynamicList;

DynamicList *createList();
void appendList(DynamicList *list, void *item);
void *shiftList(DynamicList *list);

#endif