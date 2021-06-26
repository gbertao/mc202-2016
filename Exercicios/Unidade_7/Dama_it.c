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

int existe_solucao (int v[], int n);
void push (PILHA *p, VARIAVEIS * va);
void pop (PILHA * p);
int eh_disposicao_valida(int v[], int n);
int eh_prefixo_valido (int v[], int m);

int main (void) {
	int n, *v;
	scanf(" %d", &n);
	v = (int *) malloc(sizeof(int) * n);

	if(existe_solucao(v, n)) {
		printf("Existe solucao\n");
	} else {
		printf("Não existe solucao\n");
	}

	free(v);

	return 0;
}

int existe_solucao (int v[], int n) {
	int sol = 0;
	PILHA *p;
	VARIAVEIS *varis;
	
	//Inicializacoes
	p = malloc(sizeof(PILHA));
	p->topo = 0;
	varis = malloc(sizeof(VARIAVEIS) * (n + 1));

	p->vari = varis;
	p->vari[p->topo].m = 0;
	p->vari[p->topo].i = 1;
	p->vari[p->topo].ch = chama;
	(p->topo)++;

	while(p->topo) {
		if(p->vari[p->topo - 1].ch == chama) {
			if(p->vari[p->topo - 1].m == n) {
				if(eh_disposicao_valida(v,n)){
					sol = 1;
					p->topo = 0;
				} else {
					pop(p);
					p->vari[p->topo].m = p->vari[p->topo - 1].m;
					p->vari[p->topo].i = p->vari[p->topo - 1].i;
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				}
			} else {
				if(!eh_prefixo_valido(v, p->vari[p->topo - 1].m)) {
					pop(p);
					p->vari[p->topo].m = p->vari[p->topo - 1].m;
					p->vari[p->topo].i = p->vari[p->topo - 1].i;
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				} else {
					if(p->vari[p->topo - 1].m < n) {
						v[p->vari[p->topo - 1].m] = p->vari[p->topo - 1].i;
						p->vari[p->topo].m = p->vari[p->topo - 1].m + 1;
						p->vari[p->topo].i = 1;
						p->vari[p->topo].ch = chama;
						(p->topo)++;
					} else {
						pop(p);
						p->vari[p->topo].m = p->vari[p->topo - 1].m;
						p->vari[p->topo].i = p->vari[p->topo - 1].i;
						p->vari[p->topo].ch = retorna;
						(p->topo)++;
					}
				}
			}
		} else {
			pop(p);
			if(p->topo) {
				(p->vari[p->topo - 1].i)++;
				if(p->vari[p->topo -1].i > n) {
					pop(p);
					p->vari[p->topo].m = p->vari[p->topo - 1].m;
					p->vari[p->topo].i = p->vari[p->topo - 1].i;
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				}
			}
		}
	}

	//Free
	free(varis);
	free(p);

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
