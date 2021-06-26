#include<stdio.h>
#include<stdlib.h>

struct elemento {
	struct elemento *linha, *coluna;
	int px, py;
	float valor;
};

struct matriz {
	int linhas, colunas;
	struct elemento **grid;
};

struct matriz * gerar_matriz(int linhas, int colunas);
void completar_matriz(struct matriz *m, int px, int py, float valor);
void liberar_matriz(struct matriz * m);
void liberar_lc (struct matriz *m, int ini, int fim);

int main (void) {
	struct matriz *matriz;

	matriz = gerar_matriz(4,5);
	completar_matriz(matriz, 4, 5, 100);
	liberar_matriz(matriz);

	return 0;
}

struct matriz * gerar_matriz(int linhas, int colunas) {
	int i;
	struct matriz *m;

	m = malloc(sizeof(struct matriz));

	m->linhas = linhas;
	m->colunas = colunas;
	m->grid = malloc(sizeof(struct elemento*) * (linhas + colunas));
	
	//Dummy de linha
	for(i = 0; i < linhas; i++) {
		m->grid[i] = malloc(sizeof(struct elemento));
		m->grid[i]->px = -1;
		m->grid[i]->py = 0;
		m->grid[i]->linha = m->grid[i];
		m->grid[i]->coluna = NULL;
	}
	//Dummy de colunas
	for(i = linhas; i < linhas + colunas; i++) {
		m->grid[i] = malloc(sizeof(struct elemento));
		m->grid[i]->px = 0;
		m->grid[i]->py = -1;
		m->grid[i]->linha = NULL;
		m->grid[i]->coluna = m->grid[i];
	}


	return m;
}

void completar_matriz(struct matriz *m, int px, int py, float valor) {
	struct elemento * novo, *anterior, *proximo;
	if(px <= m->linhas && py <= m->colunas) {
		anterior = m->grid[px];
		
		novo = malloc(sizeof(struct elemento));
		novo->px = px;
		novo->py = py;
		novo->valor = valor;

		if(anterior->linha == anterior) {//Linha vazia
			anterior->linha = novo;
			novo->linha = anterior;
		} else {
			proximo = anterior;
			anterior = anterior->linha;
			while(px < anterior->px) {
				anterior = anterior->linha;
			}
			while(proximo->linha != anterior) {
				proximo = proximo->linha;
			}
			novo->linha = anterior;
			proximo->linha = novo;
		}
	}
		
	return;
}

void liberar_matriz(struct matriz * m) {

	liberar_lc(m, 0, m->linhas);
	liberar_lc(m, m->linhas, m->linhas + m->colunas);

	free(m);

	return;
}
void liberar_lc (struct matriz *m, int ini, int fim) {
	int i = ini;
	struct elemento *alvo, *inicio, *anterior;

	for(i = ini; i < fim; i++) {
		inicio = m->grid[i];
		alvo = inicio;
		while(alvo->linha != inicio) {
			anterior = alvo->linha;
			free(alvo);
			alvo = anterior;
		}
		free(alvo);
	}
	return;
}
