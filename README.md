
# SigmaTube

SigmaTube é um sistema de gerenciamento para usuários e filmes, desenvolvido em C, utilizando Árvores AVL para organizar os dados de forma eficiente. O projeto permite cadastrar usuários, associar filmes assistidos a cada usuário, e gerar relatórios detalhados tanto no terminal quanto em formato JSON.

## Funcionalidades

- Cadastro de usuários e filmes.
- Associação de filmes assistidos a usuários, categorizados por gênero.
- Relatórios detalhados:
  - **Terminal:** Listagem de usuários e filmes assistidos por categoria.
  - **JSON:** Geração de arquivos JSON contendo todos os dados organizados.
- Recomendações baseadas nos gostos dos usuários:
  - **Convergentes:** Encontra usuários com gostos similares.
  - **Divergentes:** Encontra usuários com gostos diferentes.

---

## Estrutura do Projeto

```plaintext
SigmaTube/
├── include/
│   ├── sigma_tube.h         # Cabeçalho geral do projeto
│   ├── avl_alunos.h         # Funções e estruturas relacionadas a usuários
│   └── avl_filmes.h         # Funções e estruturas relacionadas a filmes
├── src/
│   ├── sigma_tube.c         # Implementação das funções gerais
│   ├── avl_alunos.c         # Implementação das funções relacionadas a usuários
│   ├── avl_filmes.c         # Implementação das funções relacionadas a filmes
│   └── main.c               # Arquivo principal do projeto
└── README.md                # Documentação do projeto
```

---

## Pré-requisitos

- **Compilador C:** GCC ou equivalente.
- **Sistema operacional:** Windows, Linux ou macOS.

---

## Compilação e Execução

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/seu-usuario/sigma-tube.git
   cd sigma-tube
   ```

2. **Compile o projeto:**
   ```bash
   gcc src/main.c src/sigma_tube.c src/avl_alunos.c src/avl_filmes.c -o sigma_tube
   ```

3. **Execute o programa:**
   ```bash
   ./sigma_tube
   ```

---

## Uso

1. Ao iniciar o programa, você verá um menu principal:
   ```
   Bem-vindo ao SigmaTube!
   1 - Login
   2 - Cadastrar Aluno
   3 - Funções de ADM
   4 - Sair
   ```

2. Escolha a opção desejada e siga as instruções.

3. Exemplos de funcionalidades:
   - **Cadastrar Aluno:** Insira o nome e associe filmes assistidos ao aluno.
   - **Adicionar Filme:** Escolha uma categoria entre:
     - Romance
     - Comédia
     - Drama
     - Terror
     - Ficção
     - Ação
   - **Relatórios:**
     - Gerar relatório no terminal ou como arquivo JSON.

---

## Estruturas de Dados

- **Árvore AVL (Alunos):**
  - Cada nó representa um aluno com as seguintes informações:
    - Número USP (chave única).
    - Nome do aluno.
    - Lista circular de filmes assistidos.
    - Contagem de filmes assistidos por categoria.
- **Árvore AVL (Filmes):**
  - Cada nó representa um filme com as seguintes informações:
    - Título.
    - Categoria.
    - Número de espectadores.

---

## Geração de Relatórios

1. **Terminal:**
   - Listagem formatada dos alunos, suas categorias assistidas e filmes.
   - Listagem dos filmes cadastrados com suas categorias e número de espectadores.

2. **JSON:**
   - Arquivo gerado com a estrutura:
     ```json
     {
       "alunos": [
         {
           "n_usp": 12345,
           "nome": "Fulano",
           "filmes_por_categoria": {
             "Romance": 3,
             "Comédia": 1,
             "Drama": 0,
             "Terror": 2
           }
         }
       ],
       "filmes": [
         {
           "titulo": "Um Filme",
           "categoria": "Romance",
           "espectadores": 10
         }
       ]
     }
     ```
