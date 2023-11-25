/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485

Funcoes para Lista
*/
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
void removeFromList(DynamicList *list, void *item);

#endif