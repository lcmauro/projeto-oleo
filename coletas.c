#include <stdio.h>
#include "coletas.h"

void importarLote()
{
    char nomeArquivo[100];
    FILE *txt;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    printf("Arquivo escolhido: %s\n", nomeArquivo);

    txt = fopen(nomeArquivo, "r");
    if (txt == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    FILE *bin;

    bin = fopen("coletas.bin", "ab");

    if (bin == NULL)
    {
        printf("Erro ao criar binario!\n");
        fclose(txt); // garaantir que o arquivo txt seja fechado
        return;
    }

    Coleta coleta;
    char linha[100];

    while (fgets(linha, sizeof(linha), txt) != NULL)
    {
        if (sscanf(linha, "%d/%d/%d %f", &coleta.dia, &coleta.mes, &coleta.ano, &coleta.quantidade) == 4)
        {
            fwrite(&coleta, sizeof(Coleta), 1, bin);
        }
        else
        {
            printf("Linha invalida: %s", linha);
        }
    }

    fclose(txt);
    fclose(bin);

    printf("Importacao concluida!\n");
}

void excluirLote()
{
    // to do
    printf("Funcao excluir lote\n");
}

void relatorioGeral()
{
    // to do
    printf("Funcao relatorio geral\n");
}

void relatorioMensal()
{
    // to do
    printf("Funcao relatorio mensal\n");
}