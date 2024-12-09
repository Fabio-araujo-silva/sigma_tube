#include "../include/avl_filmes.h"

//#include "..\include\avl_filmes.h"


void escreveFilmesJSON(FILE *file, NoFilmeAvl *no, int *primeiro);
void escreveAlunosJSON(FILE *file, Aluno *no, int *primeiro);
void escreveFilmesTerminal(NoFilmeAvl *no);
void escreveAlunosTerminal(Aluno *no);

AvlFilme *Criar_Arvore_Filme() {
    AvlFilme *arvore_filmes = (AvlFilme *)malloc(sizeof(AvlFilme));

    if (arvore_filmes != NULL) {
        arvore_filmes->raiz = NULL;
        return arvore_filmes;
    }
    return NULL;
}

// Função para rotacionar à direita
void DD_f (NoFilmeAvl **raiz)
{
    NoFilmeAvl *pai = *raiz;
    NoFilmeAvl *filho = pai->dir;

    pai->dir = filho->esq;
    filho->esq = pai;
    pai->fb = 0;
    filho->fb = 0;
    *raiz = filho;
}

// Função rotacionar à esquerda
void EE_f (NoFilmeAvl **raiz)
{
    NoFilmeAvl *pai = *raiz;
    NoFilmeAvl *filho = pai->esq;

    pai->esq = filho->dir;
    filho->dir = pai;
    pai->fb = 0;
    filho->fb = 0;
    *raiz = filho;
}

// Função auxiliar para rotação à esquerda e depois à direita
void DE_f (NoFilmeAvl **raiz)
{
    NoFilmeAvl *pai = *raiz;
    NoFilmeAvl *filho = pai->dir;
    NoFilmeAvl *neto = filho->esq;

    pai->dir = neto->esq;
    filho->esq = neto->dir;
    neto->esq = pai;
    neto->dir = filho;

    switch (neto->fb)
    {
    case -1:
        pai->fb = -1;
        filho->fb = 0;
        break;
    case 0:
        pai->fb = 0;
        filho->fb = 0;
        break;
    case 1:
        pai->fb = 0;
        filho->fb = 1;
        break;
    }
    neto->fb = 0;
    *raiz = neto;
}

// Função auxiliar para rotação ED
void ED_f (NoFilmeAvl **raiz)
{
    NoFilmeAvl *pai = *raiz;
    NoFilmeAvl *filho = pai->esq;
    NoFilmeAvl *neto = filho->dir;

    pai->esq = neto->dir;
    filho->dir = neto->esq;
    neto->dir = pai;
    neto->esq = filho;

    switch (neto->fb)
    {
    case -1:
        pai->fb = 1;
        filho->fb = 0;
        break;
    case 0:
        pai->fb = 0;
        filho->fb = 0;
        break;
    case 1:
        pai->fb = 0;
        filho->fb = -1;
        break;
    }
    neto->fb = 0;
    *raiz = neto;
}

// Função auxiliar para inserção de filmes
int aux_inserir_filme(NoFilmeAvl **raiz, char *titulo, int categoria, int *cresceu)
{
    if (*raiz == NULL)
    {
        *raiz = (NoFilmeAvl *)malloc(sizeof(NoFilmeAvl));
        if (*raiz == NULL)
        {
            return 0;
        }
        strcpy((*raiz)->titulo, titulo);
        (*raiz)->categoria = categoria;
        (*raiz)->espectadores = (int *)malloc(sizeof(int));
        if ((*raiz)->espectadores == NULL)
        {
            return 0;
        }
        *((*raiz)->espectadores) = 0;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->fb = 0;
        *cresceu = 1;
    }

    else if (strcmp(titulo, (*raiz)->titulo) < 0)
    {
        if (aux_inserir_filme(&((*raiz)->esq), titulo, categoria, cresceu))
        {
            if (*cresceu)
            {
                switch ((*raiz)->fb)
                {
                case 1:
                    (*raiz)->fb = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    (*raiz)->fb = -1;
                    break;
                case -1:
                    *cresceu = 0;
                    //AJUSTAR
                    DD_f(raiz);
                }
            }
        }
    }
    else if (strcmp(titulo, (*raiz)->titulo) > 0)
    {
        if (aux_inserir_filme(&((*raiz)->dir), titulo, categoria, cresceu))
        {
            if (*cresceu)
            {
                switch ((*raiz)->fb)
                {
                case -1:
                    (*raiz)->fb = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    (*raiz)->fb = 1;
                    break;
                case 1:
                    *cresceu = 0;
                    EE_f(raiz);
                }
            }
        }
    }
    else
    {
        return 0;
    }
}

