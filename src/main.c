#include <stdio.h>
#include <stdlib.h>
#include "domain.h"
#include "player.h"
#include "decision.h"
#include "story.h"

void desenha_logo() {
    printf("\n\n================================\n");
    printf("\tEfeito Borboleta\n");
    printf("================================\n");
}

void iniciar_jogo(char *nome) {

    Evento eventos[1] = {0};

    inicializar_historia(eventos);

    Jogo jogo;

    jogo.jogador.id = 1;
    jogo.jogador.score = 0;

    snprintf(jogo.jogador.nome, sizeof(jogo.jogador.nome), "%s", nome);

    jogo.evento_atual = &eventos[0];

    desenha_logo();

    printf("\n%s\n", jogo.evento_atual->lore);
    printf("\nVocê está diante de uma porta.\n");

    NoDecisao *atual = jogo.evento_atual->decisoes;

    while (atual != NULL) {
        printf("\n%d - %s", atual->decisao.id, atual->decisao.descricao);

        atual = atual->proximo;
    }

    int escolha;

    printf("\n\n> ");
    scanf("%d", &escolha);

    NoDecisao *decisao = buscar_decisao(jogo.evento_atual->decisoes, escolha);

    if (decisao == NULL) {
        printf("\nDecisao invalida.\n");
        return;
    }

    jogo.jogador.score += decisao->decisao.impacto;

    printf("\nVoce escolheu: %s\n", decisao->decisao.descricao);

    printf("Score atual: %d\n",jogo.jogador.score);

    liberar_decisoes(jogo.evento_atual->decisoes);
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

    printf("\n1 - Iniciar\n");
    printf("0 - Sair\n");
    int escolha = 0;
    printf("\n> ");
    scanf("%d", &escolha);

    if (escolha == 1) configurar_jogo();
}

int main() {
    desenha_menu();
    return 0;
}