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
