#include "../include/avl_alunos.h"

int usp_counter = 0;

// funcoes do tad
int altura(Aluno *p);


AvlAluno *Criar_Arvore_Aluno() {
    AvlAluno *arvore_alunos = (AvlAluno *)malloc(sizeof(AvlAluno));

    if (arvore_alunos != NULL) {
        arvore_alunos->raiz = NULL;
        return arvore_alunos;
    }
    return NULL;
}

void DD_a (Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->dir;

    pai->dir = filho->esq;
    filho->esq = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void EE_a (Aluno **r)
{
    Aluno *pai = *r;
    Aluno *filho = pai->esq;

    pai->esq = filho->dir;
    filho->dir = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void ED_a (Aluno **r)
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

void DE_a (Aluno **r)
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

// Função auxiliar para encontrar o prED_aecessor (maior nó da subárvore esquerda)
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
                            DD_a(p); 
                            // Após DD_a, se o fb do novo nó for 1, altura não muda
                            if ((*p)->fb == 1) *mudou_h = 0;
                        } else {
                            DE_a(p); 
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
            return 1; // Remoção bem sucED_aida
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
                            EE_a(p);
                            if ((*p)->fb == -1) *mudou_h = 0;
                        } else {
                            ED_a(p);
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
            // Removemos agora o nó prED_aecessor da subárvore esquerda
            if (removerAluno(&((*p)->esq), q->n_usp, mudou_h)) {
                if (*mudou_h) {
                    (*p)->fb = (*p)->fb + 1;
                    switch ((*p)->fb) {
                        case 2:
                            if ((*p)->dir->fb >= 0) {
                                DD_a(p);
                                if ((*p)->fb == 1) *mudou_h = 0;
                            } else {
                                DE_a(p);
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

    int cadastraAluno(AvlAluno *arvore, char *nome, int *n_usp_result)
    {
        int cresceu = 0;
        return aux_inserir_aluno(&arvore->raiz, nome, &cresceu, n_usp_result);
    }


    int aux_inserir_aluno(Aluno **raiz, char *nome, int *cresceu, int *n_usp_result) {
    if (*raiz == NULL) {
        Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
        if (novo == NULL) {
            return -1; // Erro de alocação: agora retorne um valor negativo para indicar falha
        }

        usp_counter++;
        novo->n_usp = usp_counter; // autoincrementa o n_usp
        strcpy(novo->nome, nome);
        novo->iniAssistidos = NULL;

        // Inicializa preferencia com zero
        for (int i = 0; i < MAX_CATEGORIAS; i++) {
            novo->categorias[i] = 0;
        }

        novo->fb = 0;
        novo->esq = novo->dir = NULL;

        *raiz = novo;
        *cresceu = 1;

        // Aqui retornamos o n_usp via parâmetro
        if (n_usp_result != NULL) {
            *n_usp_result = novo->n_usp;
        }

        return novo->n_usp; // Sucesso agora retorna o n_usp
    }

    int ret;
    if (n_usp_result - (*raiz)->n_usp > 0) {
        // Inserir à direita
        ret = aux_inserir_aluno(&(*raiz)->dir, nome, cresceu, n_usp_result);
        if (ret < 0) // Se retornou negativo, houve erro
            return ret;

        if (*cresceu) {
            switch ((*raiz)->fb) {
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
                        DD_a(raiz); // Rotação à direita
                    else
                        DE_a(raiz); // Rotação direita-esquerda
                    *cresceu = 0;
                    break;
            }
        }
        return ret;
    } else {
        // Inserir à esquerda
        ret = aux_inserir_aluno(&(*raiz)->esq, nome, cresceu, n_usp_result);
        if (ret < 0) // Se retornou negativo, houve erro
            return ret;

        if (*cresceu) {
            switch ((*raiz)->fb) {
                case 1:
                    (*raiz)->fb = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    (*raiz)->fb = -1;
                    *cresceu = 1;
                    break;
                case -1:
                    if ((*raiz)->esq->fb == -1)
                        EE_a(raiz); // Rotação à esquerda
                    else
                        ED_a(raiz); // Rotação esquerda-direita
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

// Metrica para medir a "distância" do gosto de um aluno para outro
float Metrica(Aluno *X, Aluno *Y)
{
    int i;
    float norma_X = 0, norma_Y = 0, produto_interno = 0;
    for(i = 0; i < MAX_CATEGORIAS; i++)
    {
        norma_X += pow((double)X->categorias[i], 2.0);
        norma_Y += pow((double)Y->categorias[i], 2.0);
        produto_interno += X->categorias[i] * Y->categorias[i];
    }
    produto_interno = pow((double)produto_interno, 2.0);
    if(norma_X == 0 || norma_Y == 0)
        return 0;
    else
        return (produto_interno / (norma_X * norma_Y));
}

void EncontrarMaisProximo(Aluno *p, Aluno *X, Aluno **mais_proximo, float *melhor_metrica) {
    if (p == NULL || X == NULL) {
        return; // Evita acessar nós nulos
    }

    // Calcula a métrica apenas se os alunos forem diferentes
    if (p != X) {
        float metrica_atual = Metrica(X, p);
        if (*mais_proximo == NULL || metrica_atual > *melhor_metrica) {
            *melhor_metrica = metrica_atual;
            *mais_proximo = p;
        }
    }

    // Percorre os nós recursivamente
    EncontrarMaisProximo(p->esq, X, mais_proximo, melhor_metrica);
    EncontrarMaisProximo(p->dir, X, mais_proximo, melhor_metrica);
}


// Função principal de recomendação de mais próximo
Aluno *recomendaConvergente(Aluno *p, int n_usp) {
    if (p == NULL) {
        printf("Erro: Árvore de alunos vazia.\n");
        return NULL;
    }

    Aluno *X = buscaAluno(p, n_usp);
    if (X == NULL || (p->esq == NULL && p->dir == NULL)) {
        printf("Erro: Nenhum aluno para comparar ou aluno com N_USP %d não encontrado.\n", n_usp);
        return NULL;
    }

    Aluno *mais_proximo = NULL;
    float melhor_metrica = 0;

    EncontrarMaisProximo(p, X, &mais_proximo, &melhor_metrica);

    if (mais_proximo == NULL) {
        printf("Erro: Nenhum aluno encontrado como mais próximo.\n");
    }

    return mais_proximo;
}

void EncontrarMaisDistante(Aluno *p, Aluno *X, Aluno **mais_distante, float *melhor_metrica) {
    if (p == NULL || X == NULL) {
        return;
    }

    // Calcular a métrica para o aluno atual, se for diferente de X
    if (p != X) { // Comparação por endereço para evitar o próprio aluno
        float metrica_atual = Metrica(X, p);
        if (*mais_distante == NULL || metrica_atual < *melhor_metrica) {
            *melhor_metrica = metrica_atual;
            *mais_distante = p;
        }
    }

    // Percorrer subárvore esquerda e direita
    EncontrarMaisProximo(p->esq, X, mais_distante, melhor_metrica);
    EncontrarMaisDistante(p->dir, X, mais_distante, melhor_metrica);
}

// Função principal de recomendação de mais distante
Aluno *recomendaDivergente(Aluno *p, int n_usp) {
    if (p == NULL) {
        printf("Erro: Árvore de alunos vazia.\n");
        return NULL;
    }

    Aluno *X = buscaAluno(p, n_usp);
    if (X == NULL || (p->esq == NULL && p->dir == NULL)) {
        printf("Erro: Nenhum aluno para comparar ou aluno com N_USP %d não encontrado.\n", n_usp);
        return NULL;
    }

    Aluno *mais_distante = NULL;
    float melhor_metrica = 1; // Iniciar com o valor máximo para minimizar

    EncontrarMaisDistante(p, X, &mais_distante, &melhor_metrica);

    if (mais_distante == NULL) {
        printf("Erro: Nenhum aluno encontrado como mais distante.\n");
    }

    return mais_distante;
}

int adicionarFilmeAssistido(AvlAluno *arvore, int n_usp, char *nome_filme, int categoria) {
    // Ajustar a categoria para indexação baseada em 0
    if (categoria < 1 || categoria > MAX_CATEGORIAS) {
        printf("Erro: Categoria %d inválida. Deve estar entre 1 e %d.\n", categoria, MAX_CATEGORIAS);
        return -3; // Retorno para categoria inválida
    }
    categoria -= 1; // Converter de 1 a 6 para 0 a 5

    // Busca o aluno a partir do n_usp
    Aluno *aluno = buscaAluno(arvore->raiz, n_usp);
    if (aluno == NULL) {
        printf("Erro: Aluno com N_USP %d não encontrado.\n", n_usp);
        return -1;
    }

    // Cria um novo nó de filme
    NoFilmeLinear *novo = (NoFilmeLinear *) malloc(sizeof(NoFilmeLinear));
    if (novo == NULL) {
        printf("Erro: Falha na alocação de memória para filme %s.\n", nome_filme);
        return -2;
    }
    strcpy(novo->titulo, nome_filme);

    // Caso a lista de filmes assistidos esteja vazia
    if (aluno->iniAssistidos == NULL) {
        novo->prox = novo; // Lista circular de um único elemento
        aluno->iniAssistidos = novo;
    } else {
        // Insere no final da lista circular
        NoFilmeLinear *aux = aluno->iniAssistidos;
        while (aux->prox != aluno->iniAssistidos) {
            aux = aux->prox;
        }
        novo->prox = aluno->iniAssistidos;
        aux->prox = novo;
    }

    // Incrementa o contador da categoria correspondente
    aluno->categorias[categoria]++;
    printf("Filme '%s' adicionado com sucesso para o aluno %d na categoria '%s'.\n", 
           nome_filme, n_usp, NOMES_CATEGORIAS[categoria]);
    return 0; // Sucesso
}

void infosArvoreAluno(AvlAluno *arvore) {
    if (arvore == NULL) {
        printf("Erro: Árvore de alunos não inicializada.\n");
        return;
    }

    printf("Informações da árvore de alunos:\n");
    printf("Maior difereça de altura: %d\n", calcularMaiorDiferencaAltura(arvore));
    printf("Maior grau: %d\n", maiorGrau(arvore->raiz));
    printf("Quantidade de nós: %d\n", contarNos(arvore->raiz));
}

// Função auxiliar recursiva para calcular a maior diferença de fatores de balanceamento
void calcularMaiorDiferencaAux(Aluno *no, int *maior_diferenca) {
    if (no == NULL) return;

    // Verifica o valor absoluto do fator de balanceamento do nó atual
    int diferenca_atual = abs(no->fb);

    // Atualiza a maior diferença encontrada
    if (diferenca_atual > *maior_diferenca) {
        *maior_diferenca = diferenca_atual;
    }

    // Recorre para os filhos esquerdo e direito
    calcularMaiorDiferencaAux(no->esq, maior_diferenca);
    calcularMaiorDiferencaAux(no->dir, maior_diferenca);
}

// Função principal para calcular a maior diferença de fatores de balanceamento
int calcularMaiorDiferencaAltura(AvlAluno *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        return 0; // Árvore vazia, diferença de altura é 0
    }

    int maior_diferenca = 0;
    calcularMaiorDiferencaAux(arvore->raiz, &maior_diferenca);
    return maior_diferenca;
}

// Função auxiliar para calcular o maior grau na árvore AVL
int maiorGrau(Aluno *raiz) {
    if (raiz == NULL) {
        return 0; // Se a árvore está vazia, o maior grau é 0
    }

    // Calcula o grau do nó atual
    int grau_atual = 0;
    if (raiz->esq != NULL) grau_atual++;
    if (raiz->dir != NULL) grau_atual++;

    // Recursivamente, verifica o maior grau das subárvores
    int grau_esq = maiorGrau(raiz->esq);
    int grau_dir = maiorGrau(raiz->dir);

    // Retorna o maior grau encontrado
    return (grau_atual > grau_esq ? (grau_atual > grau_dir ? grau_atual : grau_dir) : (grau_esq > grau_dir ? grau_esq : grau_dir));
}

// Função para contar a quantidade de nós na árvore AVL
int contarNos(Aluno *raiz) {
    if (raiz == NULL) {
        return 0; // Se a árvore está vazia, não há nós
    }

    // Conta o nó atual e os nós das subárvores
    int esquerda = contarNos(raiz->esq);
    int direita = contarNos(raiz->dir);
    return 1 + esquerda + direita;
}

void liberarListaCircular(NoFilmeLinear *inicio) {
    if (inicio == NULL) return;

    NoFilmeLinear *atual = inicio->prox;
    while (atual != inicio) {
        NoFilmeLinear *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(inicio); // Libera o nó inicial
}

void liberarArvoreAlunos(Aluno *raiz) {
    if (raiz == NULL) return;

    liberarArvoreAlunos(raiz->esq);
    liberarArvoreAlunos(raiz->dir);

    liberarListaCircular(raiz->iniAssistidos); // Libera a lista circular de filmes
    free(raiz); // Libera o nó atual
}

