#include<stdio.h>
#include<stdlib.h>

typedef enum {chama, retorna} CHAMADA;
typedef struct variaveis {
	int m;
	int i;
	CHAMADA ch;
} VARIAVEIS;
typedef struct pilha {
	VARIAVEIS * vari;
	int topo;
} PILHA;

int existe_solucao (int n);
void push (PILHA *p, VARIAVEIS * va);
void pop (PILHA * p);
int eh_disposicao_valida(int v[], int n);
int eh_prefixo_valido (int v[], int m);
void liberar(PILHA *p, int n);

int main (void) {
	int n;
	scanf(" %d", &n);
	
	if(existe_solucao(n)) {
		printf("Existe solucao\n");
	} else {
		printf("Não existe solucao\n");
	}

	return 0;
}

int existe_solucao (int n) {
	int *v, sol = 0;
	PILHA *p;
	VARIAVEIS *va;
	
	//Inicializacoes
	p = malloc(sizeof(PILHA));
	p->topo = 0;
	p->vari = malloc(sizeof(VARIAVEIS) * n + 1);

	va = malloc(sizeof(VARIAVEIS));
	va->m = 0;
	va->i = 1;
	va->ch = chama;

	push(p, va);
	free(va);

	v = malloc(sizeof(int) * n);

	while(p->topo) {
		if(p->vari[p->topo - 1].ch == chama) {
			if(p->vari[p->topo - 1].m == n) {
				if(eh_disposicao_valida(v,n)){
					sol = 1;
					p->topo = 0;
				} else {
					pop(p);
					va = malloc(sizeof(VARIAVEIS));
					va->m = p->vari[p->topo - 1].m;
					va->i = p->vari[p->topo - 1].i;
					va->ch = retorna;
					push(p, va);
					free(va);
				}
			} else {
				if(!eh_prefixo_valido(v, p->vari[p->topo - 1].m)) {
					pop(p);
					va = malloc(sizeof(VARIAVEIS));
					va->m = p->vari[p->topo - 1].m;
					va->i = p->vari[p->topo - 1].i;
					va->ch = retorna;
					push(p, va);
					free(va);
				} else {
					if(p->vari[p->topo - 1].m < n) {
						v[p->vari[p->topo - 1].m] = p->vari[p->topo - 1].i;
						va = malloc(sizeof(VARIAVEIS));
						va->m = p->vari[p->topo - 1].m + 1;
						va->i = 1;
						va->ch = chama;
						push(p, va);
						free(va);
					} else {
						pop(p);
						va = malloc(sizeof(VARIAVEIS));
						va->m = p->vari[p->topo - 1].m;
						va->i = p->vari[p->topo - 1].i;
						va->ch = retorna;
						push(p, va);
						free(va);
					}
				}
			}
		} else {
			pop(p);
			if(p->topo) {
				(p->vari[p->topo - 1].i)++;
				if(p->vari[p->topo -1].i > n) {
					pop(p);
					va = malloc(sizeof(VARIAVEIS));
					va->m = p->vari[p->topo - 1].m;
					va->i = p->vari[p->topo - 1].i;
					va->ch = retorna;
					push(p, va);
					free(va);
				}
			}
		}
	}

	//Free
	liberar(p, n);
	//free(v);

	return sol;
}	

void push (PILHA *p, VARIAVEIS * va) {
	p->vari[p->topo] = * va;
	(p->topo)++;
	return;
}

void pop (PILHA * p) {
	(p->topo)--;
	return;
}

int eh_disposicao_valida(int v[], int n) {
	int fat = 1, i, calc = 1;
	
	for(i = 2; i <= n; i++) {
		fat = fat * i;
	}

	for(i = 0; i < n; i++) {
		calc = calc * v[i];
	}

	if(calc == fat) {
		if(eh_prefixo_valido(v, n)) {
			return 1;
		}
	}
	return 0;
}

int eh_prefixo_valido (int v[], int m) {
	int lin, i;
	
	if(m >= 1) {
		lin = v[m-1];
	}

	for(i = 0; i < m - 1; i++) {
		if(v[i] == lin) {
			return 0;
		}
		if((m - 1) - i == abs(lin - v[i])) {
			return 0;
		}
	}

	return 1;
}

void liberar(PILHA *p, int n) {
	free(p);
	return;
}
