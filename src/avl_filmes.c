//#include "../include/avl_filmes.h"

#include "..\include\avl_filmes.h"


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
    if (p != NULL)
    {
        listaFilme(p->esq);
        printf("%s\n", p->titulo);
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
<<<<<<< Updated upstream
=======

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
>>>>>>> Stashed changes