// Cadastra um filme no sistema
int cadastraFilme(AvlFilme *arvore, char *titulo, int categoria)
{
    int cresceu;
    return aux_inserir_filme(&(arvore->raiz), titulo, categoria, &cresceu);
}

// Lista todos os filmes cadastrados em ordem alfabética
int listaFilme(NoFilmeAvl *p)
{
    char categoria[30];
    if (p != NULL)
    {
        listaFilme(p->esq);
        printf("Titulo: %s,  ", p->titulo);
        switch (p->categoria)
        {
            case 0:
                strcpy(categoria, "Romance");
                break;
            
            case 1:
                strcpy(categoria, "Comedia");
                break;
            
            case 2:
                strcpy(categoria, "Drama");
                break;

            case 3:
                strcpy(categoria, "Terror");
                break;

            case 4:
                strcpy(categoria, "Ficcao");
                break;
            
            case 5:
                strcpy(categoria, "Acao");
                break;

            default:
                strcpy(categoria, " ");
                break;
        }
        printf("Categoria: %s.\n", categoria);
        listaFilme(p->dir);
    }
    return 1;
}

int buscaFilme(NoFilmeAvl *p, char *titulo, int *assistido)
{
    if (p == NULL)
    {
        if (assistido != NULL) {
            *assistido = 0; // Filme não encontrado, nenhum espectador
        }
        return 0; // Filme não encontrado
    }
    
    if (strcmp(titulo, p->titulo) < 0)
    {
        return buscaFilme(p->esq, titulo, assistido);
    }
    else if (strcmp(titulo, p->titulo) > 0)
    {
        return buscaFilme(p->dir, titulo, assistido);
    }
    else
    {
        if (assistido != NULL) {
            *assistido = *(p->espectadores); // Atualiza o número de espectadores
        }
        return 1; // Filme encontrado
    }
}

int adicionarVisualizacao(AvlFilme *arvore, char *titulo) {
    NoFilmeAvl *atual = arvore->raiz;

    while (atual != NULL) {
        int cmp = strcmp(titulo, atual->titulo);

        if (cmp == 0) {
            // Filme encontrado, incrementa o número de espectadores
            (*(atual->espectadores))++;
            return 1; // Sucesso
        } else if (cmp < 0) {
            atual = atual->esq; // Busca na subárvore esquerda
        } else {
            atual = atual->dir; // Busca na subárvore direita
        }
    }
    return 0; // Filme não encontrado
}

// Função auxiliar para percorrer a árvore e coletar filmes e visualizações
void coletarFilmes(NoFilmeAvl *raiz, NoFilmeAvl **filmes, int *contador) {
    if (raiz == NULL) {
        return;
    }

    // Adiciona o filme atual ao vetor de filmes
    filmes[*contador] = raiz;
    (*contador)++;

    // Recurssão nas subárvores
    coletarFilmes(raiz->esq, filmes, contador);
    coletarFilmes(raiz->dir, filmes, contador);
}

// Função para ordenar os filmes com base no número de espectadores (Selection Sort)
void ordenarFilmes(NoFilmeAvl **filmes, int contador) {
    for (int i = 0; i < contador - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < contador; j++) {
            if (*(filmes[j]->espectadores) > *(filmes[max_idx]->espectadores)) {
                max_idx = j;
            }
        }
        // Troca os filmes
        if (max_idx != i) {
            NoFilmeAvl *temp = filmes[i];
            filmes[i] = filmes[max_idx];
            filmes[max_idx] = temp;
        }
    }
}

// Função para exibir os 10 filmes mais populares
int top10doMomento(NoFilmeAvl *raiz) {
    NoFilmeAvl *filmes[1000];  // Vetor para armazenar os filmes (ajustar o tamanho conforme necessário)
    int contador = 0;

    // Coleta todos os filmes da árvore
    coletarFilmes(raiz, filmes, &contador);

    // Ordena os filmes com base no número de espectadores (usando Selection Sort)
    ordenarFilmes(filmes, contador);

    // Exibe os 10 primeiros filmes ou todos os filmes se houver menos que 10
    printf("Top 10 Filmes mais Populares:\n");
    for (int i = 0; i < 10 && i < contador; i++) {
        printf("Titulo: %s, Espectadores: %d\n", filmes[i]->titulo, *(filmes[i]->espectadores));
    }

    return 1;
}

