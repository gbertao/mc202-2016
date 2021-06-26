#include<stdio.h>
#define MAX 10050

typedef struct heap {
	int fila[MAX];
	int capacidade;
	int tamanho;
}CACHE;

void criar_fila(CACHE * c, int n);
int procurar_cache(CACHE * c, int arq);
void inserir_cache(CACHE * c, int arq);
void aumentar_prioridade(CACHE * c, int posicao);

int main (void) {
	CACHE cache;
	int c, n, a, i, arq, r, solucao = 0;

	scanf("%d %d %d", &c, &n, &a);

	criar_fila(&cache, c);

	for(i = 0; i < a; i++) {
		scanf(" %d", &arq);
		
		r = procurar_cache(&cache, arq);

		if(r >= cache.tamanho) {
			inserir_cache(&cache, arq);
			solucao++;
		} else {
			aumentar_prioridade(&cache, r);
		}
	}
	
	printf("%d\n", solucao);

}

void criar_fila(CACHE * c, int n) {
	c->tamanho = 0;
	c->capacidade = n;
}

int procurar_cache(CACHE * c, int arq) {
	int i, menor;

	if(c->tamanho < c->capacidade) {
		menor = c->tamanho;
	} else {
		menor = c->capacidade;
	}

	for(i = 0; i < menor; i++) {
		if(c->fila[i] == arq) {
			break;
		}
	}

	return i;
}

void inserir_cache(CACHE * c, int arq) {
	int i = 0, menor;
	
	if(c->tamanho < c->capacidade) {
		menor = c->tamanho;
	} else {
		menor = c->capacidade;
	}

	for(i = menor; i > 0; i--) {
		c->fila[i] = c->fila[i - 1];
	}

	c->fila[i] = arq;
	if(c->tamanho < c->capacidade) {
		(c->tamanho)++;
	}
}

void aumentar_prioridade(CACHE * c, int posicao) {
	int valor, i;

	valor = c->fila[posicao];

	for(i = posicao; i > 0; i--) {
		c->fila[i] = c->fila[i - 1];
	}

	c->fila[i] = valor;
}
