#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"
#include "../include/sigma_tube.h"
/*
#include "..\include\avl_alunos.h"
#include "..\include\avl_filmes.h"
#include "..\include\sigma_tube.h"*/

int Adm(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);
int Usuario(int n_usp, AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);
int MainMenu(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes);

// Função principal, chama o menu principal
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

// Função de menu para o administrador
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
            printf("5 - Produzir relatórios\n");                          // Gera arquivo de texto com todas as informações do sistema
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
                        printf("Aluno %s, N_USP: %d encontrado!\n", aluno->nome, aluno->n_usp);
                    }
                    else
                    {
                        printf("Aluno com numero USP %d nao encontrado!\n", n_usp);
                    }
                    break;

                // Remover um aluno
                case 3:
                    printf("Insira o número do aluno a ser removido: ");
                    int balanceamento;
                    scanf("%d", &n_usp);
                    removerAluno(&arvore_alunos->raiz, n_usp, &balanceamento) == 1 ? printf("Aluno dono do numero USP %d, removido com sucesso\n", n_usp) : printf("Erro na remocao do usuario n_usp %d\n", n_usp);
                    break;

                // Listar filmes
                case 4:
                    listaFilme(arvore_filmes->raiz);
                    break;
        
                case 5:
                    geraRelatorioTerminal(arvore_alunos, arvore_filmes);
                    geraRelatorioJSON(arvore_alunos, arvore_filmes, "relatorio.json");
                    break;

                case 6:
                    infosArvoreAluno(arvore_alunos);
                    break;

                case 7:
                    MainMenu(arvore_alunos, arvore_filmes);
                    break;

                default:
                    break;
            }

        } while (modo != 7);            
}

// Função de menu para o usuário
int Usuario(int n_usp, AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo, flag, categoria, n_uspb;
    int count = 1;
    char nomefilme[MAX_TITULO];
    Aluno *colega;

    printf("=========================================\n");
    printf("Logado como: %s \nSelecione a opção desejada:\n", buscaAluno(arvore_alunos->raiz, n_usp)->nome);

    do {
        printf("=========================================\n");
        printf("1 - Buscar um filme\n");                              // Busca um filme no sistema a partir do seu nome verificando se foi assistido
        printf("2 - Encontrar colega com gostos similares\n");        // Encontra um amigo com gostos similares a partir de um aluno
        printf("3 - Encontrar colega com gostos diferentes\n");       // Encontra um amigo com gostos diferentes a partir de um aluno
        printf("4 - Exibir top 10 filmes do momento\n"); // Exibe os 10 filmes mais populares do momento
        printf("5 - Adicionar filme\n");
        printf("6 - Sair\n");
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
                    printf("o filme esta no catalogo!\n");
                }
                else
                {
                    printf("O filme não esta no catalogo!\n");
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
                top10doMomento(arvore_filmes->raiz);
                break;
            
            case 5:                    
                        printf("Nome do filme %d: ",count);
                        scanf(" %[^\n]s", nomefilme);

                        if (buscaFilme(arvore_filmes->raiz, nomefilme, 0) == 0)
                        {
                            printf("Categoria do filme %d: \n",count);
                            do
                            {
                                printf("1 - Romance\n");
                                printf("2 - Comedia\n");
                                printf("3 - Drama\n");
                                printf("4 - Terror\n");
                                printf("5 - Ficcao\n");
                                printf("6 - Acao\n");
                                scanf("%d", &categoria);
                            } while (categoria > 6 || categoria < 1);
                           adicionarFilmeAssistido(arvore_alunos, n_usp, nomefilme, categoria); 
                           cadastraFilme(arvore_filmes, nomefilme, categoria - 1);
                           if (adicionarVisualizacao(arvore_filmes, nomefilme))
                                printf("Visualização adicionada com sucesso!\n");
                        }
                        else
                        {
                            if (adicionarVisualizacao(arvore_filmes, nomefilme))
                           {
                                categoria = obterCategoriaFilme(arvore_filmes->raiz, nomefilme);
                                printf("Visualização adicionada com sucesso!\n");
                                adicionarFilmeAssistido(arvore_alunos, n_usp, nomefilme, categoria);
                           }
                           else
                           {
                                printf("Filme não encontrado.\n");
                           }
                        }
                break;

            case 6:
                MainMenu(arvore_alunos, arvore_filmes);
                break;

            default:
                break;        
        }
        } while (modo != 6);
}

// Função de menu principal
int MainMenu(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes)
{
    int modo, n_usp, flag, count, categoria;
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
                int n_uspb;
                n_uspb = 0;
                count = 1;
                char nomefilme[MAX_TITULO];
                printf("Insira o nome do aluno: ");
                char nome[MAX_NOME];
                scanf(" %[^\n]s", nome);
                cadastraAluno(arvore_alunos, nome, &n_uspb);
                printf("Ótimo! %s, voce foi cadastrado com numero usp: '%d'\n\n",nome, n_uspb);
                    printf("Deseja adicionar os filmes ja assistidos por você?\n");
                do {
                    printf("1 - Adicionar um filme\n2 - Nao\n\n");
                    scanf("%d", &flag);
                    if (flag == 1)
                    {
                        printf("Nome do filme %d: ",count);
                        scanf(" %[^\n]s", nomefilme);

                        if (buscaFilme(arvore_filmes->raiz, nomefilme, 0) == 0)
                        {
                            printf("Categoria do filme %d: \n",count);
                            do
                            {
                                printf("1 - Romance\n");
                                printf("2 - Comedia\n");
                                printf("3 - Drama\n");
                                printf("4 - Terror\n");
                                printf("5 - Ficcao\n");
                                printf("6 - Acao\n");
                                scanf("%d", &categoria);
                            } while (categoria > 6 || categoria < 1);
                           adicionarFilmeAssistido(arvore_alunos, n_uspb, nomefilme, categoria); 
                           cadastraFilme(arvore_filmes, nomefilme, categoria - 1);
                           if (adicionarVisualizacao(arvore_filmes, nomefilme))
                                printf("Visualização adicionada com sucesso!\n");
                        }
                        else
                        {
                            if (adicionarVisualizacao(arvore_filmes, nomefilme))
                           {
                                printf("Visualização adicionada com sucesso!\n");
                                adicionarFilmeAssistido(arvore_alunos, n_uspb, nomefilme, categoria);
                           }
                           else
                           {
                                printf("Filme não encontrado.\n");
                           }
                        }
                        count++;
                    }
                } while (flag != 2);
                break;

            case 3:
                Adm(arvore_alunos, arvore_filmes);

            case 4:
                exit(0);

            default:
                MainMenu(arvore_alunos, arvore_filmes);
                break;
        }
        
    } while (modo != 4);
}