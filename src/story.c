#include <stdio.h>
#include "story.h"
#include "decision.h"

void inicializar_historia(Evento eventos[TOTAL_EVENTOS]) {
    eventos[0].id = 1;
    eventos[0].decisoes = NULL;
    snprintf(eventos[0].lore, sizeof(eventos[0].lore),
        "Voce encontra uma carteira caida no corredor da faculdade.");
    adicionar_decisao(&eventos[0].decisoes, (Decisao){1, "Procurar o dono da carteira", 3, 2});
    adicionar_decisao(&eventos[0].decisoes, (Decisao){2, "Guardar o dinheiro para voce", -3, 3});
    adicionar_decisao(&eventos[0].decisoes, (Decisao){3, "Entregar na recepcao sem procurar o dono", 1, 2});

    eventos[1].id = 2;
    eventos[1].decisoes = NULL;
    snprintf(eventos[1].lore, sizeof(eventos[1].lore),
        "Enquanto procura o dono, voce percebe um colega sendo acusado\n"
        "injustamente de ter pego a carteira.");
    adicionar_decisao(&eventos[1].decisoes, (Decisao){1, "Assumir que foi voce quem a encontrou", 3, 4});
    adicionar_decisao(&eventos[1].decisoes, (Decisao){2, "Ficar em silencio e deixar o mal-entendido", -2, 4});
    adicionar_decisao(&eventos[1].decisoes, (Decisao){3, "Aproveitar a confusao para culpar mais o colega", -4, 5});

    eventos[2].id = 3;
    eventos[2].decisoes = NULL;
    snprintf(eventos[2].lore, sizeof(eventos[2].lore),
        "Com o dinheiro guardado, a culpa comeca a pesar nos dias seguintes.");
    adicionar_decisao(&eventos[2].decisoes, (Decisao){1, "Confessar e devolver o dinheiro", 2, 4});
    adicionar_decisao(&eventos[2].decisoes, (Decisao){2, "Gastar o dinheiro rapido, antes de se arrepender", -3, 5});
    adicionar_decisao(&eventos[2].decisoes, (Decisao){3, "Doar o valor de forma anonima", 1, 4});

    eventos[3].id = 4;
    eventos[3].decisoes = NULL;
    snprintf(eventos[3].lore, sizeof(eventos[3].lore),
        "Semanas depois, as pessoas comecam a te procurar por causa das\n"
        "suas atitudes recentes.");
    adicionar_decisao(&eventos[3].decisoes, (Decisao){1, "Ajudar um novo colega a se adaptar", 2, 6});
    adicionar_decisao(&eventos[3].decisoes, (Decisao){2, "Focar apenas nos proprios estudos", 0, 6});
    adicionar_decisao(&eventos[3].decisoes, (Decisao){3, "Aceitar liderar um projeto social", 3, 6});

    eventos[4].id = 5;
    eventos[4].decisoes = NULL;
    snprintf(eventos[4].lore, sizeof(eventos[4].lore),
        "As pessoas ao seu redor comecam a te tratar com desconfianca.");
    adicionar_decisao(&eventos[4].decisoes, (Decisao){1, "Tentar reconquistar a confianca das pessoas", 1, 6});
    adicionar_decisao(&eventos[4].decisoes, (Decisao){2, "Isolar-se e evitar o problema", -2, 6});
    adicionar_decisao(&eventos[4].decisoes, (Decisao){3, "Culpar os outros pela sua propria reputacao", -3, 6});

    eventos[5].id = 6;
    eventos[5].decisoes = NULL;
    snprintf(eventos[5].lore, sizeof(eventos[5].lore),
        "Chegou o dia da formatura. O efeito borboleta de cada pequena\n"
        "escolha te trouxe ate aqui.");
    adicionar_decisao(&eventos[5].decisoes, (Decisao){1, "Agradecer publicamente quem te ajudou", 2, EVENTO_FIM});
    adicionar_decisao(&eventos[5].decisoes, (Decisao){2, "Comemorar sozinho, sem se importar com os outros", -1, EVENTO_FIM});
    adicionar_decisao(&eventos[5].decisoes, (Decisao){3, "Refletir sobre a jornada e planejar o futuro", 1, EVENTO_FIM});
}

const char *obter_final(int categoria) {
    switch (categoria) {
        case 0:
            return
                "FINAL POSITIVO\n"
                "Suas escolhas generosas construiram uma reputacao admirada.\n"
                "Cada pequena atitude gerou um grande efeito borboleta ao seu redor.";
        case 2:
            return
                "FINAL NEGATIVO\n"
                "As escolhas dificeis cobraram seu preco. O efeito borboleta\n"
                "das suas atitudes trouxe consequencias duras.";
        default:
            return
                "FINAL NEUTRO\n"
                "Sua jornada teve acertos e erros equilibrados. O efeito das\n"
                "suas escolhas ainda esta em aberto.";
    }
}
