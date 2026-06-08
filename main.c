#include <stdio.h>
#include "coletas.h"
#include "pss.h"

int main()
{
    int opcao;

    do
    {
        printf("\n===== SISTEMA DE RECICLAGEM DE OLEO =====\n");
        printf("1 - Importar lote\n");
        printf("2 - Excluir lote\n");
        printf("3 - Relatorio geral\n");
        printf("4 - Relatorio mensal\n");
        printf("5 - Sair\n");
        printf("Opcao: ");

        opcao = input_d("Opcao: ");

        switch(opcao)
        {
            case 1:
                importarLote();
                break;

            case 2:
                excluirLote();
                break;

            case 3:
                relatorioGeral();
                break;

            case 4:
                relatorioMensal();
                break;

            case 5:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 5);

    return 0;
}