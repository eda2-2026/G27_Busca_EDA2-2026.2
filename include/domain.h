#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct Jogador {
    int id;
    char nome[50];
    int score;
} Jogador;

typedef struct Decisao {
    int id;
    char descricao[255];
    char impacto[255];
} Decisao;

typedef struct Evento {
    int id;
    Decisao decisoes;
} Evento;

typedef struct Jogo {
    Jogador jogador;
    Evento evento_atual;
} Jogo;

#endif