#ifndef SEARCH_H
#define SEARCH_H

#include "domain.h"

Evento *buscar_evento_binario(Evento eventos[], int tamanho, int id, int *comparacoes);

int busca_sequencial_vetor(const int vetor[], int tamanho, int alvo, int *comparacoes);
int busca_sequencial_vetor_verbosa(const int vetor[], int tamanho, int alvo, int *comparacoes);

int busca_binaria_vetor(const int vetor[], int tamanho, int alvo, int *comparacoes);
int busca_binaria_vetor_verbosa(const int vetor[], int tamanho, int alvo, int *comparacoes);

#endif
