#ifndef STORY_H
#define STORY_H

#include "domain.h"

#define TOTAL_EVENTOS 6
#define EVENTO_INICIAL 1
#define EVENTO_FIM 0

void inicializar_historia(Evento eventos[TOTAL_EVENTOS]);

const char *obter_final(int score);

#endif
