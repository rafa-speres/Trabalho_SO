/* GRUPO 4
- Rodrigo Teixeira Ribeiro da Silva, 11816164
- Rafael Scalon Peres Conti, 11871181
- João Otávio Cano, 11858651
- Henrique Gualberto Marques, 13692380
- Gustavo Alves da Silva Souza, 13727485
*/
#ifndef THREADS
#define THREADS

void *thread_PontoDeOnibus(void *arg);
void *thread_Onibus(void *arg);
void *thread_Passageiro(void *arg);
void *thread_state_printer(void *arg);

#endif