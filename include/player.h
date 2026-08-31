#include <stdio.h>
#include "domain.h"

void atualiza_score(Jogador jogador) {
    jogador.score += 1;
    return;
}

int consultar_score(Jogador jogador) {
    return jogador.score;
}