void geraRelatorioTerminal(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes) {
    printf("Relatório do Sistema:\n");
    printf("=====================\n");

    // Processar alunos
    printf("Lista de Alunos:\n");
    if (arvore_alunos->raiz == NULL) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        escreveAlunosTerminal(arvore_alunos->raiz);
    }

    // Processar filmes
    printf("\nLista de Filmes:\n");
    if (arvore_filmes->raiz == NULL) {
        printf("Nenhum filme cadastrado.\n");
    } else {
        escreveFilmesTerminal(arvore_filmes->raiz);
    }

    printf("=====================\n");
}

void escreveAlunosJSON(FILE *file, Aluno *no, int *primeiro) {
    if (no == NULL) return;

    // Percorre a subárvore esquerda
    escreveAlunosJSON(file, no->esq, primeiro);

    // Escreve o nó atual
    if (!*primeiro) {
        fprintf(file, ",\n");
    }
    *primeiro = 0;

    fprintf(file, "    {\n");
    fprintf(file, "      \"n_usp\": %d,\n", no->n_usp);
    fprintf(file, "      \"nome\": \"%s\",\n", no->nome);
    fprintf(file, "      \"filmes_por_categoria\": {\n");
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        fprintf(file, "        \"%s\": %d", NOMES_CATEGORIAS[i], no->categorias[i]);
        if (i < MAX_CATEGORIAS - 1) fprintf(file, ",");
        fprintf(file, "\n");
    }
    fprintf(file, "      }\n");
    fprintf(file, "    }");

    // Percorre a subárvore direita
    escreveAlunosJSON(file, no->dir, primeiro);
}

void escreveFilmesJSON(FILE *file, NoFilmeAvl *no, int *primeiro) {
    if (no == NULL) return;

    // Percorre a subárvore esquerda
    escreveFilmesJSON(file, no->esq, primeiro);

    // Escreve o nó atual
    if (!*primeiro) {
        fprintf(file, ",\n");
    }
    *primeiro = 0;

    fprintf(file, "    {\n");
    fprintf(file, "      \"titulo\": \"%s\",\n", no->titulo);
    fprintf(file, "      \"categoria\": \"%s\",\n", NOMES_CATEGORIAS[no->categoria]);
    fprintf(file, "      \"espectadores\": %d\n", *(no->espectadores));
    fprintf(file, "    }");

    // Percorre a subárvore direita
    escreveFilmesJSON(file, no->dir, primeiro);
}

void geraRelatorioJSON(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao criar o arquivo JSON.\n");
        return;
    }

    fprintf(file, "{\n");

    // Processar alunos
    fprintf(file, "  \"alunos\": [\n");
    int primeiro = 1; // Controle de vírgulas
    escreveAlunosJSON(file, arvore_alunos->raiz, &primeiro);
    fprintf(file, "\n  ],\n");

    // Processar filmes
    fprintf(file, "  \"filmes\": [\n");
    primeiro = 1; // Reseta controle para filmes
    escreveFilmesJSON(file, arvore_filmes->raiz, &primeiro);
    fprintf(file, "\n  ]\n");

    fprintf(file, "}\n");
    fclose(file);
    printf("Relatório JSON salvo em %s\n", filename);
}

void escreveAlunosTerminal(Aluno *no) {
    if (no == NULL) return;

    // Percorre a subárvore esquerda
    escreveAlunosTerminal(no->esq);

    // Exibe o nó atual
    printf("N USP: %d, Nome: %s\n", no->n_usp, no->nome);
    printf("Filmes assistidos por categoria:\n");
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        printf("  %s: %d filmes\n", NOMES_CATEGORIAS[i], no->categorias[i]);
    }
    printf("-------------------------\n");

    // Percorre a subárvore direita
    escreveAlunosTerminal(no->dir);
}

void escreveFilmesTerminal(NoFilmeAvl *no) {
    if (no == NULL) return;

    // Percorre a subárvore esquerda
    escreveFilmesTerminal(no->esq);

    // Exibe o nó atual
    printf("Título: %s\n", no->titulo);
    printf("  Categoria: %s\n", NOMES_CATEGORIAS[no->categoria]);
    printf("  Espectadores: %d\n", *(no->espectadores));
    printf("-------------------------\n");

    // Percorre a subárvore direita
    escreveFilmesTerminal(no->dir);
}

