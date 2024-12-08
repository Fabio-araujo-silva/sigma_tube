#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/avl_filmes.h"
#include "../include/sigma_tube.h"
#include "../include/avl_alunos.h"

int main()
{
    int n_usp;
    int modo = 0;

    AvlAluno *arvore_alunos = Criar_Arvore_Aluno();
    AvlFilme *arvore_filmes = Criar_Arvore_Filme();

    Aluno *aluno;
    Aluno *colega;

    printf("Bem-vindo ao SigmaTube!\n");

    printf("Selecione a opção desejada:\n");

    while (modo != 12)
    {
        printf("Escolha uma opção:\n");
        printf("1 - Cadastrar um aluno\n");                           // Cadastra um aluno no sistema
        printf("2 - Listar alunos\n");                                // Lista todos os alunos cadastrados no sistema
        printf("3 - Buscar um aluno\n");                              // Busca um aluno no sistema a partir do seu nome verificando se está cadastrado
        printf("4 - Remover um aluno\n");                             // Remove um aluno do sistema
        printf("5 - Listar filmes\n");                                // Lista todos os filmes cadastrados no sistema
        printf("6 - Buscar um filme\n");                              // Busca um filme no sistema a partir do seu nome verificando se foi assistido
        printf("7 - Encontrar colega com gostos similares\n");        // Encontra um amigo com gostos similares a partir de um aluno
        printf("8 - Encontrar colega com gostos diferentes\n");       // Encontra um amigo com gostos diferentes a partir de um aluno
        printf("9 - Exibir top 10 filmes do momento\n");              // Exibe os 10 filmes mais populares do momento
        printf("10 - Produzir relatório\n");                          // Gera arquivo de texto com todas as informações do sistema
        printf("11 - Exibir informações técnicas de armazenmento\n"); // Exibe informações técnicas da ABB de alunos
        printf("12 - Sair\n");
        scanf("%d", &modo);

        switch (modo)
        {

        // Cadastrar um aluno
        case 1:
            printf("Insira o nome do aluno: ");
            char nome[MAX_NOME];
            scanf(" %[^\n]s", nome);
            cadastraAluno(arvore_alunos, nome);
            break;

        // Listar alunos
        case 2:
            listarAlunos(arvore_alunos->raiz);
            break;

        // Buscar um aluno
        case 3:
            printf("Insira o numero usp do aluno: ");
            scanf("%d", n_usp);

            aluno = buscaAluno(arvore_alunos->raiz, n_usp);

            if (aluno != NULL)
            {
                printf("Aluno encontrado!\n");
            }
            else
            {
                printf("Aluno nao encontrado!\n");
            }
            break;

        // Remover um aluno
        case 4:
            printf("Insira o número do aluno a ser removido: ");
            int balanceamento;
            scanf("%d", n_usp);
            removerAluno(&arvore_alunos->raiz, n_usp, &balanceamento);

        // Listar filmes
        case 5:
            listaFilme(arvore_filmes->raiz);
            break;

        // Buscar um filme
        case 6:
            printf("Insira o nome do filme: ");
            char titulo_busca[MAX_TITULO];
            scanf(" %[^\n]s", titulo_busca);

            int assistido = 0;
            buscaFilme(arvore_filmes->raiz, titulo_busca, &assistido);

            if (assistido)
            {
                printf("o filme foi assistido!\n");
            }
            else
            {
                printf("O filme não foi assistido!\n");
            }
            break;

        // Encontrar colega com gostos similares
        case 7:
            printf("Insira o número usp do aluno: ");
            scanf("%d", n_usp);

            Aluno *colega = recomendaConvergente(arvore_alunos->raiz, n_usp);

            printf("O colega com gosto similar é: %s\n", colega->nome);
            break;
        
        // Encontrar colega com gostos diferentes
        case 8:
            printf("Insira o nome do aluno: ");
            scanf("%d", n_usp);
            colega = recomendaDivergente(arvore_alunos->raiz, n_usp);

            printf("O colega com gosto mais divergente é: %s\n", colega->nome);
            break;
/*
        case 9:
            top10doMomento();
            break;

        case 10:
            geraRelatorio();
            break;

        case 11:
            infosArvore();
            break;
        */
        case 12:
            break;
        default:
            break;
        }
        
    }

    return 0;
}