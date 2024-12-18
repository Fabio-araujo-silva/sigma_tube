#include "sigma_tube.h"
#include "../include/avl_alunos.h"

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
int top10doMomento(NoFilmeAvl *raiz);
// Funções de manipulação de estruturas
int aux_inserir_filme(NoFilmeAvl **raiz, char *titulo, int categoria, int *cresceu); // Função auxiliar para inserção de filmes
int cadastraFilme(AvlFilme *arvore, char *titulo, int categoria);                    // Cadastra um filme no sistema
int listaFilme(NoFilmeAvl *p); // Lista todos os filmes cadastrados em ordem alfabética
int buscaFilme(NoFilmeAvl *p, char *titulo, int *assistido); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente
int adicionarVisualizacao(AvlFilme *arvore, char *titulo);
void geraRelatorioJSON(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes, const char *filename);
void geraRelatorioTerminal(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);

int obterCategoriaFilme(NoFilmeAvl *raiz, char *titulo);
void liberarArvoreFilmes(NoFilmeAvl *raiz);
// Exibe os 10 filmes mais populares do momento
/*
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();*/
