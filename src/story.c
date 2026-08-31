#include "story.h"
#include "decision.h"

void inicializar_historia(Evento *eventos) {
    eventos[0].id = 1;
    eventos[0].lore[0] = '\0';

    adicionar_decisao(&eventos[0].decisoes, (Decisao){1, "Abrir a porta", 2, 0});
    adicionar_decisao(&eventos[0].decisoes, (Decisao){2, "Ir embora", -1, 0});
    adicionar_decisao(&eventos[0].decisoes, (Decisao){3, "Bater na porta", 1, 0});
}