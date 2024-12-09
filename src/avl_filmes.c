#include "../include/avl_filmes.h"

void escreveFilmesJSON(FILE *file, NoFilmeAvl *no, int *primeiro);
void escreveAlunosJSON(FILE *file, Aluno *no, int *primeiro);

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

void geraRelatorioTerminal(AvlAluno *arvore_alunos, AvlFilme *arvore_filmes) {
    printf("Relatório do Sistema:\n");
    printf("=====================\n");
    printf("Lista de Alunos:\n");

    Aluno *alunoAtual = arvore_alunos->raiz;
    while (alunoAtual != NULL) { // Iterar pelos alunos da árvore
        printf("Nome: %s, N_USP: %d\n", alunoAtual->nome, alunoAtual->n_usp);
        printf("Filmes assistidos por categoria:\n");
        for (int i = 0; i < MAX_CATEGORIAS; i++) {
            printf("  Categoria %d: %d filmes\n", i, alunoAtual->categorias[i]);
        }
        alunoAtual = alunoAtual->dir; // Supondo um método para iterar os nós
    }

    printf("\nLista de Filmes:\n");
    NoFilmeAvl *filmeAtual = arvore_filmes->raiz;
    while (filmeAtual != NULL) { // Iterar pelos filmes da árvore
        printf("Título: %s, Categoria: %d, Espectadores: %d\n", 
               filmeAtual->titulo, 
               filmeAtual->categoria, 
               *(filmeAtual->espectadores));
        filmeAtual = filmeAtual->dir; // Supondo um método para iterar os nós
    }
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
        fprintf(file, "        \"categoria_%d\": %d", i, no->categorias[i]);
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
    fprintf(file, "      \"categoria\": %d,\n", no->categoria);
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
