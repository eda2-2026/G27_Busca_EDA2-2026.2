#ifndef DECISION_H
#define DECISION_H

#include "domain.h"

NoDecisao *buscar_decisao(NoDecisao *inicio, int id);

void adicionar_decisao(NoDecisao **inicio, Decisao decisao);

#endif