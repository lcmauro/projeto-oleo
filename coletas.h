#ifndef COLETAS_H
#define COLETAS_H

typedef struct {
    int dia;
    int mes;
    int ano;
    float quantidade;
} Coleta;

typedef struct {
    int mes;
    int ano;
    float total;
} TotalMensal;

void importarLote();
void excluirLote();
void relatorioGeral();
void relatorioMensal();

#endif