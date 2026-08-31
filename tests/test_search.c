#include <assert.h>
#include <stdio.h>
#include "domain.h"
#include "decision.h"
#include "search.h"

static void testar_buscar_decisao(void) {
    NoDecisao *lista = NULL;

    adicionar_decisao(&lista, (Decisao){1, "Primeira", 1, 0});
    adicionar_decisao(&lista, (Decisao){2, "Segunda", 2, 0});
    adicionar_decisao(&lista, (Decisao){3, "Terceira", 3, 0});

    assert(buscar_decisao(lista, 1) != NULL);
    assert(buscar_decisao(lista, 2) != NULL);
    assert(buscar_decisao(lista, 3) != NULL);
    assert(buscar_decisao(lista, 99) == NULL);

    liberar_decisoes(lista);

    printf("OK: buscar_decisao (primeiro, meio, ultimo, nao encontrado)\n");
}

static void testar_buscar_decisao_instrumentada(void) {
    NoDecisao *lista = NULL;

    adicionar_decisao(&lista, (Decisao){10, "Primeira", 1, 0});
    adicionar_decisao(&lista, (Decisao){20, "Segunda", 2, 0});
    adicionar_decisao(&lista, (Decisao){30, "Terceira", 3, 0});

    int comparacoes = 0;

    assert(buscar_decisao_instrumentada(lista, 10, &comparacoes) != NULL);
    assert(comparacoes == 1);

    assert(buscar_decisao_instrumentada(lista, 30, &comparacoes) != NULL);
    assert(comparacoes == 3);

    assert(buscar_decisao_instrumentada(lista, 99, &comparacoes) == NULL);
    assert(comparacoes == 3);

    assert(buscar_decisao_instrumentada(NULL, 1, &comparacoes) == NULL);
    assert(comparacoes == 0);

    liberar_decisoes(lista);

    printf("OK: buscar_decisao_instrumentada (contagem de comparacoes)\n");
}

static void testar_busca_sequencial_vetor(void) {
    int vetor[] = {2, 4, 6, 8, 10};
    int tamanho = 5;
    int comparacoes;

    assert(busca_sequencial_vetor(vetor, tamanho, 2, &comparacoes) == 0);
    assert(comparacoes == 1);

    assert(busca_sequencial_vetor(vetor, tamanho, 6, &comparacoes) == 2);
    assert(comparacoes == 3);

    assert(busca_sequencial_vetor(vetor, tamanho, 10, &comparacoes) == 4);
    assert(comparacoes == 5);

    assert(busca_sequencial_vetor(vetor, tamanho, 99, &comparacoes) == -1);
    assert(comparacoes == 5);

    printf("OK: busca_sequencial_vetor (primeiro, meio, ultimo, nao encontrado)\n");
}

static void testar_busca_binaria_vetor(void) {
    int vetor[] = {2, 4, 6, 8, 10, 12, 14};
    int tamanho = 7;
    int comparacoes;

    assert(busca_binaria_vetor(vetor, tamanho, 2, &comparacoes) == 0);
    assert(busca_binaria_vetor(vetor, tamanho, 8, &comparacoes) == 3);
    assert(busca_binaria_vetor(vetor, tamanho, 14, &comparacoes) == 6);
    assert(busca_binaria_vetor(vetor, tamanho, 5, &comparacoes) == -1);

    int vetor_unico[] = {7};
    assert(busca_binaria_vetor(vetor_unico, 1, 7, &comparacoes) == 0);
    assert(busca_binaria_vetor(vetor_unico, 1, 1, &comparacoes) == -1);

    assert(busca_binaria_vetor(vetor, 0, 2, &comparacoes) == -1);

    printf("OK: busca_binaria_vetor (primeiro, meio, ultimo, nao encontrado, vetor de 1, vetor vazio)\n");
}

static void testar_buscar_evento_binario(void) {
    Evento eventos[3];

    eventos[0].id = 1;
    eventos[0].decisoes = NULL;
    eventos[1].id = 2;
    eventos[1].decisoes = NULL;
    eventos[2].id = 3;
    eventos[2].decisoes = NULL;

    int comparacoes;

    assert(buscar_evento_binario(eventos, 3, 1, &comparacoes) == &eventos[0]);
    assert(buscar_evento_binario(eventos, 3, 2, &comparacoes) == &eventos[1]);
    assert(buscar_evento_binario(eventos, 3, 3, &comparacoes) == &eventos[2]);
    assert(buscar_evento_binario(eventos, 3, 99, &comparacoes) == NULL);
    assert(buscar_evento_binario(eventos, 0, 1, &comparacoes) == NULL);

    printf("OK: buscar_evento_binario (primeiro, meio, ultimo, nao encontrado, vetor vazio)\n");
}

int main(void) {
    testar_buscar_decisao();
    testar_buscar_decisao_instrumentada();
    testar_busca_sequencial_vetor();
    testar_busca_binaria_vetor();
    testar_buscar_evento_binario();

    printf("\nTodos os testes passaram.\n");
    return 0;
}
