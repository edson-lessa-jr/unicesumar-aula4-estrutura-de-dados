#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex2_filas.h"

#define MAX_URL_LENGTH 256

/**
    Esta função exibe a URL atual sendo acessada pelo usuário.

    Parâmetros:
        - atual: Ponteiro para a string contendo a URL atual.

    Retorno:
        A função não possui retorno.
*/
void exibirNavegacaoAtualFila(char *atual) {
    printf("Voce esta acessando %s\n\n", atual);
}

/**
    Esta função inicializa uma fila, configurando seus ponteiros de frente e trás como NULL e
    definindo o tamanho da fila como 0.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila a ser inicializada.

    Retorno:
        A função não possui retorno.
*/
void initFila(Fila *fila) {
    fila->front = NULL;
    fila->rear = NULL;
    fila->size = 0;
}

/**
    Esta função adiciona uma URL à fila.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila onde a URL será adicionada.
        - url: Ponteiro para a string contendo a URL a ser adicionada.

    Retorno:
        A função não possui retorno.
**/
void incluirNaFila(Fila *fila, const char *url) {
    // Aloca memória para o novo nó
    Node *newNode = (Node *) malloc(sizeof(Node));
    // Copia a URL para o novo nó
    strcpy(newNode->url, url);
    newNode->next = NULL;

    // Verifica se a fila não está vazia
    if (fila->rear) {
        fila->rear->next = newNode; // Conecta o novo nó ao final da fila
    } else {
        fila->front = newNode; // Define o novo nó como o primeiro da fila
    }
    fila->rear = newNode; // Atualiza o ponteiro traseiro para o novo nó
    fila->size++; // Incrementa o tamanho da fila
}


/**
    Esta função remove e retorna a URL da frente da fila.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila.

    Retorno:
        Retorna um ponteiro para a string contendo a URL removida da frente da fila.
        Se a fila estiver vazia, retorna NULL.
*/
char *retirarDaFila(Fila *fila) {
    // Verifica se a fila está vazia
    if (fila->front == NULL) {
        return NULL;
    }
    // Armazena o nó da frente temporariamente
    Node *temp = fila->front;
    // Aloca memória para a URL
    char *url = (char *) malloc(MAX_URL_LENGTH * sizeof(char));
    // Copia a URL do nó temporário para a variável de retorno
    strcpy(url, temp->url);
    // Atualiza o ponteiro de frente para o próximo nó da fila
    fila->front = fila->front->next;
    // Se a fila estiver vazia após a remoção, atualiza o ponteiro de trás
    if (fila->front == NULL) {
        fila->rear = NULL;
    }
    // Libera a memória do nó removido
    free(temp);
    // Decrementa o tamanho da fila
    fila->size--;
    // Retorna a URL removida
    return url;
}

/*
    Esta função verifica se a fila está vazia.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila.

    Retorno:
        Retorna 1 se a fila estiver vazia, senão retorna 0.
*/
int isEmpty(Fila *fila) {
    return fila->size == 0;
}

/**
    Esta função imprime todas as URLs na fila.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila.

    Retorno:
        A função não possui retorno.
*/
void printFila(Fila *fila) {
    // Inicializa um ponteiro para percorrer a fila
    Node *current = fila->front;
    // Inicializa um índice para numerar as URLs na impressão
    int index = 1;
    printf("\n");
    // Percorre a fila enquanto houver nós
    while (current) {
        // Imprime o índice e a URL do nó atual
        printf("%d - %s\n", index++, current->url);
        // Move o ponteiro para o próximo nó
        current = current->next;
    }
    printf("\n");
}


