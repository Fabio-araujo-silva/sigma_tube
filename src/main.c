#include "../include/avl_alunos.h"
#include "../include/avl_filmes.h"
#include "../include/sigma_tube.h"
#include "menus/Adm.c"
#include "menus/Usuario.c"
#include "menus/MainMenu.c"

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