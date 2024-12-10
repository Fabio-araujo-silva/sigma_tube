CFLAGS = -Wno-implicit-function-declaration

all: final

final: main.o avl_alunos.o avl_filmes.o sigma_tube.o
	gcc $(CFLAGS) main.o avl_alunos.o avl_filmes.o sigma_tube.o -o sigmaTube -lm

avl_alunos.o: avl_alunos.c
	@echo "Compilando avl_alunos.c..."
	gcc $(CFLAGS) -c avl_alunos.c

avl_filmes.o: avl_filmes.c
	@echo "Compilando avl_filmes.c..."
	gcc $(CFLAGS) -c avl_filmes.c

sigma_tube.o: sigma_tube.c
	@echo "Compilando sigma_tube.c..."
	gcc $(CFLAGS) -c sigma_tube.c

main.o: main.c
	@echo "Compilando main.c..."
	gcc $(CFLAGS) -c main.c

clean:
	@echo "Removendo arquivos .o..."
	rm main.o avl_filmes.o avl_alunos.o sigma_tube.o sigmaTube
