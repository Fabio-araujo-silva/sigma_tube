#include "sigma_tube.h"

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

// No para registro dos filmes em lista circular que será atributo de cada usuário
typedef struct noFilmeLinear
{
    char titulo[MAX_TITULO];
    struct no_filme_Linear *prox;
} NoFilmeLinear;

int aux_inserir_aluno(Aluno **raiz, char *nome, int *cresceu);
int cadastraAluno(AvlAluno *arvore, char *nome); // Cadastra um aluno no sistema
Aluno *buscaAluno(Aluno *p, int usp);            // Busca um aluno no sistema a partir do seu nome
int altura(Aluno *p);
Aluno* predecessor(Aluno *u);
int removerAluno(Aluno **p, int usp, int *mudou_h);
int listarAlunos(Aluno *p); // Lista todos os alunos cadastrados no sistema
float Metrica(Aluno *X, Aluno *Y);
void EncontrarMaisProximo(Aluno *p, int n_usp, Aluno **mais_proximo, float *melhor_metrica);
Aluno *recomendaConvergente(Aluno *p, Aluno *X);
void EncontrarMaisDistante(Aluno *p, int n_usp, Aluno **mais_distante, float *melhor_metrica);
Aluno *recomendaDivergente(Aluno *p, Aluno *X);
int infosArvore();              // Exibe informações técnicas da ABB de alunos
int retirarAluno();             // Apaga cadastro de um aluno
