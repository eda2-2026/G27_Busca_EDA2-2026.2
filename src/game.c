#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "domain.h"
#include "player.h"
#include "decision.h"
#include "story.h"
#include "search.h"

void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static int ler_inteiro(const char *prompt) {
    int valor;
    int resultado;

    while (1) {
        printf("%s", prompt);
        resultado = scanf("%d", &valor);

        if (resultado == EOF) {
            printf("\nEntrada encerrada. Fechando o jogo.\n");
            exit(EXIT_SUCCESS);
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if (resultado == 1) return valor;

        printf("\nEntrada invalida. Digite um numero.\n");
    }
}

void desenha_logo(void) {
    printf("\n+--------------------------------------+\n");
    printf("|          EFEITO BORBOLETA             |\n");
    printf("+--------------------------------------+\n");
}

static void desenha_cabecalho_evento(const Jogo *jogo) {
    desenha_logo();
    printf("\nJogador: %s\n", jogo->jogador.nome);
    printf("Score: %d\n", consultar_score(&jogo->jogador));
    printf("----------------------------------------\n");
}

static void executar_partida(bool modo_debug) {
    limpar_tela();
    desenha_logo();

    Jogo jogo;
    jogo.jogador = cadastrar_jogador();

    Evento eventos[TOTAL_EVENTOS];
    inicializar_historia(eventos);

    int id_evento_atual = EVENTO_INICIAL;

    while (id_evento_atual != EVENTO_FIM) {
        int comparacoes_binaria = 0;
        Evento *evento = buscar_evento_binario(eventos, TOTAL_EVENTOS, id_evento_atual, &comparacoes_binaria);

        if (evento == NULL) break;

        jogo.evento_atual = evento;

        limpar_tela();
        desenha_cabecalho_evento(&jogo);

        printf("\n%s\n\n", evento->lore);

        if (modo_debug) {
            printf("[BUSCA BINARIA] Evento %d localizado no vetor (comparacoes: %d)\n\n",
                id_evento_atual, comparacoes_binaria);
        }

        printf("O que voce faz?\n\n");

        NoDecisao *atual = evento->decisoes;
        while (atual != NULL) {
            printf("[%d] %-45s (%+d)\n", atual->decisao.id, atual->decisao.descricao, atual->decisao.impacto);
            atual = atual->proximo;
        }

        int escolha = ler_inteiro("\nEscolha > ");

        int comparacoes_sequencial = 0;
        NoDecisao *decisao = buscar_decisao_instrumentada(evento->decisoes, escolha, &comparacoes_sequencial);

        while (decisao == NULL) {
            printf("\nOpcao invalida. Digite novamente.\n");
            escolha = ler_inteiro("Escolha > ");
            decisao = buscar_decisao_instrumentada(evento->decisoes, escolha, &comparacoes_sequencial);
        }

        if (modo_debug) {
            printf("\n[BUSCA SEQUENCIAL]\n");
            printf("Procurando decisao de ID %d...\n", escolha);
            printf("Comparacoes realizadas: %d\n", comparacoes_sequencial);
            printf("Decisao encontrada.\n");
        }

        atualiza_score(&jogo.jogador, decisao->decisao.impacto);

        printf("\nVoce escolheu: %s\n", decisao->decisao.descricao);
        printf("Score atual: %d\n", consultar_score(&jogo.jogador));

        id_evento_atual = decisao->decisao.proximo_evento;

        if (id_evento_atual != EVENTO_FIM) {
            ler_inteiro("\nDigite 1 e pressione ENTER para continuar > ");
        }
    }

    limpar_tela();
    desenha_logo();

    printf("\n================ FIM DE JOGO ================\n");
    printf("\nJogador: %s\n", jogo.jogador.nome);
    printf("Score final: %d\n\n", consultar_score(&jogo.jogador));
    printf("%s\n\n", obter_final(consultar_score(&jogo.jogador)));

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        liberar_decisoes(eventos[i].decisoes);
    }

    ler_inteiro("Digite 1 e pressione ENTER para voltar ao menu > ");
}

void menu_principal(void) {
    int opcao;

    do {
        limpar_tela();
        desenha_logo();

        printf("\nBem-vindo ao Efeito Borboleta!\n\n");
        printf("[1] Iniciar jogo\n");
        printf("[2] Iniciar jogo (modo debug - mostra as buscas)\n");
        printf("[0] Sair\n");

        opcao = ler_inteiro("\nEscolha > ");

        switch (opcao) {
            case 1: executar_partida(false); break;
            case 2: executar_partida(true); break;
            case 0: printf("\nAte a proxima!\n\n"); break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcao != 0);
}
