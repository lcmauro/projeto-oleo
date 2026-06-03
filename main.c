#include <stdio.h>
#include "coletas.h" //arquivo de cabeçalho contendo biblioteca de tipos

int main()
{

    int opcao; // variavel do menu

    do
    {
        printf("\n===== SISTEMA DE RECICLAGEM DE OLEO =====\n");
        printf("1 - Importar lote\n");
        printf("2 - Excluir lote\n");
        printf("3 - Gerar relatorio geral\n");
        printf("4 - Gerar relatorio mensal\n");
        printf("5 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
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
            printf("Saindo do programa...");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}