#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <locale.h> // Inclui a biblioteca para manipulação de localidade
#include "navegacao.h" // Inclui o cabeçalho da estrutura de navegação

/**
Este programa demonstra a utilização das estruturas de pilhas e
 filas para navegação em um navegador web simulado.

Bibliotecas:
    -stdio.h: Biblioteca padrão de entrada e saída.
    -locale.h: Biblioteca para manipulação de localidade.

Funções Principais:
-main: Função principal do programa, responsável por exibir
o menu de opções e chamar as funções correspondentes.

Parâmetros:
-Nenhum. return =0 :Indica que o programa foi executado com sucesso.

Observações:
-Este programa utiliza a codificação de caracteres UTF-8
 para suportar caracteres especiais.
*/
int main(void) {
    // Define a codificação de caracteres para UTF-8
    setlocale(LC_ALL, "en_US.UTF-8");

    int opcao;

    printf("Iniciando o programa\n");

    do {
        // Exibindo o ex2_filas de opções

        printf("\nMenu:\n");
        printf("1. Exemplo Pilhas\n");
        printf("2. Exemplo Filas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Verificando a opção escolhida e chamando a função correspondente
        switch (opcao) {
            case 1:
                ex1_pilhas(); // Chama a função de exemplo de pilhas
                break;
            case 2:
                ex2_filas(); // Chama a função de exemplo de filas
                break;
            case 0:
                printf("Saindo do programa. Obrigado!\n"); // Mensagem de saída
                break;
            default:
                printf("Opcao invalida. Por favor, escolha uma opcao valida.\n"); // Mensagem de opção inválida
        }
    } while (opcao != 0); // Loop continua até que a opção de saída (0) seja escolhida

    return 0; // Indica que o programa foi executado com sucesso
}

