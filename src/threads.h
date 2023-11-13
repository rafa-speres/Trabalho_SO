#ifndef THREADS
#define THREADS

void *thread_PontoDeOnibus(void *arg);
void *thread_Onibus(void *arg);
void *thread_Passageiro(void *arg);

#endif