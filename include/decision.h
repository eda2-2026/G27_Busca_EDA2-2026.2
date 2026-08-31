#ifndef DECISION_H
#define DECISION_H

#include "domain.h"

NoDecisao *buscar_decisao(NoDecisao *inicio, int id);

NoDecisao *buscar_decisao_instrumentada(NoDecisao *inicio, int id, int *comparacoes);

void adicionar_decisao(NoDecisao **inicio, Decisao decisao);

void liberar_decisoes(NoDecisao *inicio);

#endif