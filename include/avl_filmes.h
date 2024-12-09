#include "sigma_tube.h"

// No para registro "global" de filmes em árvore de busca binária
typedef struct noFilmeAvl
{
    char titulo[MAX_TITULO];
    int categoria;
    int *espectadores;
    int fb;
    struct noFilmeAvl *esq, *dir;
} NoFilmeAvl;

typedef struct avlFilme
{
    NoFilmeAvl *raiz;
} AvlFilme;

AvlFilme *Criar_Arvore_Filme();
// Funções de manipulação de estruturas
int aux_inserir_filme(NoFilmeAvl **raiz, char *titulo, int categoria, int *cresceu); // Função auxiliar para inserção de filmes
int cadastraFilme(AvlFilme *arvore, char *titulo, int categoria);                    // Cadastra um filme no sistema
int listaFilme(NoFilmeAvl *p); // Lista todos os filmes cadastrados em ordem alfabética
int buscaFilme(NoFilmeAvl *p, char *titulo, int *assistido); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente
int adicionarVisualizacao(AvlFilme *arvore, char *titulo);
/*
// adicionais
int top10doMomento(); // Exibe os 10 filmes mais populares do momento
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();*/
