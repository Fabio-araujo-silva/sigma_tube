#include "sigma_tube.h"

// No para registro "global" de filmes em árvore de busca binária
typedef struct noFilmeAVL
{
    char titulo[MAX_TITULO];
    int categoria;
    int *espectadores;
    int fb;
    struct noFilmeAbb *esq, *dir;
} NoFilmeAvl;

typedef struct avlFilme
{
    NoFilmeAvl *raiz;
} AvlFilme;

// Funções de manipulação de estruturas
int aux_inserir_filme(NoFilmeAvl **raiz, char *titulo, int categoria, int *cresceu); // Função auxiliar para inserção de filmes
int cadastraFilme(AvlFilme *arvore, char *titulo, int categoria);                    // Cadastra um filme no sistema

int listaFilme(NoFilmeAvl *p); // Lista todos os filmes cadastrados em ordem alfabética

int buscaFilme(NoFilmeAvl *p, char *titulo, int *assistido); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente

// adicionais
int top10doMomento(); // Exibe os 10 filmes mais populares do momento
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();
