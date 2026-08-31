#ifndef PLAYER_H
#define PLAYER_H

#include "domain.h"

Jogador cadastrar_jogador(void);
void atualiza_score(Jogador *jogador, int pontos);
int consultar_score(const Jogador *jogador);

#endif