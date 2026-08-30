#include <stdio.h>

void iniciar_jogo() {
    printf("\n\njogo iniciado!\n");
};

void desenha_menu() {
    printf("\n\n================================\n");
    printf("\tEfeito Borboleta\n");
    printf("================================\n");

    printf("\n\nBem Vindo ao Jogo!\n");

    printf("1 - Iniciar\n");
    printf("0 - Sair\n");
    int escolha = 0;
    scanf("%d", &escolha);
    if(escolha == 0) return;
    if(escolha == 1) {
        iniciar_jogo();
        return;
    }
};

int main() {
    desenha_menu();
    return 0;
};