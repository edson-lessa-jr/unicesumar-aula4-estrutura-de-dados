#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ex1_pilhas.h"

/**
    Esta função inicializa uma nova pilha.

    Retorno:
        - Retorna um ponteiro para a nova pilha inicializada.

    Funcionamento:
        - Aloca memória para a estrutura Pilha.
        - Define a capacidade inicial da pilha como TAMANHO_INICIAL.
        - Define o topo da pilha como -1, indicando uma pilha vazia.
        - Aloca memória para armazenar as URLs da pilha.

    Observação:
        - A função assume que TAMANHO_INICIAL está definido.
**/

Pilha *inicializaPilha() {
    // Aloca memória para a estrutura Pilha.
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    // Define a capacidade inicial da pilha como TAMANHO_INICIAL.
    pilha->capacidade = TAMANHO_INICIAL;
    // Define o topo da pilha como -1, indicando uma pilha vazia.
    pilha->top = -1;
    // Aloca memória para armazenar as URLs da pilha.
    pilha->urls = (char **) malloc(pilha->capacidade * sizeof(char *));
    return pilha;
}


/**
    Esta função empilha uma URL na pilha.

    Parâmetros:
        - pilha: Ponteiro para a pilha onde a URL será empilhada.
        - url: String contendo a URL a ser empilhada.

    Funcionamento:
        - Verifica se o topo da pilha está no limite de capacidade.
        - Se estiver no limite, dobra a capacidade da pilha usando realloc.
        - Incrementa o topo da pilha e copia a URL para a posição correspondente.

    Observação:
        - A função assume que a pilha já foi inicializada.
**/

void empilha(Pilha *pilha, const char *url) {
    // Verifica se o topo da pilha está no limite de capacidade.
    if (pilha->top == pilha->capacidade - 1) {
        // Se estiver no limite, dobra a capacidade da pilha usando realloc.
        pilha->capacidade *= 2;
        pilha->urls = (char **) realloc(pilha->urls, pilha->capacidade * sizeof(char *));
    }
    // Incrementa o topo da pilha e copia a URL para a posição correspondente.
    pilha->urls[++pilha->top] = strdup(url);
}

/**
    Esta função desempilha uma URL da pilha.

    Parâmetros:
        - pilha: Ponteiro para a pilha de onde a URL será desempilhada.

    Retorno:
        - Retorna a URL desempilhada.

    Observação:
        - Se a pilha estiver vazia, a função exibe uma mensagem de erro e retorna NULL.
**/

char *desempilha(Pilha *pilha) {
    // Verifica se a pilha está vazia.
    if (pilha->top == -1) {
        // Se a pilha estiver vazia, exibe uma mensagem de erro e retorna NULL.
        printf("Estrutura esta vazia\n");
        return NULL;
    }
    // Retorna a URL desempilhada e decrementa o topo da pilha.
    return pilha->urls[pilha->top--];
}


// Funcao para carregar URLs de um arquivo
/**
    Esta função é responsável por carregar URLs de um arquivo para uma pilha.

    Parâmetros:
        - pilha: Ponteiro para a pilha onde as URLs serão armazenadas.
        - urlAtual: String contendo a URL atual.
        - nomeArquivo: Nome do arquivo contendo as URLs a serem carregadas.

    Funcionamento:
        - Obtém o diretório de trabalho atual e o exibe.
        - Abre o arquivo especificado em modo de leitura.
        - Lê cada linha do arquivo e verifica se é uma URL válida.
        - Caso seja válida, empilha a URL atual na pilha e atualiza a URL atual.
        - Caso contrário, exibe uma mensagem de URL inválida.
        - Fecha o arquivo após a leitura.

    Observação:
        - A função assume que a pilha já foi inicializada e que o tamanho da URL atual é suficiente para armazenar as URLs do arquivo.
**/

