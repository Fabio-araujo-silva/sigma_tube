#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"

int Usuario(int n_usp, AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo;
    Aluno *colega;

    printf("=========================================\n");
    printf("Selecione a opção desejada:\n");

    do {
        printf("1 - Buscar um filme\n");                              // Busca um filme no sistema a partir do seu nome verificando se foi assistido
        printf("2 - Encontrar colega com gostos similares\n");        // Encontra um amigo com gostos similares a partir de um aluno
        printf("3 - Encontrar colega com gostos diferentes\n");       // Encontra um amigo com gostos diferentes a partir de um aluno
        printf("4 - Exibir top 10 filmes do momento\n");              // Exibe os 10 filmes mais populares do momento
        printf("5 - Sair\n");
        scanf("%d", &modo);

        switch (modo)
        {
            // Buscar um filme
            case 1:
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
            case 2:
                colega = recomendaConvergente(arvore_alunos->raiz, n_usp);

                printf("O colega com gosto similar é: %s\n", colega->nome);
                break;

            // Encontrar colega com gostos diferentes
            case 3:
                colega = recomendaDivergente(arvore_alunos->raiz, n_usp);

                printf("O colega com gosto mais divergente é: %s\n", colega->nome);
                break;

            case 4:
                top10doMomento();
                break;
            
            case 5:
                MainMenu(arvore_alunos, arvore_filmes);
                break;

            default:
                break;        
        }
        } while (modo != 5);
}