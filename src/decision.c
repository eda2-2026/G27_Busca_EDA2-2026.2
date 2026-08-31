#include <stdlib.h>
#include "decision.h"

void adicionar_decisao(NoDecisao **inicio, Decisao decisao) {
    NoDecisao *novo = malloc(sizeof(NoDecisao));

    if (novo == NULL) return;

    novo->decisao = decisao;
    novo->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
        return;
    }

    NoDecisao *atual = *inicio;

    while (atual->proximo != NULL) atual = atual->proximo;

    atual->proximo = novo;
}

NoDecisao *buscar_decisao(NoDecisao *inicio, int id) {
    NoDecisao *atual = inicio;

    while (atual != NULL) {
        if (atual->decisao.id == id) return atual;

        atual = atual->proximo;
    }

    return NULL;
}

void liberar_decisoes(NoDecisao *inicio) {
    NoDecisao *atual = inicio;

    while (atual != NULL) {
        NoDecisao *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}