#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct Jogador {
    int id;
    char nome[50];
} Jogador;

typedef struct Decisao {
    int id;
    char descricao[255];
    int impacto;
    int proximo_evento;
} Decisao;

typedef struct NoDecisao {
    Decisao decisao;
    struct NoDecisao *proximo;
} NoDecisao;

typedef struct Evento {
    int id;
    char lore[500];
    NoDecisao *decisoes;
} Evento;

typedef struct Jogo {
    Jogador jogador;
    Evento *evento_atual;
} Jogo;

#endif