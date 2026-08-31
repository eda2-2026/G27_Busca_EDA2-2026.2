#include <stdbool.h>
#include <stdio.h>
#include "search.h"

Evento *buscar_evento_binario(Evento eventos[], int tamanho, int id, int *comparacoes) {
    int inicio = 0;
    int fim = tamanho - 1;

    if (comparacoes != NULL) *comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (comparacoes != NULL) (*comparacoes)++;

        if (eventos[meio].id == id) return &eventos[meio];

        if (eventos[meio].id < id) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return NULL;
}

static int busca_sequencial_interna(const int vetor[], int tamanho, int alvo, int *comparacoes, bool verboso) {
    if (comparacoes != NULL) *comparacoes = 0;

    for (int i = 0; i < tamanho; i++) {
        if (comparacoes != NULL) (*comparacoes)++;

        if (verboso) printf("Comparando posicao %d (valor %d) com %d...\n", i, vetor[i], alvo);

        if (vetor[i] == alvo) {
            if (verboso) printf("Encontrado na posicao %d.\n", i);
            return i;
        }
    }

    if (verboso) printf("Nao encontrado apos percorrer %d posicoes.\n", tamanho);

    return -1;
}

int busca_sequencial_vetor(const int vetor[], int tamanho, int alvo, int *comparacoes) {
    return busca_sequencial_interna(vetor, tamanho, alvo, comparacoes, false);
}

int busca_sequencial_vetor_verbosa(const int vetor[], int tamanho, int alvo, int *comparacoes) {
    return busca_sequencial_interna(vetor, tamanho, alvo, comparacoes, true);
}

static int busca_binaria_interna(const int vetor[], int tamanho, int alvo, int *comparacoes, bool verboso) {
    int inicio = 0;
    int fim = tamanho - 1;

    if (comparacoes != NULL) *comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (comparacoes != NULL) (*comparacoes)++;

        if (verboso) {
            printf("inicio = %d, fim = %d, meio = %d\n", inicio, fim, meio);
            printf("Comparando posicao %d (valor %d) com %d...\n", meio, vetor[meio], alvo);
        }

        if (vetor[meio] == alvo) {
            if (verboso) printf("Encontrado na posicao %d.\n", meio);
            return meio;
        }

        if (vetor[meio] < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (verboso) printf("Nao encontrado.\n");

    return -1;
}

int busca_binaria_vetor(const int vetor[], int tamanho, int alvo, int *comparacoes) {
    return busca_binaria_interna(vetor, tamanho, alvo, comparacoes, false);
}

int busca_binaria_vetor_verbosa(const int vetor[], int tamanho, int alvo, int *comparacoes) {
    return busca_binaria_interna(vetor, tamanho, alvo, comparacoes, true);
}
