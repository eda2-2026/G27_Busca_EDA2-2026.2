#include <stdio.h>
#include <stdlib.h>

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
    scanf("%d", &escolha);
    if(escolha == 1) printf("\nVocê entrou na sala\n");
    if(escolha == 2) printf("\nVocê foi embora\n");
}

void configurar_jogo() {
    system("clear");
    desenha_logo();
    char nome_jogador[100];
    printf("\nDigite seu Nickname:\n");
    scanf("%s", nome_jogador);
    system("clear");
    iniciar_jogo(nome_jogador);
};

void desenha_menu() {
    desenha_logo();

    printf("\n\nBem Vindo ao Jogo!\n");

    printf("1 - Iniciar\n");
    printf("0 - Sair\n");
    int escolha = 0;
    scanf("%d", &escolha);
    if(escolha == 0) return;
    if(escolha == 1) {
        configurar_jogo();
        return;
    }
};

int main() {
    desenha_menu();
    return 0;
};