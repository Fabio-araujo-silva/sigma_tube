#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"

int MainMenu(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo, n_usp;
    printf("=========================================\n");
    printf("Selecione a opção desejada:\n");

    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Login\n");
        printf("2 - Cadastrar Aluno\n");
        printf("3 - Funcoes de ADM\n"); 
        printf("4 - Sair\n");
        scanf("%d", &modo);
        switch (modo)
        {
            case 1:
                printf("Informe seu N_USP:\n");
                scanf("%d", n_usp);
                if(buscaAluno(arvore_alunos->raiz, n_usp) != NULL)
                {
                    Usuario(n_usp, arvore_alunos, arvore_filmes);
                }
                else
                {
                    printf("Aluno nao encontrado!\n");
                }        
                break;

            case 2:
                printf("Insira o nome do aluno: ");
                char nome[MAX_NOME];
                scanf(" %[^\n]s", nome);
                cadastraAluno(arvore_alunos, nome);
                break;

            case 3:
                Adm(arvore_alunos, arvore_filmes);

            default:
                break;
        }
        
    } while (modo != 4);

}