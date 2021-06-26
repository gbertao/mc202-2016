/* Lab 04 - Damas e Sudoku - Giovanni Bertao - ra173325- mc202ef
 * Funcionamento: O programa recebe uma entrada N seguida de uma matriz NxN;
 * 				  O programa utiliza técnica de permutação e backtracking para encontrar uma solucao valida;
 * 				  O programa retorna se e possivel ou não anexar as N rainhas no tabuleiro.
 */

#include<stdio.h>
#include<stdlib.h>

//Estrutura
typedef struct damas {
	int linha;
	char valor;
} DAMAS;

//Assinatura de Funcoes
int existe_solucao (char ** m, int n);
void permutar(DAMAS v[], char **m, int fixo, int n, int * sol);
int eh_prefixo_valido (DAMAS v[], int fixo);
void trocar(DAMAS * a, DAMAS * b, char ** m, int fixo, int i);

int main (void) {
	//Variaveis
	int n, i, j;
	char **m, elemento;

	scanf(" %d", &n);

	
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
	if(existe_solucao(m, n)) {
		printf("Tem solucao.\n");
	} else {
		printf("Sem solucao.\n");
	}

	//Liberar Memoria alocada dinamicamente
	for(i = 0; i < n; i++) {
		free(m[i]);
	}
	free(m);

	return 0;
}

//Funcao: Cria um vetor de DAMAS e calcula uma se existe uma solucao para a configuracao da matriz m
int existe_solucao (char ** m, int n) {
	int sol = 0, i;
	DAMAS *v;

	v = malloc(sizeof(DAMAS) * n);

	for(i = 0; i < n; i++) {
		v[i].linha = i + 1;
		v[i].valor = m[v[i].linha - 1][i];
	}

	permutar(v, m, 0, n, &sol);

	//Liberar memória alocada pela funcao
	free(v);

	return sol;
}	

//Funcao: Permuta o vetor de DAMAS ate que encontrar uma solucao para o problema
void permutar(DAMAS v[], char **m, int fixo, int n, int * sol) {
	int i;
	if(eh_prefixo_valido(v, fixo)) {
		if(fixo == n) {
			*sol = 1;
		} else {
			for(i = fixo; i < n; i++) {
				trocar(&v[fixo], &v[i], m, fixo, i);
				permutar(v, m, fixo + 1, n, sol);
				trocar(&v[fixo], &v[i], m, fixo, i);//backtracking
			}
		}
	}
}

//Funcao: Verifica se o atual prefixo eh valido, garante que nao precisamos testar todas as configuracoes
int eh_prefixo_valido (DAMAS v[], int fixo) {
	int lin, i;
	char val;

	if(fixo >= 1) {
		lin = v[fixo-1].linha;
		val = v[fixo-1].valor;

		for(i = 0; i < fixo - 1; i++) {
			if((fixo - 1) - i == abs(lin - v[i].linha)) {
				return 0;
			}
			if(v[i].valor == val) {
				return 0;
			}
		}
	}

	return 1;
}

//Funcao: troca duas DAMAS de coluna e atualiza o valor de cada uma
void trocar(DAMAS * a, DAMAS * b, char ** m, int fixo, int i) {
	DAMAS aux;

	aux = *a;
	*a = *b;
	*b = aux;

	//Atualizar valor
	a->valor = m[a->linha - 1][fixo];
	b->valor = m[b->linha - 1][i];
}
