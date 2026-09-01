#include <stdlib.h>
#include "category.h"

void inicializar_historico(HistoricoEscolhas *h) {
    if (h == NULL) return;

    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        h->buckets[i] = NULL;
        h->contagem[i] = 0;
    }
}

int categorizar(int impacto) {
    if (impacto >= 2) return 0;
    if (impacto <= -2) return 2;
    return 1;
}

void registrar_escolha(HistoricoEscolhas *h, Decisao d, int evento_id) {
    if (h == NULL) return;

    int bucket = categorizar(d.impacto);

    NoEscolha *novo = malloc(sizeof(NoEscolha));
    if (novo == NULL) return;

    novo->decisao = d;
    novo->evento_id = evento_id;
    novo->proximo = h->buckets[bucket];

    h->buckets[bucket] = novo;
    h->contagem[bucket]++;
}

int obter_categoria_dominante(const HistoricoEscolhas *h) {
    if (h == NULL) return 1;

    int max_idx = 0;

    for (int i = 1; i < NUM_CATEGORIAS; i++) {
        if (h->contagem[i] > h->contagem[max_idx]) {
            max_idx = i;
        }
    }

    return max_idx;
}

void liberar_historico(HistoricoEscolhas *h) {
    if (h == NULL) return;

    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        NoEscolha *atual = h->buckets[i];

        while (atual != NULL) {
            NoEscolha *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }

        h->buckets[i] = NULL;
        h->contagem[i] = 0;
    }
}
