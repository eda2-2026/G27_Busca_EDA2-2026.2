#include <stdio.h>
#include <stdlib.h>
#include "domain.h"
#include "player.c"

void desenha_logo() {
    printf("\n\n================================\n");
    printf("\tEfeito Borboleta\n");
    printf("================================\n");
}

void iniciar_jogo(char* jogador) {
    desenha_logo();
    printf("\nVocê está diante de uma porta.\n");

    printf("\n1 - Abrir a porta\n");
    printf("2 - Ir embora\n");
    int escolha = 0;
    printf("\n> ");
    scanf("%d", &escolha);
    if (escolha == 1) printf("\nVocê entrou na sala\n");
    if (escolha == 2) printf("\nVocê foi embora\n");
}

void configurar_jogo() {
    system("clear");
    desenha_logo();
    Jogador jogador = cadastrar_jogador();
    iniciar_jogo(jogador.nome);
}

void desenha_menu() {
    desenha_logo();

    printf("\n\nBem Vindo ao Jogo!\n");

    printf("1 - Iniciar\n");
    printf("0 - Sair\n");
    int escolha = 0;
    printf("\n> ");
    scanf("%d", &escolha);
    if (escolha == 0) return;
    if (escolha == 1) {
        configurar_jogo();
        return;
    }
}

int main() {
    Decisao decisao;
    desenha_menu();
    return 0;
}