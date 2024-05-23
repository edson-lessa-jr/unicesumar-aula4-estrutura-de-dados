#ifndef NAVEGACAO_H
#define NAVEGACAO_H

#include "ex1_pilhas/ex1_pilhas.h"
#include "ex2_filas/ex2_filas.h"

// Estrutura para a inicialização da navegação
typedef struct {
    char* atual;
    Pilha* pilha;
    Fila* fila;
} Navegacao;

// Inicializa a estrutura de navegação
Navegacao* inicializaNavegacao();

// Navega para uma nova URL
void navegar(Navegacao* nav, const char* url);

// Volta para a URL anterior
void voltar(Navegacao* nav);

// Exibe o histórico de navegação
void exibirHistoricoNavegacao(Navegacao* nav);

#endif // NAVEGACAO_H
