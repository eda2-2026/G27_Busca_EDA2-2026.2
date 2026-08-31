#include <stdio.h>
#include "player.h"

Jogador cadastrar_jogador(void) {
    Jogador jogador = {0};

    jogador.id = 1;
    jogador.score = 0;

    printf("Digite seu nickname: ");
    scanf("%49s", jogador.nome);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    return jogador;
}

void atualiza_score(Jogador *jogador, int pontos) {
    if (jogador == NULL) return;

    jogador->score += pontos;
}

int consultar_score(const Jogador *jogador) {
    if (jogador == NULL) return 0;

    return jogador->score;
}
