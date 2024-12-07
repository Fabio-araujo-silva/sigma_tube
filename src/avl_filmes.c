//#include ".\include\avl_filmes.h"
#include "../include/avl_filmes.h"

// Função auxiliar para rotação DD
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

// Função auxiliar para rotação EE
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

// Função auxiliar para rotação DE
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
                    return DD_f(raiz);
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
                    return EE_f(raiz);
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

// Busca filme a partir de seu nome e verifica se foi assistido, retornando inteiro correspondente
int buscaFilme(NoFilmeAvl *p, char *titulo, int *assistido)
{
    if (p == NULL)
    {
        assistido = 0;
        return 0;
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
        *assistido = *(p->espectadores);
        return 1;
    }
}

