#include <stdio.h>
#include "player.h"

Jogador cadastrar_jogador(void) {
    Jogador jogador = {0};

    jogador.id = 1;

    printf("Digite seu nickname: ");
    scanf("%49s", jogador.nome);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    return jogador;
}
