#include <stdio.h>
#include <string.h>
#include "coletas.h"
#include "pss.h"

void importarLote()
{
    FILE *txt;
    FILE *bin;

    Coleta c;

    char nomeArquivo[50];

    input_s(
        "Digite o nome do arquivo: ",
        nomeArquivo,
        sizeof(nomeArquivo));

    txt = fopen(nomeArquivo, "r");

    if (txt == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    bin = fopen("dados.bin", "ab");

    if (bin == NULL)
    {
        printf("Erro ao abrir dados.bin!\n");
        fclose(txt);
        return;
    }

    int d, m, a;

    if (sscanf(nomeArquivo,
               "%d_%d_%d.txt",
               &d,
               &m,
               &a) != 3)
    {
        printf("Nome do arquivo invalido!\n");
        fclose(txt);
        fclose(bin);
        return;
    }

    sprintf(c.arquivo,
            "%02d/%02d/%04d",
            d,
            m,
            a);

    while (fscanf(txt,
                  "%d %d %d %f",
                  &c.dia,
                  &c.mes,
                  &c.ano,
                  &c.quantidade) == 4)
    {
        fwrite(&c,
               sizeof(Coleta),
               1,
               bin);
    }

    fclose(txt);
    fclose(bin);

    printf("\nLote %s importado com sucesso!\n", c.arquivo);
}

void excluirLote()
{
    FILE *bin;
    FILE *temp;
    FILE *backup;

    Coleta c;

    char lote[11];

    int removidos = 0;

    input_s(
        "Digite a data do lote (dd/mm/aaaa): ",
        lote,
        sizeof(lote)
    );

    /* abre o arquivo principal */
    bin = fopen("dados.bin", "rb");

    if(bin == NULL)
    {
        printf("Arquivo dados.bin nao encontrado.\n");
        return;
    }

    /* cria o backup */
    backup = fopen("backup.bin", "wb");

    if(backup == NULL)
    {
        printf("Erro ao criar backup.\n");
        fclose(bin);
        return;
    }

    /* copia todo o conteudo para o backup */
    while(fread(&c, sizeof(Coleta), 1, bin) == 1)
    {
        fwrite(&c, sizeof(Coleta), 1, backup);
    }

    fclose(backup);
    fclose(bin);

    printf("Backup criado com sucesso!\n");

    /* reabre o arquivo original */
    bin = fopen("dados.bin", "rb");

    if(bin == NULL)
    {
        printf("Erro ao reabrir dados.bin.\n");
        return;
    }

    /* cria arquivo temporario */
    temp = fopen("temp.bin", "wb");

    if(temp == NULL)
    {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(bin);
        return;
    }

    /* copia apenas os registros que nao pertencem ao lote */
    while(fread(&c, sizeof(Coleta), 1, bin) == 1)
    {
        if(strcmp(c.arquivo, lote) == 0)
        {
            removidos++;
        }
        else
        {
            fwrite(&c, sizeof(Coleta), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    remove("dados.bin");
    rename("temp.bin", "dados.bin");

    printf("\nLote removido com sucesso!\n");
    printf("Quantidade de registros eliminados: %d\n", removidos);
}

void relatorioGeral()
{
    FILE *bin;
    FILE *csv;

    Coleta c;

    bin = fopen("dados.bin", "rb");

    if (bin == NULL)
    {
        printf("Nenhum dado encontrado.\n");
        return;
    }

    csv = fopen("listagem.csv", "w");

    if (csv == NULL)
    {
        printf("Erro ao criar CSV.\n");
        fclose(bin);
        return;
    }

    fprintf(csv,
            "dia,mes,ano,litros,arquivo\n");

    while (fread(&c,
                 sizeof(Coleta),
                 1,
                 bin) == 1)
    {
        fprintf(csv,
                "%d,%d,%d,%.2f,%s\n",
                c.dia,
                c.mes,
                c.ano,
                c.quantidade,
                c.arquivo);
    }

    fclose(bin);
    fclose(csv);

    printf("\nRelatorio geral gerado com sucesso!\n");
}

void relatorioMensal()
{
    FILE *bin;
    FILE *csv;

    Coleta c;

    float total[12] = {0};

    bin = fopen("dados.bin", "rb");

    if (bin == NULL)
    {
        printf("Nenhum dado encontrado.\n");
        return;
    }

    while (fread(&c,
                 sizeof(Coleta),
                 1,
                 bin) == 1)
    {
        total[c.mes - 1] += c.quantidade;
    }

    fclose(bin);

    csv = fopen("mensal.csv", "w");

    if (csv == NULL)
    {
        printf("Erro ao criar CSV.\n");
        return;
    }

    fprintf(csv,
            "mes,total\n");

    for (int i = 0; i < 12; i++)
    {
        fprintf(csv,
                "%d,%.2f\n",
                i + 1,
                total[i]);
    }

    fclose(csv);

    printf("\nRelatorio mensal gerado com sucesso!\n");
}