void carregarUrlsDoArquivo(Pilha *pilha, const char *urlAtual, const char *nomeArquivo) {
    // Declaração de uma variável para armazenar o diretório de trabalho atual.
    char cwd[1024];

    // Verifica se é possível obter o diretório de trabalho atual e exibe-o.
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretorio de trabalho atual: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }

    // Abre o arquivo especificado em modo de leitura.
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        // Se ocorrer um erro ao abrir o arquivo, exibe uma mensagem de erro.
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    // Declaração de uma variável para armazenar temporariamente cada linha do arquivo.
    char url[TAMANHO_MAX_URL];

    // Lê cada linha do arquivo até o final.
    while (fgets(url, sizeof(url), arquivo) != NULL) {
        // Remove o caractere de nova linha da linha lida.
        url[strcspn(url, "\n")] = '\0';

        // Verifica se a linha lida corresponde a uma URL válida.
        if ((strstr(url, "http://")||strstr(url, "https://")) && (strstr(url, ".com")||strstr(url, ".br")||strstr(url, ".org"))) {
            // Se for uma URL válida, empilha a URL atual na pilha.
            if (strlen(urlAtual) > 0) {
                empilha(pilha, urlAtual);
            }
            // Atualiza a URL atual com a URL lida do arquivo.
            strcpy(urlAtual, url);
            // Exibe a URL atual.
            exibirNavegacaoAtual(urlAtual);
        } else {
            // Se a URL lida não for válida, exibe uma mensagem de URL inválida.
            printf("URL invalida: %s\n",url);
        }
    }

    // Fecha o arquivo após a leitura.
    fclose(arquivo);
}


/**
    Esta função verifica se a pilha está vazia.

    Parâmetros:
        - pilha: ponteiro para a pilha a ser verificada.

    Retorno:
        - Retorna 1 se a pilha estiver vazia, caso contrário, retorna 0.
*/

int vazio(Pilha *pilha) {
    return pilha->top == -1;
}

/**
    Esta função exibe o histórico armazenado na pilha.

    Parâmetros:
        - pilha: ponteiro para a pilha contendo o histórico de URLs.

    Funcionamento:
        - Percorre a pilha do topo até o fundo, imprimindo cada URL na ordem em que foram empilhadas.
*/

void exibirHistorico(Pilha *pilha) {
    printf("\nImprimindo o conteudo da pilha\n");
    for (int i = pilha->top; i >= 0; i--) {
        printf("%dº %s\n", pilha->top - i + 1, pilha->urls[i]);
    }
}

/**
    Esta função exibe a URL atual.

    Parâmetros:
        - atual: string contendo a URL atual.

    Funcionamento:
        - Imprime a mensagem informando qual URL está sendo acessada.
*/

void exibirNavegacaoAtual(char *atual) {
    printf("Voce esta acessando %s\n\n", atual);
}

/**
    Esta função implementa o menu de interação com o usuário para manipulação de uma pilha de URLs.

    Funcionamento:
        - Inicializa a pilha.
        - Dentro de um loop infinito, exibe um menu com opções para o usuário.
        - O usuário pode escolher entre navegar para uma URL, exibir a URL atual, voltar para uma URL anterior,
          exibir o histórico, carregar dados de um arquivo ou sair do programa.
        - Conforme a opção escolhida pelo usuário, as funções correspondentes são chamadas para executar a ação desejada.

    Retorno:
        - Retorna 0 quando o usuário escolhe sair do programa.
*/

int ex1_pilhas() {
    Pilha *pilha = inicializaPilha(); // Inicializa a pilha
    char atual[TAMANHO_MAX_URL] = ""; // Inicializa a string para armazenar a URL atual
    int opcao;
    char url[TAMANHO_MAX_URL];

    while (1) {
        printf("1 - Navegar para uma URL\n"
               "2 - Exibir URL atual\n"
               "3 - Voltar para uma URL\n"
               "4 - Exibir historico\n"
               "5 - Carregar dados\n"
               "0 - Deseja Sair\n");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Informe sua URL\n");
                fgets(url, TAMANHO_MAX_URL, stdin);
                url[strcspn(url, "\n")] = '\0'; // Remove o caractere de nova linha
                if (strstr(url, "http://") && strstr(url, ".com")) {
                    if (strlen(atual) > 0) {
                        empilha(pilha, atual); // Empilha a URL atual antes de navegar para a nova URL
                    }
                    strcpy(atual, url);
                    exibirNavegacaoAtual(atual);
                } else {
                    printf("URL invalida\n");
                }
                break;
            case 2:
                exibirNavegacaoAtual(atual);
                break;
            case 3:
                if (vazio(pilha)) {
                    printf("Estrutura esta vazia\n");
                } else {
                    strcpy(atual, desempilha(pilha)); // Desempilha a URL anterior para voltar a ela
                    exibirNavegacaoAtual(atual);
                }
                break;
            case 4:
                exibirHistorico(pilha); // Exibe o histórico de URLs acessadas
                break;
            case 5:
                carregarUrlsDoArquivo(pilha, atual, "../urls.txt"); // Carrega URLs de um arquivo
                desempilha(pilha); // Remove a URL atual da pilha após carregar os dados
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao Invalida\n");
        }
    }

    return 0;
}
