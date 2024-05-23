#ifndef EX2_FILAS_H
#define EX2_FILAS_H

#define MAX_URL_LENGTH 256

typedef struct Node {
    char url[MAX_URL_LENGTH];
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Fila;

// Inicializa a fila
void initFila(Fila* fila);

// Adiciona uma URL na fila
void incluirNaFila(Fila* fila, const char* url);

// Remove e retorna a URL da frente da fila
char* retirarDaFila(Fila* fila);

// Verifica se a fila esta vazia
int isEmpty(Fila* fila);

// Imprime todos os elementos da fila
void printFila(Fila* fila);

// Exibe a URL atual
void exibirNavegacaoAtualFila(char* atual);

// Importa URLs de um arquivo e as adiciona na fila
void importarHistoricoNavegacao(Fila* fila, char* atual);

// Função principal para interagir com o usuário
void ex2_filas();

#endif // EX2_FILAS_H
