#ifndef COLETAS_H
#define COLETAS_H

typedef struct {
    int dia;
    int mes;
    int ano;
    float quantidade;

    char arquivo[11]; // dd/mm/aaaa
} Coleta;

void importarLote();
void excluirLote();
void relatorioGeral();
void relatorioMensal();

#endif