#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ex1_pilhas.h"

// Funcao para inicializar a pilha
Pilha *inicializaPilha() {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    pilha->capacidade = TAMANHO_INICIAL;
    pilha->top = -1;
    pilha->urls = (char **) malloc(pilha->capacidade * sizeof(char *));
    return pilha;
}

// Funcao para empilhar uma URL
void empilha(Pilha *pilha, const char *url) {
    if (pilha->top == pilha->capacidade - 1) {
        pilha->capacidade *= 2;
        pilha->urls = (char **) realloc(pilha->urls, pilha->capacidade * sizeof(char *));
    }
    pilha->urls[++pilha->top] = strdup(url);
}

// Funcao para desempilhar uma URL
char *desempilha(Pilha *pilha) {
    if (pilha->top == -1) {
        printf("Estrutura esta vazia\n");
        return NULL;
    }
    return pilha->urls[pilha->top--];
}

// Funcao para carregar URLs de um arquivo
void carregarUrlsDoArquivo(Pilha *pilha, const char *urlAtual, const char *nomeArquivo) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretorio de trabalho atual: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char url[TAMANHO_MAX_URL];
    while (fgets(url, sizeof(url), arquivo) != NULL) {
        url[strcspn(url, "\n")] = '\0'; // Remove o caractere de nova linha
        if ((strstr(url, "http://")||strstr(url, "https://")) && (strstr(url, ".com")||strstr(url, ".br")||strstr(url, ".org"))) {
            if (strlen(urlAtual) > 0) {
                empilha(pilha, urlAtual);
            }
            strcpy(urlAtual, url);
            exibirNavegacaoAtual(urlAtual);
        } else {
            printf("URL invalida: %s\n",url);
        }
        //empilha(pilha, urlAtual);
    }

    fclose(arquivo);
}

// Funcao para verificar se a pilha esta vazia
int vazio(Pilha *pilha) {
    return pilha->top == -1;
}

// Funcao para exibir o historico
void exibirHistorico(Pilha *pilha) {
    printf("\nImprimindo o conteudo da pilha\n");
    for (int i = pilha->top; i >= 0; i--) {
        printf("%dº %s\n", pilha->top - i + 1, pilha->urls[i]);
    }
}

// Funcao para exibir a URL atual
void exibirNavegacaoAtual(char *atual) {
    printf("Voce esta acessando %s\n\n", atual);
}

int ex1_pilhas() {
    Pilha *pilha = inicializaPilha();
    char atual[TAMANHO_MAX_URL] = "";
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
                        empilha(pilha, atual);
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
                    strcpy(atual, desempilha(pilha));
                    exibirNavegacaoAtual(atual);
                }
                break;
            case 4:
                exibirHistorico(pilha);
                break;
            case 5:
                carregarUrlsDoArquivo(pilha, atual, "../urls.txt");
                desempilha(pilha);
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
