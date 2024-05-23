#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

// Estrutura para um nó na fila
typedef struct Node {
    char url[MAX_URL_LENGTH];
    struct Node* next;
} Node;

// Estrutura para a fila
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Fila;

// Inicializa a fila
void initFila(Fila* fila) {
    fila->front = NULL;
    fila->rear = NULL;
    fila->size = 0;
}

// Adiciona uma URL na fila
void incluirNaFila(Fila* fila, const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->next = NULL;

    if (fila->rear) {
        fila->rear->next = newNode;
    } else {
        fila->front = newNode;
    }
    fila->rear = newNode;
    fila->size++;
}

// Remove e retorna a URL da frente da fila
char* retirarDaFila(Fila* fila) {
    if (fila->front == NULL) {
        return NULL;
    }
    Node* temp = fila->front;
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    strcpy(url, temp->url);
    fila->front = fila->front->next;
    if (fila->front == NULL) {
        fila->rear = NULL;
    }
    free(temp);
    fila->size--;
    return url;
}

// Verifica se a fila esta vazia
int isEmpty(Fila* fila) {
    return fila->size == 0;
}

// Imprime todos os elementos da fila
void printFila(Fila* fila) {
    Node* current = fila->front;
    int index = 1;
    printf("\n");
    while (current) {
        printf("%d - %s\n", index++, current->url);
        current = current->next;
    }
}

// Exibe a URL atual
void exibirNavegacaoAtual(const char* atual) {
    printf("Voce esta acessando %s\n\n", atual);
}

// Importa URLs de um arquivo e as adiciona na fila
void importarHistoricoNavegacao(Fila* fila, char* atual) {
    FILE* file = fopen("urls.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo urls.txt\n");
        return;
    }

    char url[MAX_URL_LENGTH];
    while (fgets(url, MAX_URL_LENGTH, file) != NULL) {
        url[strcspn(url, "\n")] = 0; // Remove newline character

        if (strstr(url, "http://") && strstr(url, ".com")) {
            if (strlen(atual) > 0) {
                incluirNaFila(fila, atual);
            }
            strcpy(atual, url);
        }
    }
    fclose(file);
}

// Menu de interacao com o usuario
void ex2_filas() {
    Fila fila;
    initFila(&fila);
    char atual[MAX_URL_LENGTH] = "";
    while (1) {
        printf("1 - Navegar para uma URL\n"
               "2 - Exibir URL atual\n"
               "3 - Voltar para uma URL\n"
               "4 - Exibir historico\n"
               "5 - Importar Historico de Navegacao\n"
               "0 - Deseja Sair\n");
        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha do buffer

        if (opcao == 1) {
            char url[MAX_URL_LENGTH];
            printf("Informar uma url\n");
            fgets(url, MAX_URL_LENGTH, stdin);
            url[strcspn(url, "\n")] = 0; // Remove o caractere de nova linha

            if (strstr(url, "http://") && strstr(url, ".com")) {
                if (strlen(atual) > 0) {
                    incluirNaFila(&fila, atual);
                }
                strcpy(atual, url);
                exibirNavegacaoAtual(atual);
            } else {
                printf("URL invalida\n");
            }
        } else if (opcao == 2) {
            exibirNavegacaoAtual(atual);
        } else if (opcao == 3) {
            if (!isEmpty(&fila)) {
                char* url = retirarDaFila(&fila);
                strcpy(atual, url);
                free(url);
                exibirNavegacaoAtual(atual);
            } else {
                printf("Estrutura esta vazia\n");
            }
        } else if (opcao == 4) {
            printf("\nImprimindo o conteudo da fila\n");
            printFila(&fila);
        } else if (opcao == 5) {
            importarHistoricoNavegacao(&fila, atual);
        } else if (opcao == 0) {
            break;
        } else {
            printf("Opcao Invalida\n");
        }
    }
}

