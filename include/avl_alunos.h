#ifndef AVL_ALUNOS_H
#define AVL_ALUNOS_H

#include "sigma_tube.h"

// No para registro dos filmes em lista circular que será atributo de cada usuário
typedef struct noFilmeLinear
{
    char titulo[MAX_TITULO];
    struct noFilmeLinear *prox;
} NoFilmeLinear;

typedef struct aluno
{
    int n_usp;
    char nome[MAX_NOME];
    NoFilmeLinear *iniAssistidos;
    NoFilmeLinear *iniFav;
    int categorias[MAX_CATEGORIAS];
    int fb;
    struct aluno *esq, *dir;
} Aluno;

typedef struct avlAluno
{
    Aluno *raiz;
} AvlAluno;

AvlAluno *Criar_Arvore_Aluno();
int aux_inserir_aluno(Aluno **raiz, char *nome, int *cresceu, int *n_usp_result);
int cadastraAluno(AvlAluno *arvore, char *nome, int *n_usp_result); // Cadastra um aluno no sistema            // Busca um aluno no sistema a partir do seu nome
int altura(Aluno *p);
Aluno* predecessor(Aluno *u);
int removerAluno(Aluno **p, int usp, int *mudou_h);
int listarAlunos(Aluno *p); // Lista todos os alunos cadastrados no sistema
float Metrica(Aluno *X, Aluno *Y);
void EncontrarMaisProximo(Aluno *p, Aluno *X, Aluno **mais_proximo, float *melhor_metrica);
Aluno *recomendaConvergente(Aluno *p, int n_usp);
void EncontrarMaisDistante(Aluno *p, Aluno *X, Aluno **mais_distante, float *melhor_metrica);
Aluno *recomendaDivergente(Aluno *p, int n_usp);
int adicionarFilmeAssistido(AvlAluno *arvore, int n_usp, char *nome_filme, int categoria);
Aluno *buscaAluno(Aluno *p, int n_usp);
void infosArvoreAluno(AvlAluno *arvore);
int calcularMaiorDiferencaAltura(AvlAluno *arvore);
int maiorGrau(Aluno *raiz);
int contarNos(Aluno *raiz);
/*
int infosArvore();              // Exibe informações técnicas da ABB de alunos
int retirarAluno();             // Apaga cadastro de um aluno
*/

#endif