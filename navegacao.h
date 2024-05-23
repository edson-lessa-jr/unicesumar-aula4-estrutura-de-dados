/**
Este arquivo de cabeçalho define a estrutura e as funções relacionadas à navegação
    em um navegador web, utilizando pilhas e filas para manter o histórico de navegação.

    Estruturas de Dados:
        - Navegacao: Estrutura que contém o URL atual, a pilha de histórico e a fila de URLs visitadas.

    Funções:
        - inicializaNavegacao: Inicializa a estrutura de navegação, alocando memória e inicializando as estruturas internas.
        - navegar: Navega para uma nova URL, empilhando a URL atual e adicionando-a à fila de URLs visitadas.
        - voltar: Volta para a URL anterior, desempilhando a URL atual da pilha.
        - exibirHistoricoNavegacao: Exibe o histórico de navegação, mostrando as URLs visitadas na ordem em que foram acessadas.

    Parâmetros:
        - nav: Ponteiro para a estrutura de navegação.
        - url: Ponteiro para uma string contendo a nova URL a ser navegada.

    Retorno:
        - Não há retorno.
*/

#ifndef NAVEGACAO_H
#define NAVEGACAO_H

#include "ex1_pilhas/ex1_pilhas.h" // Inclui o cabeçalho da pilha
#include "ex2_filas/ex2_filas.h" // Inclui o cabeçalho da fila

// Estrutura para a inicialização da navegação
typedef struct {
    char* atual; // URL atual
    Pilha* pilha; // Pilha para o histórico de navegação
    Fila* fila; // Fila para as URLs visitadas
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
