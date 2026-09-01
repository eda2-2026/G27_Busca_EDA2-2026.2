#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "domain.h"
#include "player.h"
#include "decision.h"
#include "story.h"
#include "search.h"
#include "category.h"

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
    printf("----------------------------------------\n");
}

static const char *nome_categoria(int idx) {
    switch (idx) {
        case 0: return "Altruista";
        case 2: return "Egoista";
        default: return "Neutro";
    }
}

static void executar_partida(bool modo_debug) {
    limpar_tela();
    desenha_logo();

    Jogo jogo;
    jogo.jogador = cadastrar_jogador();

    Evento eventos[TOTAL_EVENTOS];
    inicializar_historia(eventos);

    HistoricoEscolhas historico;
    inicializar_historico(&historico);

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

        registrar_escolha(&historico, decisao->decisao, id_evento_atual);

        int cat = categorizar(decisao->decisao.impacto);
        printf("\nVoce escolheu: %s\n", decisao->decisao.descricao);
        printf("Categoria: %s\n", nome_categoria(cat));

        id_evento_atual = decisao->decisao.proximo_evento;

        if (id_evento_atual != EVENTO_FIM) {
            ler_inteiro("\nDigite 1 e pressione ENTER para continuar > ");
        }
    }

    int dominante = obter_categoria_dominante(&historico);

    limpar_tela();
    desenha_logo();

    printf("\n================ FIM DE JOGO ================\n");
    printf("\nJogador: %s\n", jogo.jogador.nome);
    printf("Categoria dominante: %s (%d de 6 escolhas)\n\n",
        nome_categoria(dominante), historico.contagem[dominante]);

    printf("%s\n\n", obter_final(dominante));

    printf("Suas escolhas que definiram este final:\n\n");
    NoEscolha *atual = historico.buckets[dominante];
    while (atual != NULL) {
        printf("  - \"%s\" (evento %d, impacto %+d)\n",
            atual->decisao.descricao, atual->evento_id, atual->decisao.impacto);
        atual = atual->proximo;
    }
    printf("\n");

    liberar_historico(&historico);

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        liberar_decisoes(eventos[i].decisoes);
    }

    ler_inteiro("Digite 1 e pressione ENTER para voltar ao menu > ");
}

static void demonstracao_buscas(void) {
    limpar_tela();
    desenha_logo();

    Evento eventos[TOTAL_EVENTOS];
    inicializar_historia(eventos);

    int ids[TOTAL_EVENTOS];
    for (int i = 0; i < TOTAL_EVENTOS; i++) ids[i] = eventos[i].id;

    printf("\n====================================\n");
    printf("       DEMONSTRACAO DE BUSCAS\n");
    printf("====================================\n");
    printf("\nEventos disponiveis (ordenados por ID): ");
    for (int i = 0; i < TOTAL_EVENTOS; i++) printf("%d ", ids[i]);
    printf("\n");

    int alvo = ler_inteiro("\nDigite o ID do evento a procurar > ");

    printf("\n[BUSCA SEQUENCIAL]\n");
    int comparacoes_seq = 0;
    int indice_seq = busca_sequencial_vetor_verbosa(ids, TOTAL_EVENTOS, alvo, &comparacoes_seq);
    printf("Comparacoes realizadas: %d\n", comparacoes_seq);
    printf("Complexidade: O(n)\n");

    printf("\n[BUSCA BINARIA]\n");
    int comparacoes_bin = 0;
    int indice_bin = busca_binaria_vetor_verbosa(ids, TOTAL_EVENTOS, alvo, &comparacoes_bin);
    printf("Comparacoes realizadas: %d\n", comparacoes_bin);
    printf("Complexidade: O(log n)\n");

    printf("\n------------------------------------\n");
    printf("Elemento procurado: %d\n", alvo);
    printf("Busca Sequencial -> comparacoes: %d | %s\n", comparacoes_seq,
        indice_seq >= 0 ? "encontrado" : "nao encontrado");
    printf("Busca Binaria    -> comparacoes: %d | %s\n", comparacoes_bin,
        indice_bin >= 0 ? "encontrado" : "nao encontrado");
    printf("------------------------------------\n");

    for (int i = 0; i < TOTAL_EVENTOS; i++) liberar_decisoes(eventos[i].decisoes);

    ler_inteiro("\nDigite 1 e pressione ENTER para voltar ao menu > ");
}

void menu_principal(void) {
    int opcao;

    do {
        limpar_tela();
        desenha_logo();

        printf("\nBem-vindo ao Efeito Borboleta!\n\n");
        printf("[1] Iniciar jogo\n");
        printf("[2] Iniciar jogo (modo debug - mostra as buscas)\n");
        printf("[3] Demonstracao de algoritmos de busca\n");
        printf("[0] Sair\n");

        opcao = ler_inteiro("\nEscolha > ");

        switch (opcao) {
            case 1: executar_partida(false); break;
            case 2: executar_partida(true); break;
            case 3: demonstracao_buscas(); break;
            case 0: printf("\nAte a proxima!\n\n"); break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcao != 0);
}
