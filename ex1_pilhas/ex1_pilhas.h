/**
Este arquivo de cabeçalho define a interface para manipulação de pilhas de URLs.

    Estrutura de Dados:
        - Pilha: Estrutura para armazenar as URLs. Contém um ponteiro para um array de ponteiros de caracteres
                 (representando as URLs), o índice do topo da pilha e a capacidade máxima da pilha.

    Macros:
        - TAMANHO_MAX_URL: Define o tamanho máximo de uma URL.
        - TAMANHO_INICIAL: Define o tamanho inicial da capacidade da pilha.

    Funções:
        - inicializaPilha: Inicializa uma nova pilha, alocando memória e configurando seus campos.
        - empilha: Adiciona uma URL à pilha.
        - desempilha: Remove e retorna a URL no topo da pilha.
        - carregarUrlsDoArquivo: Carrega URLs de um arquivo e as adiciona à pilha.
        - vazio: Verifica se a pilha está vazia.
        - exibirHistorico: Exibe o histórico de URLs armazenadas na pilha.
        - exibirNavegacaoAtual: Exibe a URL atual.
        - ex1_pilhas: Função principal para interação com o usuário e manipulação da pilha.

    Diretivas de Pré-processador:
        - EX1_PILHAS_H: Evita a inclusão duplicada deste arquivo de cabeçalho.

*/

#ifndef EX1_PILHAS_H
#define EX1_PILHAS_H

#define TAMANHO_MAX_URL 256
#define TAMANHO_INICIAL 10

typedef struct {
    char **urls;
    int top;
    int capacidade;
} Pilha;

Pilha *inicializaPilha();
void empilha(Pilha *pilha, const char *url);
char *desempilha(Pilha *pilha);
void carregarUrlsDoArquivo(Pilha *pilha, const char *urlAtual, const char *nomeArquivo); // Corrigido para aceitar Pilha *
int vazio(Pilha *pilha);
void exibirHistorico(Pilha *pilha);
void exibirNavegacaoAtual(char *atual);
int ex1_pilhas();

#endif // EX1_PILHAS_H
