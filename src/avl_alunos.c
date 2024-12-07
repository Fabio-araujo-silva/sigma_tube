//#include ".\include\avl_alunos.h"
#include "../include/avl_alunos.h"

static int usp_counter = 1;

// funcoes do tad
int altura(Aluno *p);

void DD(Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->dir;

    pai->dir = filho->esq;
    filho->esq = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void EE(Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->esq;

    pai->esq = filho->dir;
    filho->dir = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void ED(Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->esq;
    Aluno *neto = filho->dir;

    pai->esq = neto->dir;
    filho->dir = neto->esq;
    neto->dir = pai;
    neto->esq = filho;

    // Ajusta fatores de balanceamento
    if (neto->fb == -1)
    {
        pai->fb = 1;
        filho->fb = 0;
    }
    else if (neto->fb == 1)
    {
        pai->fb = 0;
        filho->fb = -1;
    }
    else
    {
        pai->fb = 0;
        filho->fb = 0;
    }
    neto->fb = 0;

    *r = neto;
}

void DE(Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->dir;
    Aluno *neto = filho->esq;

    pai->dir = neto->esq;
    filho->esq = neto->dir;
    neto->esq = pai;
    neto->dir = filho;

    // Ajusta fatores de balanceamento
    if (neto->fb == 1)
    {
        pai->fb = -1;
        filho->fb = 0;
    }
    else if (neto->fb == -1)
    {
        pai->fb = 0;
        filho->fb = 1;
    }
    else
    {
        pai->fb = 0;
        filho->fb = 0;
    }
    neto->fb = 0;

    *r = neto;
}

int altura(Aluno *p)
{
    if (p == NULL)
        return 0;
    else
    {
        int alt_esq = 1 + altura(p->esq);
        int alt_dir = 1 + altura(p->dir);
        return (alt_esq > alt_dir ? alt_esq : alt_dir);
    }
}

// Função auxiliar para encontrar o predecessor (maior nó da subárvore esquerda)
Aluno* predecessor(Aluno *u) {
    u = u->esq;
    while (u->dir != NULL) {
        u = u->dir;
    }
    return u;
}

// Função de remoção AVL
int removerAluno(Aluno **p, int usp, int *mudou_h) {
    if (*p == NULL) {
        return 0; // não encontrou o aluno
    }

    if (usp < (*p)->n_usp) {
        // Remover na subárvore esquerda
        if (removerAluno(&((*p)->esq), usp, mudou_h)) {
            // Remoção ocorreu à esquerda
            if (*mudou_h) {
                // Ajusta o fb pois a subárvore esquerda diminuiu de altura
                (*p)->fb = (*p)->fb + 1; 
                switch ((*p)->fb) {
                    case 2:
                        // subárvore direita mais alta
                        if ((*p)->dir->fb >= 0) {
                            DD(p); 
                            // Após DD, se o fb do novo nó for 1, altura não muda
                            if ((*p)->fb == 1) *mudou_h = 0;
                        } else {
                            DE(p); 
                            // Após DE, a árvore pode ou não manter a altura
                            // Ajustes finos podem ser necessários dependendo da implementação
                        }
                        break;
                    case 1:
                        // Não mudou a altura total dessa subárvore
                        *mudou_h = 0;
                        break;
                    case 0:
                        // A altura dessa subárvore diminuiu
                        // *mudou_h = 1; já é verdadeiro
                        break;
                }
            }
            return 1; // Remoção bem sucedida
        }
    } else if (usp > (*p)->n_usp) {
        // Remover na subárvore direita
        if (removerAluno(&((*p)->dir), usp, mudou_h)) {
            if (*mudou_h) {
                // subárvore direita diminuiu de altura
                (*p)->fb = (*p)->fb - 1;
                switch ((*p)->fb) {
                    case -2:
                        if ((*p)->esq->fb <= 0) {
                            EE(p);
                            if ((*p)->fb == -1) *mudou_h = 0;
                        } else {
                            ED(p);
                            // Ajustes finos podem ser necessários dependendo da implementação
                        }
                        break;
                    case -1:
                        // Não mudou a altura total
                        *mudou_h = 0;
                        break;
                    case 0:
                        // Altura diminuiu
                        // *mudou_h = 1; já verdadeiro
                        break;
                }
            }
            return 1; 
        }
    } else {
        // usp == (*p)->n_usp, encontrou o nó a remover
        if ((*p)->esq == NULL && (*p)->dir == NULL) {
            // Nó folha
            free(*p);
            *p = NULL;
            *mudou_h = 1; // altura mudou
            return 1;
        } else if ((*p)->esq != NULL && (*p)->dir != NULL) {
            // Nó com duas subárvores
            Aluno *q = predecessor(*p);
            (*p)->n_usp = q->n_usp;
            strcpy((*p)->nome, q->nome);
            // Copie outros campos se necessário (preferencias, etc)
            // Removemos agora o nó predecessor da subárvore esquerda
            if (removerAluno(&((*p)->esq), q->n_usp, mudou_h)) {
                if (*mudou_h) {
                    (*p)->fb = (*p)->fb + 1;
                    switch ((*p)->fb) {
                        case 2:
                            if ((*p)->dir->fb >= 0) {
                                DD(p);
                                if ((*p)->fb == 1) *mudou_h = 0;
                            } else {
                                DE(p);
                            }
                            break;
                        case 1:
                            *mudou_h = 0;
                            break;
                        case 0:
                            // altura diminuiu
                            break;
                    }
                }
                return 1;
            }
        } else {
            // Nó com apenas uma subárvore
            Aluno *aux;
            if ((*p)->esq != NULL) {
                aux = (*p)->esq;
                (*p)->n_usp = aux->n_usp;
                strcpy((*p)->nome, aux->nome);
                // Copie outros campos se necessário
                (*p)->esq = aux->esq;
                (*p)->dir = aux->dir;
                (*p)->fb = aux->fb;
                free(aux);
            } else {
                aux = (*p)->dir;
                (*p)->n_usp = aux->n_usp;
                strcpy((*p)->nome, aux->nome);
                // Copie outros campos se necessário
                (*p)->esq = aux->esq;
                (*p)->dir = aux->dir;
                (*p)->fb = aux->fb;
                free(aux);
            }
            *mudou_h = 1; // remoção alterou a altura
            return 1;
        }
    }

    return 0; // caso não encontrado ou não removido
}

int cadastraAluno(AvlAluno *arvore, char *nome)
{
    int cresceu = 0;
    return aux_inserir_aluno(&arvore->raiz, nome, &cresceu);
}

int aux_inserir_aluno(Aluno **raiz, char *nome, int *cresceu)
{
    if (*raiz == NULL)
    {
        Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
        if (novo == NULL)
            return 1; // Erro de alocação
        usp_counter++;
        novo->n_usp = usp_counter; // autoincrementa o n_usp
        strcpy(novo->nome, nome);
        novo->iniAssistidos = NULL;
        novo->iniFav = NULL;

        // Inicializa preferencia com zero
        for (int i = 0; i < MAX_CATEGORIAS; i++)
        {
            novo->categorias[i] = 0;
        }

        novo->fb = 0;
        novo->esq = novo->dir = NULL;

        *raiz = novo;
        *cresceu = 1;
        return 0; // Sucesso
    }
    if (usp_counter > (*raiz)->n_usp)
    {
        // Inserir à direita
        int ret = aux_inserir_aluno(&(*raiz)->dir, nome, cresceu);
        if (ret != 0)
            return ret;

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
                *cresceu = 1;
                break;
            case 1:
                if ((*raiz)->dir->fb == 1)
                    DD(raiz); // Rotação à direita
                else
                    DE(raiz); // Rotação direita-esquerda
                *cresceu = 0;
                break;
            }
        }
        return ret;
    }
    else
    {
        // Inserir à esquerda (caso por algum motivo o usp_counter fosse menor, o que não ocorrerá se usp_counter só aumenta)
        int ret = aux_inserir_aluno(&(*raiz)->esq, nome, cresceu);
        if (ret != 0)
            return ret;

        if (*cresceu)
        {
            switch ((*raiz)->fb)
            {
            case -1:
                if ((*raiz)->esq->fb == -1)
                    EE(raiz); // Rotação à esquerda
                else
                    ED(raiz); // Rotação esquerda-direita
                *cresceu = 0;
                break;
            case 0:
                (*raiz)->fb = -1;
                *cresceu = 1;
                break;
            case 1:
                (*raiz)->fb = 0;
                *cresceu = 0;
                break;
            }
        }
        return ret;
    }
}

