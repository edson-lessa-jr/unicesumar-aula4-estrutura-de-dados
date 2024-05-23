#include <stdio.h>
#include <locale.h>

int ex1_pilhas();
int ex2_filas();

int main(void) {
    // Define a codificação de caracteres para UTF-8
    setlocale(LC_ALL, "en_US.UTF-8");

    int opcao;

    printf("Iniciando o programa\n");

    do {
        // Exibindo o menu de opções
        printf("\nMenu:\n");
        printf("1. Exemplo Pilhas\n");
        printf("2. Exemplo Filas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Verificando a opção escolhida e chamando a função correspondente
        switch (opcao) {
            case 1:
                ex1_pilhas();
            break;
            case 2:
                 ex2_filas();
            break;
            case 0:
                printf("Saindo do programa. Obrigado!\n");
            break;
            default:
                printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
        }
    } while (opcao != 0);

    return 0;
}