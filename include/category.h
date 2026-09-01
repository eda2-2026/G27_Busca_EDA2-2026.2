#ifndef CATEGORY_H
#define CATEGORY_H

#include "domain.h"

#define NUM_CATEGORIAS 3

typedef struct NoEscolha {
    Decisao decisao;
    int evento_id;
    struct NoEscolha *proximo;
} NoEscolha;

typedef struct {
    NoEscolha *buckets[NUM_CATEGORIAS];
    int contagem[NUM_CATEGORIAS];
} HistoricoEscolhas;

void inicializar_historico(HistoricoEscolhas *h);
int  categorizar(int impacto);
void registrar_escolha(HistoricoEscolhas *h, Decisao d, int evento_id);
int  obter_categoria_dominante(const HistoricoEscolhas *h);
void liberar_historico(HistoricoEscolhas *h);

#endif