Aluno *buscaAluno(Aluno *p, int n_usp)
{
    if (p == NULL)
    {
        return NULL; // Não encontrou
    }
    else if (p->n_usp == n_usp)
    {
        return p; // Encontrou o aluno
    }
    else if (n_usp < p->n_usp)
    {
        return buscaAluno(p->esq, n_usp); // Se usp for menor, busca na subárvore esquerda
    }
    else
    {
        return buscaAluno(p->dir, n_usp); // Se usp for maior, busca na subárvore direita
    }
}

int listarAlunos(Aluno *p)
{
    if (p != NULL)
    {
        listarAlunos(p->esq);
        printf("N USP: %d, Nome: %s\n", p->n_usp, p->nome);
        listarAlunos(p->dir);
        return 0;
    }
    return 1;
}

float Diferenca(Aluno *aluno1, Aluno *aluno2)
{
    double normaAluno1 = 0, normaAluno2 = 0, somaDiferencas = 0;

    for (int i = 0; i < MAX_CATEGORIAS; i++)
    {
        normaAluno1 += pow(aluno1->categorias[i], 2);
        normaAluno2 += pow(aluno2->categorias[i], 2);
    }

    normaAluno1 = sqrt(normaAluno1);
    normaAluno2 = sqrt(normaAluno2);

    for (int i = 0; i < MAX_CATEGORIAS; i++)
    {
        somaDiferencas += pow(aluno1->categorias[i] * normaAluno2 - aluno2->categorias[i] * normaAluno1, 2);
    }

    return (1 / (2 * normaAluno1 * normaAluno2 * somaDiferencas));
}
