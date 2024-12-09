#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"
#include "../include/sigma_tube.h"

int Adm(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);
int Usuario(int n_usp, AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);
int MainMenu(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);

int main()
{
    int n_usp;
    int modo = 0;

    AvlAluno *arvore_alunos = Criar_Arvore_Aluno();
    AvlFilme *arvore_filmes = Criar_Arvore_Filme();

    printf("Bem-vindo ao SigmaTube!\n");

    MainMenu(arvore_alunos, arvore_filmes);

    return 0;
}

int Adm(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{ 
    int modo, n_usp;
    Aluno *aluno;

    printf("Selecione a opção desejada:\n");
        
        do
        {
            printf("=========================================\n");
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
                    scanf("%d", &n_usp);

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
                    scanf("%d", &n_usp);
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

int Usuario(int n_usp, AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo;
    Aluno *colega;

    printf("=========================================\n");
    printf("Logado como: %s \nSelecione a opção desejada:\n", buscaAluno(arvore_alunos->raiz, n_usp)->nome);

    do {
        printf("=========================================\n");
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
                /*top10doMomento();*/
                break;
            
            case 5:
                MainMenu(arvore_alunos, arvore_filmes);
                break;

            default:
                break;        
        }
        } while (modo != 5);
}

int MainMenu(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo, n_usp, flag, count, categoria, n_uspb;
    printf("Selecione a opção desejada:\n");

    do {

        printf("=========================================\n");
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
                scanf("%d", &n_usp);
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
                count = 1;
                char nomefilme[MAX_TITULO];
                printf("Insira o nome do aluno: ");
                char nome[MAX_NOME];
                scanf(" %[^\n]s", nome);
                cadastraAluno(arvore_alunos, nome, &n_uspb);
                printf("Ótimo! seu numero usp e: %d\n",n_uspb);
                    printf("Insira os filmes ja assistidos por você: \n");
                do {
                    printf("1 - Adicionar um filme\n2 - Sair\n");
                    scanf("%d", &flag);
                    if (flag == 1)
                    {
                        printf("Nome do filme %d: ",count);
                        scanf(" %[^\n]s", nomefilme);

                        printf("Categoria do filme %d: \n",count);
                        printf("1 - Romance\n");
                        printf("2 - Comedia\n");
                        printf("3 - Drama\n");
                        printf("4 - Terror\n");
                        printf("5 - Ficcao\n");
                        printf("6 - Acao\n");
                        scanf("%d", &categoria);

                        if (buscaFilme(arvore_filmes->raiz, nomefilme, 0) == 0)
                        {
                           //aumentar em 1 a visualização
                           adicionarFilmeAssistido(arvore_alunos, n_uspb, nomefilme); 
                           cadastraFilme(arvore_filmes, nomefilme, categoria - 1);
                        }
                        else
                        {
                            //aumentar visualização
                        }
                        count++;
                    }
                } while (flag != 2);
                break;

            case 3:
                Adm(arvore_alunos, arvore_filmes);

            default:
                break;
        }
        
    } while (modo != 4);

}