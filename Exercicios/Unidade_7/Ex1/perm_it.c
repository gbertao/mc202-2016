#include<stdio.h>
#include<stdlib.h>

typedef enum {chama, retorna} CHAMADA;
typedef struct memo {
	int m, i;
	CHAMADA ch;
}MEMORIA;
typedef struct pilha {
	MEMORIA *mem;
	int topo;
}PILHA;
void troca(int * a, int * b) {
	int  aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

int valido(int v[], int m) {
	int lin, i;
	if(m > 0) {
		lin = v[m-1];
		for(i = 0; i < m - 1; i++) {
			if((m - 1) - i == abs(lin - v[i])) {
				return 0;
			}
		}
	}
	return 1;
}

void permutar (int vetor[], int m, int n) {
	PILHA *p;
	p=malloc(sizeof(PILHA));
	p->mem = malloc(sizeof(MEMORIA) * (n + 1));
	p->topo = 0;
	
	p->mem[p->topo].ch = chama;
	p->mem[p->topo].m = 0;
	p->mem[p->topo].i = 0;

	(p->topo)++;
	while(p->topo) {
		if(p->mem[p->topo - 1].ch == chama) {
			if(p->mem[p->topo - 1].m == n) {
				printf("OK\n");
				(p->topo)--;
				p->mem[p->topo - 1].ch = retorna;
			} else {
				troca(&vetor[p->mem[p->topo - 1].m], &vetor[p->mem[p->topo - 1].i]);
				p->mem[p->topo].m = p->mem[p->topo - 1].m + 1;
				p->mem[p->topo].i = p->mem[p->topo].m;
				p->mem[p->topo].ch = chama;
				(p->topo)++;
			}
		} else {
			troca(&vetor[p->mem[p->topo - 1].m], &vetor[p->mem[p->topo - 1].i]);
			(p->mem[p->topo - 1].i)++;
			if(p->mem[p->topo - 1].i >= n) {
				(p->topo)--;
				if(p->topo) {
					p->mem[p->topo - 1].ch = retorna;
				}
			} else {
				p->mem[p->topo - 1].ch = chama;
			}
		}
	}
	free(p->mem);
	free(p);
	/*int i;
	if(valido(vetor, m)) {
		if (n == m) {
			// todo vetor fixo, só há uma combinação
			printf("OK\n");
		} else {
			for (i = m; i < n; i++) {
				troca(&vetor[m], &vetor[i]);
				//troca e fixa
				permutar(vetor, m + 1, n);
				// permuta o resto
				troca(&vetor[m], &vetor[i]);
				//volta ao original
			}
		}
	}*/
}


int main (void) {
	int *v, n, i;

	scanf("%d", &n);

	v = malloc(sizeof(int) * n);

	for(i = 0; i < n; i++) {
		v[i] = i+1;
	}

	permutar(v, 0, n);

	free(v);
	return 1;
}
