#include<stdio.h>
#include<stdlib.h>

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
			if(lin == v[i]) {
				return 0;
			}
			if((m - 1) - i == abs(lin - v[i])) {
				return 0;
			}
		}
	}
	return 1;
}

void permutar (int vetor[], int m, int n) {
	int i;
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
}

int main (void) {
	int *v, n, i;

	scanf("%d", &n);

	v = malloc(sizeof(int) * n);

	for(i = 0; i < n; i++) {
		v[i] = i;
	}

	permutar(v, 0, n);

	free(v);
	return 1;
}
