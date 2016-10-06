/* Lab 04 - Damas e Sudoku - Giovanni Bertao - ra173325- mc202ef
 * Funcionamento: O programa recebe uma entrada N seguida de uma matriz NxN;
 * 				  O programa utiliza técnica de backtracking e simula as recursoes utilizando iteracao;
 * 				  A recursao e simulada afim de ganhar tempo de execucao;
 * 				  O programa retorna se e possivel ou não anexar as N rainhas no tabuleiro.
 */

#include<stdio.h>
#include<stdlib.h>

//Estruturas
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
typedef struct damas {
	int linha;
	char valor;
} DAMAS;

//Assinatura de Funcoes
int existe_solucao (char ** m, DAMAS v[], int n);
void remove_topo (PILHA * p);
int eh_disposicao_valida(DAMAS v[], int n);
int eh_prefixo_valido (DAMAS v[], int m);

int main (void) {
	//Variaveis
	int n, i, j;
	char **m, elemento;
	DAMAS *v;

	scanf(" %d", &n);

	v = malloc(sizeof(DAMAS) * n);
	
	m = malloc(sizeof(char*) * n);
	for(i = 0; i < n; i++) {
		m[i] = malloc(sizeof(char) * n);
	}

	//Preencher matriz
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			scanf(" %c", &elemento);
			if(n <= 9) {
				elemento = elemento + '0';
			}
			m[i][j] = elemento;
		}
	}

	//Processamento e saida
	if(existe_solucao(m, v, n)) {
		printf("Tem solucao.\n");
	} else {
		printf("Sem solucao.\n");
	}

	//Liberar Memoria alocada dinamicamente
	for(i = 0; i < n; i++) {
		free(m[i]);
	}
	free(m);
	free(v);

	return 0;
}

//Funcao: Opera sobre as entrada, simulando recursao usando iteracao e uma pilha, devolve 0 ou 1
int existe_solucao (char ** m, DAMAS v[], int n) {
	int sol = 0;
	PILHA *p;
	VARIAVEIS *varis;
	
	//Inicializacoes e atribuicoes iniciais
	p = malloc(sizeof(PILHA));
	p->topo = 0;
	varis = malloc(sizeof(VARIAVEIS) * (n + 1));

	p->vari = varis;
	p->vari[p->topo].m = 0;
	p->vari[p->topo].i = 1;
	p->vari[p->topo].ch = chama;
	(p->topo)++;

	//Simula recursao
	while(p->topo) {//Enquanto existir uma chamada na pilha de execucao
		if(p->vari[p->topo - 1].ch == chama) {
			if(p->vari[p->topo - 1].m == n) {//Caso base: ultima coluna
				if(eh_disposicao_valida(v,n)){
					sol = 1;
					p->topo = 0;
				} else {
					remove_topo(p);
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				}
			} else {
				if(!eh_prefixo_valido(v, p->vari[p->topo - 1].m)) {//Backtracking
					remove_topo(p);
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				} else {
					if(p->vari[p->topo - 1].m < n) {//Fixa posicao e parte para outra coluna
						v[p->vari[p->topo - 1].m].linha = p->vari[p->topo - 1].i;
						v[p->vari[p->topo - 1].m].valor = m[p->vari[p->topo - 1].m][p->vari[p->topo - 1].i - 1];

						p->vari[p->topo].m = p->vari[p->topo - 1].m + 1;
						p->vari[p->topo].i = 1;
						p->vari[p->topo].ch = chama;
						(p->topo)++;
					} else {
						remove_topo(p);
						p->vari[p->topo].ch = retorna;
						(p->topo)++;
					}
				}
			}
		} else {//Volta da chamada recursiva(atributo de chamada = retorno)
			remove_topo(p);
			if(p->topo) {
				(p->vari[p->topo - 1].i)++;
				if(p->vari[p->topo -1].i > n) {
					remove_topo(p);
					p->vari[p->topo].ch = retorna;
					(p->topo)++;
				}
			}
		}
	}

	//Liberar memória alocada pela funcao
	free(varis);
	free(p);

	return sol;
}	

//Funcao: remover o topo da pilha de execucao, semelhante a retornar da chamada
void remove_topo (PILHA * p) {
	(p->topo)--;
	return;
}

//Funcao: Checa se a configuracao final eh uma solucao
int eh_disposicao_valida(DAMAS v[], int n) {
	int fat = 1, i, calc = 1;
	
	for(i = 2; i <= n; i++) {
		fat = fat * i;
	}

	for(i = 0; i < n; i++) {
		calc = calc * v[i].linha;
	}

	if(calc == fat) {//Se a pricipio cada dama esta em uma linha
		if(eh_prefixo_valido(v, n)) {
			return 1;
		}
	}
	return 0;
}

//Funcao: Analisa se o prefixo eh valido, analisa se existe linhas, colunas ou valores  conhecidentes.
//(utilizado no backtracking)
int eh_prefixo_valido (DAMAS v[], int m) {
	int lin, i;
	char val;

	if(m >= 1) {
		lin = v[m-1].linha;
		val = v[m-1].valor;

		for(i = 0; i < m - 1; i++) {
			if(v[i].linha == lin) {
				return 0;
			}
			if((m - 1) - i == abs(lin - v[i].linha)) {
				return 0;
			}
			if(v[i].valor == val) {
				return 0;
			}
		}
	}

	return 1;
}
