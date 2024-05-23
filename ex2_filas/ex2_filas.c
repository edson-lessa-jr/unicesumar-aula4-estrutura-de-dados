#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO_MAX_URL 256

// Estrutura de nó da fila
typedef struct Fila {
    char url[TAMANHO_MAX_URL];
    struct Fila *next;
} Fila;

// Estrutura para manter a referência ao início e ao fim da fila
typedef struct {
    Fila *front;
    Fila *rear;
} Queue;

// Função para criar um novo nó
Fila* adicionarFila(const char *url) {
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (novaFila == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strncpy(novaFila->url, url, TAMANHO_MAX_URL);
    novaFila->url[TAMANHO_MAX_URL - 1] = '\0'; // Assegura que a string é terminada com '\0'
    novaFila->next = NULL;
    return novaFila;
}

// Função para enfileirar uma URL
void enqueue(Queue *queue, const char *url) {
    Fila *novaFila = adicionarFila(url);
    if (queue->rear == NULL) {
        queue->front = queue->rear = novaFila;
    } else {
        queue->rear->next = novaFila;
        queue->rear = novaFila;
    }
    printf("Navegando para: %s\n", url);
}

// Função para desenfileirar uma URL
char* dequeue(Queue *queue) {
    if (queue->front == NULL) {
        printf("Histórico vazio.\n");
        return NULL;
    }
    Fila *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    char *url = (char *)malloc(TAMANHO_MAX_URL * sizeof(char));
    if (url == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strncpy(url, temp->url, TAMANHO_MAX_URL);
    free(temp);
    return url;
}

// Função para exibir o histórico
void exibirFila(Queue *queue) {
    printf("Histórico de navegação:\n");
    if (queue->front == NULL) {
        printf("Histórico vazio.\n");
        return;
    }
    Fila *current = queue->front;
    while (current != NULL) {
        printf("%s\n", current->url);
        current = current->next;
    }
}

// Função para carregar URLs de um arquivo
void carregarUrlsDoArquivo(Queue *queue, const char *nomeArquivo) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretório de trabalho atual: %s\n", cwd);
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
        enqueue(queue, url);
    }

    fclose(arquivo);
}

// Função para limpar a fila
void limparFila(Queue *queue) {
    // Limpa a fila antes de sair
    while (queue->front != NULL) {
        char *url = dequeue(queue);
        free(url);
    }
}

int ex2_filas() {
    Queue history = {NULL, NULL};
    int choice;
    char url[TAMANHO_MAX_URL];

    // Carregar URLs do arquivo

    while (1) {
        printf("\nMenu:\n");
        printf("1. Navegar para uma nova URL\n");
        printf("2. Voltar\n");
        printf("3. Exibir histórico\n");
        printf("4. Carregar dados do arquivo\n");
        printf("5. Limpar histórico\n");
        printf("0. Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        switch (choice) {
            case 1:
                printf("Digite a URL: ");
                fgets(url, TAMANHO_MAX_URL, stdin);
                url[strcspn(url, "\n")] = '\0'; // Remove o caractere de nova linha
                enqueue(&history, url);
                break;
            case 2:
                {
                    char *lastUrl = dequeue(&history);
                    if (lastUrl != NULL) {
                        printf("Voltando de: %s\n", lastUrl);
                        free(lastUrl);
                    }
                }
                break;
            case 3:
                exibirFila(&history);
                break;
            case 4:
                carregarUrlsDoArquivo(&history, "../urls.txt");
                break;
            case 5:
                limparFila(&history);
                break;
            case 0:
                limparFila(&history);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
