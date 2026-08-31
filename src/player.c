#include <stdio.h>
#include <stdlib.h>
#include "player.h"

Jogador cadastrar_jogador() {
    printf("\nDigite seu Nickname:\n");
    printf("\n> ");
    Jogador jogador = {0};
    scanf("%49s", jogador.nome);
    system("clear");
    return jogador;
}

void atualiza_score(Jogador jogador) {
    jogador.score += 1;
}

int consultar_score(Jogador jogador) {
    return jogador.score;
}

int player() {

    return 0;
}