
#include "sigma_tube.h"

// No para registro "global" de filmes em árvore de busca binária
typedef struct noFilmeAVL {
    char titulo[MAX_TITULO];
    int categoria;
    int *espectadores;
    struct noFilmeAbb *esq, *dir;
} NoFilmeAvl;

typedef struct avlFilme {
    NoFilmeAvl *raiz;
} AvlFilme;

// Funções de manipulação de estruturas
int listaFilme(); // Lista todos os filmes cadastrados em ordem alfabética
int buscaFilme(); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente

//adicionais
int top10doMomento(); // Exibe os 10 filmes mais populares do momento
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();
