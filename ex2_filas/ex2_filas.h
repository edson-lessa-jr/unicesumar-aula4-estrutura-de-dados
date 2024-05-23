/*
    Este arquivo de cabeçalho define a estrutura e as funções relacionadas a uma fila
    utilizada para simular um histórico de navegação em um navegador web.

    Estruturas de Dados:
        - Node: Estrutura que representa um nó na fila, contendo uma URL e um ponteiro para o próximo nó.
        - Fila: Estrutura que representa a fila, contendo ponteiros para o primeiro e o último nós da fila,
                bem como o tamanho atual da fila.

    Funções:
        - initFila: Inicializa a fila, definindo os ponteiros frontal e traseiro como nulos e o tamanho como zero.
        - incluirNaFila: Adiciona uma nova URL à fila.
        - retirarDaFila: Remove e retorna a URL na frente da fila.
        - isEmpty: Verifica se a fila está vazia.
        - printFila: Imprime todas as URLs na fila.
        - exibirNavegacaoAtualFila: Exibe a URL atual que está sendo acessada.
        - importarHistoricoNavegacao: Importa URLs de um arquivo e as adiciona à fila.

    A função principal, ex2_filas(), permite que o usuário interaja com a fila de URLs,
    simulando um navegador web básico.

    Parâmetros:
        - fila: Ponteiro para a estrutura da fila.
        - url: Ponteiro para uma string contendo a URL atual.
        - atual: String contendo a URL atual que está sendo acessada.

    Retorno:
        - Não há retorno.
*/

#ifndef EX2_FILAS_H
#define EX2_FILAS_H

#define MAX_URL_LENGTH 256

// Definição da estrutura do nó da fila
typedef struct Node {
    char url[MAX_URL_LENGTH]; // URL armazenada no nó
    struct Node* next; // Ponteiro para o próximo nó
} Node;

// Definição da estrutura da fila
typedef struct {
    Node* front; // Ponteiro para o primeiro nó da fila
    Node* rear; // Ponteiro para o último nó da fila
    int size; // Tamanho atual da fila
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
