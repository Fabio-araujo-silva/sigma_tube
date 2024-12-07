# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "include/avl_filmes.h"
# include "include/sigma_tube.h"
# include "include/avl_alunos.h"

int main()
{
    int modo = 0;

    while (modo != 5)
    {
        printf("Escolha uma opção:\n");
        printf("1 - Cadastrar um filme\n");
        printf("2 - Buscar um filme\n");
        printf("3 - Adicionar um espectador a um filme\n");
        printf("4 - Remover um filme\n");
        printf("5 - Sair\n");
        scanf("%d", &modo);

        switch (modo)
        {
        case 1:
            printf("Cadastrando um filme\n");
            break;
        case 2:
            printf("Buscando um filme\n");
            break;
        case 3:
            printf("Adicionando um espectador a um filme\n");
            break;
        case 4:
            printf("Removendo um filme\n");
            break;
        case 5:
            printf("Saindo\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    }

    return 0;
}