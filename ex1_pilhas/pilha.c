#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO_MAX_URL 256

// Estrutura de no da pilhas
typedef struct Pilha {
    char url[TAMANHO_MAX_URL];
    struct Pilha *next;
} Pilha;

// Funcao para criar um novo no
Pilha* adicionarPilha(const char *url) {
    Pilha *novaPilha = (Pilha *)malloc(sizeof(Pilha));
    if (novaPilha == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strncpy(novaPilha->url, url, TAMANHO_MAX_URL);
    novaPilha->url[TAMANHO_MAX_URL - 1] = '\0'; // Assegura que a string é terminada com '\0'
    novaPilha->next = NULL;
    return novaPilha;
}

// Funcao para empilhar uma URL
void push(Pilha **top, const char *url) {
    Pilha *novaPilha = adicionarPilha(url);
    novaPilha->next = *top;
    *top = novaPilha;
    printf("Navegando para: %s\n", url);
}

// Funcao para desempilhar uma URL
char* pop(Pilha **top) {
    if (*top == NULL) {
        printf("Historico vazio.\n");
        return NULL;
    }
    Pilha *temp = *top;
    *top = (*top)->next;
    char *url = (char *)malloc(TAMANHO_MAX_URL * sizeof(char));
    if (url == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strncpy(url, temp->url, TAMANHO_MAX_URL);
    free(temp);
    return url;
}

// Funcao para exibir o historico
void exibirPilha(Pilha *top) {
    printf("Historico de navegacao:\n");
    if (top == NULL) {
        printf("Historico vazio.\n");
        return;
    }
    while (top != NULL) {
        printf("%s\n", top->url);
        top = top->next;
    }
}

// Funcao para carregar URLs de um arquivo
void carregarUrlsDoArquivo(Pilha **top, const char *nomeArquivo) {
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
        push(top, url);
    }

    fclose(arquivo);
}

void limparPilha(Pilha **historico) {
    // Limpa a pilhas antes de sair
    while (historico != NULL) {
        char *url = pop(&historico);
        free(url);
    }

}

int ex1_pilhas() {
    Pilha *history = NULL;
    int choice;
    char url[TAMANHO_MAX_URL];

    // Carregar URLs do arquivo

    while (1) {
        printf("\nMenu:\n");
        printf("1. Navegar para uma nova URL\n");
        printf("2. Voltar\n");
        printf("3. Exibir historico\n");
        printf("4. Carregar dados arquivo\n");
        printf("5. Limpar historico\n");
        printf("0. Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        getchar(); // Limpa o buffer de entrada

        switch (choice) {
            case 1:
                printf("Digite a URL: ");
                fgets(url, TAMANHO_MAX_URL, stdin);
                url[strcspn(url, "\n")] = '\0'; // Remove o caractere de nova linha
                push(&history, url);
                break;
            case 2:
                {
                    char *lastUrl = pop(&history);
                    if (lastUrl != NULL) {
                        printf("Voltando de: %s\n", lastUrl);
                        free(lastUrl);
                    }
                }
                break;
            case 3:
                exibirPilha(history);
                break;
            case 4:
                carregarUrlsDoArquivo(&history, "../urls.txt");
                break;
            case 5:
                limparPilha(&history);
                break;
            case 0:
                limparPilha(&history);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
