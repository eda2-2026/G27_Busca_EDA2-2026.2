#include <assert.h>
#include <stdio.h>
#include "domain.h"
#include "decision.h"

static void testar_buscar_decisao(void) {
    NoDecisao *lista = NULL;

    adicionar_decisao(&lista, (Decisao){1, "Primeira", 1});
    adicionar_decisao(&lista, (Decisao){2, "Segunda", 2});
    adicionar_decisao(&lista, (Decisao){3, "Terceira", 3});

    assert(buscar_decisao(lista, 1) != NULL);
    assert(buscar_decisao(lista, 2) != NULL);
    assert(buscar_decisao(lista, 3) != NULL);
    assert(buscar_decisao(lista, 99) == NULL);

    liberar_decisoes(lista);

    printf("OK: buscar_decisao (primeiro, meio, ultimo, nao encontrado)\n");
}

static void testar_buscar_decisao_instrumentada(void) {
    NoDecisao *lista = NULL;

    adicionar_decisao(&lista, (Decisao){10, "Primeira", 1});
    adicionar_decisao(&lista, (Decisao){20, "Segunda", 2});
    adicionar_decisao(&lista, (Decisao){30, "Terceira", 3});

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

int main(void) {
    testar_buscar_decisao();
    testar_buscar_decisao_instrumentada();

    printf("\nTodos os testes passaram.\n");
    return 0;
}
