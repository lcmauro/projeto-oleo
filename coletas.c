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
    FILE *bin;
    FILE *csv;

    bin = fopen("coletas.bin", "rb");

    if (bin == NULL)
    {
        printf("Arquivo binario nao encontrado!\n");
        return;
    }

    csv = fopen("relatorio_geral.csv", "w");

    if (csv == NULL)
    {
        printf("Erro ao criar CSV!\n");
        fclose(bin);
        return;
    }

    Coleta coleta;

    fprintf(csv, "Dia;Mes;Ano;Quantidade\n");

    while (fread(&coleta,
                 sizeof(Coleta),
                 1,
                 bin) == 1)
    {
        fprintf(csv,
                "%d;%d;%d;%.2f\n",
                coleta.dia,
                coleta.mes,
                coleta.ano,
                coleta.quantidade);
    }

    fclose(bin);
    fclose(csv);

    printf("Relatorio geral gerado com sucesso!\n");
}

void relatorioMensal()
{
    FILE *bin;
    FILE *csv;

    bin = fopen("coletas.bin", "rb");

    if(bin == NULL)
    {
        printf("Arquivo binario nao encontrado!\n");
        return;
    }

    csv = fopen("relatorio_mensal.csv", "w");

    if(csv == NULL)
    {
        printf("Erro ao criar CSV!\n");
        fclose(bin);
        return;
    }

    TotalMensal totais[100];
    int qtdMeses = 0;

    Coleta coleta;

    while(fread(&coleta, sizeof(Coleta), 1, bin) == 1)
    {
        int encontrou = 0;

        for(int i = 0; i < qtdMeses; i++)
        {
            if(totais[i].mes == coleta.mes &&
               totais[i].ano == coleta.ano)
            {
                totais[i].total += coleta.quantidade;
                encontrou = 1;
                break;
            }
        }

        if(!encontrou)
        {
            totais[qtdMeses].mes = coleta.mes;
            totais[qtdMeses].ano = coleta.ano;
            totais[qtdMeses].total = coleta.quantidade;
            qtdMeses++;
        }
    }

    fprintf(csv, "Mes;Ano;Total\n");

    for(int i = 0; i < qtdMeses; i++)
    {
        fprintf(csv,
                "%d;%d;%.2f\n",
                totais[i].mes,
                totais[i].ano,
                totais[i].total);
    }

    fclose(bin);
    fclose(csv);

    printf("Relatorio mensal gerado com sucesso!\n");
}