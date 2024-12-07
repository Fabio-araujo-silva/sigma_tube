#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 40
#define MAX_TITULO 40
#define MAX_CATEGORIAS 6

// No para registro "global" de filmes em árvore de busca binária
typedef struct noFilmeAVL {
    char titulo[MAX_TITULO];
    int categoria;
    int *espectadores;
    struct noFilmeAbb *esq, *dir;
} NoFilmeAbb;

// No para registro dos filmes em lista circular que será atributo de cada usuário
typedef struct noFilmeLinear {
    char titulo[MAX_TITULO];
    struct no_filme_Linear *prox;
} NoFilmeLinear;

typedef struct aluno {
    int n_usp;
    char nome[MAX_NOME];
    NoFilmeLinear *iniAssistidos;
    NoFilmeLinear *iniFav;
    int preferencia[MAX_CATEGORIAS];
    struct aluno *esq, *dir;
} Aluno;

typedef struct avlAluno {
    Aluno *raiz;
} AbbAluno;

// Funções de manipulação de estruturas

int cadastraAluno(); // Cadastra um aluno no sistema
int listaAlunos(); // Lista todos os alunos cadastrados no sistema
Aluno buscaAluno(); // Busca um aluno no sistema a partir do seu nome
int listaFilme(); // Lista todos os filmes cadastrados em ordem alfabética
int buscaFilme(); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente
Diferenca(Aluno aluno1, Aluno aluno2);
Aluno preferenciaConvergente(); // Aponta o aluno cujas preferências são mais compatíveis
Aluno preferenciaDivergente(); // Aponta o aluno cujas preferências são menos compatíveis
int geraRelatorio(); // Gera arquivo de texto com todas as informações do sistema
int infosArvore(); // Exibe informações técnicas da ABB de alunos
int retirarAluno(); // Apaga cadastro de um aluno

// Funcionalidades adicionais
int top10doMomento(); // Exibe os 10 filmes mais populares do momento
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();