/**
    Esta função importa URLs de um arquivo e as adiciona à fila de histórico de navegação.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila.
        - atual: String contendo a URL atual.

    Retorno:
        A função não possui retorno.
*/
void importarHistoricoNavegacao(Fila *fila, char *atual) {
    // Abre o arquivo de URLs para leitura
    FILE *file = fopen("../urls.txt", "r");
    // Verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        printf("Erro ao abrir o arquivo urls.txt\n");
        return;
    }

    // Variável para armazenar cada URL lida do arquivo
    char url[MAX_URL_LENGTH];
    // Lê cada linha do arquivo até encontrar o final do arquivo
    while (fgets(url, MAX_URL_LENGTH, file) != NULL) {
        // Remove o caractere de nova linha do final de cada URL
        url[strcspn(url, "\n")] = 0;

        // Verifica se a URL atende aos critérios de ser válida
        if ((strstr(url, "http://") || strstr(url, "https://")) && (
                strstr(url, ".com") || strstr(url, ".br") || strstr(url, ".org"))) {
            // Se a URL atual não estiver vazia, a adiciona à fila
            if (strlen(atual) > 0) {
                incluirNaFila(fila, atual);
            }
            // Define a URL atual como a URL lida do arquivo
            strcpy(atual, url);
                }
    }
    // Fecha o arquivo após a leitura
    fclose(file);
}


/**
    Esta função simula um navegador web básico usando uma fila para armazenar o histórico de navegação.

    A cada iteração do loop principal, o usuário tem a opção de navegar para uma URL,
    exibir a URL atual, voltar para uma URL anterior, exibir o histórico ou importar
    um histórico de navegação de um arquivo.

    A função continua em execução até que o usuário escolha a opção para sair (0).

    A função utiliza as seguintes funções auxiliares:
        - initFila: Inicializa a fila.
        - incluirNaFila: Adiciona uma URL à fila.
        - isEmpty: Verifica se a fila está vazia.
        - retirarDaFila: Remove e retorna a URL na frente da fila.
        - printFila: Imprime todas as URLs na fila.
        - importarHistoricoNavegacao: Importa URLs de um arquivo e as adiciona à fila.

    Parâmetros:
        A função não recebe parâmetros.

    Retorno:
        A função não possui retorno.
*/
void ex2_filas() {
    // Inicializa a fila e define a URL atual como uma string vazia
    Fila fila;
    initFila(&fila);
    char atual[MAX_URL_LENGTH] = "";

    // Loop principal para interação com o usuário
    while (1) {
        // Exibe as opções do menu
        printf("1 - Navegar para uma URL\n"
               "2 - Exibir URL atual\n"
               "3 - Voltar para uma URL\n"
               "4 - Exibir historico\n"
               "5 - Importar Historico de Navegacao\n"
               "0 - Deseja Sair\n");

        int opcao;
        // Obtém a opção escolhida pelo usuário
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha do buffer

        // Realiza a operação correspondente à opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                // Navegar para uma URL
                char url[MAX_URL_LENGTH];
                printf("Informar uma url\n");
                fgets(url, MAX_URL_LENGTH, stdin);
                url[strcspn(url, "\n")] = 0; // Remove o caractere de nova linha

                // Verifica se a URL é válida e a adiciona à fila
                if (strstr(url, "http://") && strstr(url, ".com")) {
                    if (strlen(atual) > 0) {
                        incluirNaFila(&fila, atual);
                    }
                    strcpy(atual, url);
                    exibirNavegacaoAtualFila(atual);
                } else {
                    printf("URL invalida\n");
                }
                break;

            case 2:
                // Exibir URL atual
                exibirNavegacaoAtualFila(atual);
                break;

            case 3:
                // Voltar para uma URL anterior
                if (!isEmpty(&fila)) {
                    char *url = retirarDaFila(&fila);
                    strcpy(atual, url);
                    free(url);
                    exibirNavegacaoAtualFila(atual);
                } else {
                    printf("Estrutura esta vazia\n");
                }
                break;

            case 4:
                // Exibir o histórico de navegação
                printf("\nImprimindo o conteudo da fila\n");
                printFila(&fila);
                break;

            case 5:
                // Importar histórico de navegação de um arquivo
                importarHistoricoNavegacao(&fila, atual);
                break;

            case 0:
                // Sair do programa
                printf("Saindo....");
                return;

            default:
                // Opção inválida
                printf("Opcao Invalida\n");
        }
    }
}

