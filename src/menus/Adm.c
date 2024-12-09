#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"

int Adm(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{ 
    int modo, n_usp;
    Aluno *aluno;

    printf("=========================================\n");
    printf("Selecione a opção desejada:\n");
        
        do
        {
            printf("1 - Listar alunos\n");                                // Lista todos os alunos cadastrados no sistema
            printf("2 - Buscar um aluno\n");                              // Busca um aluno no sistema a partir do seu nome verificando se está cadastrado
            printf("3 - Remover um aluno\n");                             // Remove um aluno do sistema
            printf("4 - Listar filmes\n");                                // Lista todos os filmes cadastrados no sistema
            printf("5 - Produzir relatório\n");                          // Gera arquivo de texto com todas as informações do sistema
            printf("6 - Exibir informações técnicas de armazenmento\n"); // Exibe informações técnicas da ABB de alunos
            printf("7 - Sair\n");
            scanf("%d", &modo);

            switch (modo)
            {
            // Listar alunos
                case 1:
                    listarAlunos(arvore_alunos->raiz);
                    break;

                // Buscar um aluno
                case 2:
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
                case 3:
                    printf("Insira o número do aluno a ser removido: ");
                    int balanceamento;
                    scanf("%d", n_usp);
                    removerAluno(&arvore_alunos->raiz, n_usp, &balanceamento);

                // Listar filmes
                case 4:
                    listaFilme(arvore_filmes->raiz);
                    break;
                /*
                case 10:
                    geraRelatorio();
                    break;

                case 11:
                    infosArvore();
                    break;
                */
            case 7:
                    MainMenu(arvore_alunos, arvore_filmes);
                    break;

                default:
                    break;
            }

        } while (modo != 7);            
}