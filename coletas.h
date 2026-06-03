#ifndef COLETAS_H
#define COLETAS_H

typedef struct {
    int dia;
    int mes;
    int ano;
    float quantidade;
} Coleta;

void importarLote();
void excluirLote();
void relatorioGeral();
void relatorioMensal();

#endif