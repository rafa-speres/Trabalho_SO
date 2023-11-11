#include "functions.h"

PontoDeOnibus *create_PontoDeOnibus(int sent_id) {
    PontoDeOnibus *p = (PontoDeOnibus *)malloc(sizeof(PontoDeOnibus));
    assert(p != NULL);

    p->id = sent_id;
    p->onibus_ocupando = -1;
    
    return p;
}

void print_PontoDeOnibus(PontoDeOnibus *p) {
    printf("\nPonto de Onibus %d\n", p->id);
    if (p->onibus_ocupando != -1) {
        printf("Ocupacao: %d\n\n", p->onibus_ocupando);
    } else {
        printf("Ocupacao: Vazio\n\n");

    }
}
