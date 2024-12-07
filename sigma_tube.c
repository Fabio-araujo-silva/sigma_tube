#include <sigma_tube.h>

int n_usp;
int insereArvore();
AbbAluno Arvore;

int cadastraAluno(char *nome) {
    Aluno aluno;
    strcpy(aluno.nome, nome);
    if ()
    aluno.n_usp = n_usp++;
}

int listaAlunos(); // Lista todos os alunos cadastrados no sistema
Aluno buscaAluno(); // Busca um aluno no sistema a partir do seu nome
int listaFilme(); // Lista todos os filmes cadastrados em ordem alfabética
int buscaFilme(); // Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente
float Diferenca(Aluno aluno1, Aluno aluno2) {
    double normaAluno1 = 0, normaAluno2 = 0, somaDiferencas = 0;

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        normaAluno1 += pow(aluno1->categorias[i], 2);
        normaAluno2 += pow(aluno2->categorias[i], 2);
    }

    normaAluno1 = sqrt(normaAluno1);
    normaAluno2 = sqrt(normaAluno2);

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        somaDiferencas += pow(aluno1->categorias[i] * normaAluno2 - aluno2->categorias[i] * normaAluno1, 2);
    }

    return (1 / (2 * normaAluno1 * normaAluno2 * somaDiferencas));
}

Aluno preferenciaConvergente(); // Aponta o aluno cujas preferências são mais compatíveis
Aluno preferenciaDivergente(); // Aponta o aluno cujas preferências são menos compatíveis
int geraRelatorio(); // Gera arquivo de texto com todas as informações do sistema
int infosArvore(); // Exibe informações técnicas da ABB de alunos
int retirarAluno(); // Apaga cadastro de um aluno

// Funcionalidades adicionais
int top10doMomento(); // Exibe os 10 filmes mais populares do momento
int adicionaFilmeFavorito();
int imprimeFilmesFavorito();
