#include<stdio.h>
#include<stdlib.h>

void ordenar(int numeros[], int ini, int fim, int total);
void intercalar(int numeros[], int inicio, int meio, int fim, int total);
int main (void) {
	FILE *arq, *arq2;
	int n, *numeros, i, valor, k = 1;

	arq = fopen("numeros.txt", "r");
	arq2 = fopen("saida.txt", "w");

	fscanf(arq, " %d", &n);

	numeros = malloc(sizeof(int) * n);

	for(i = 0; i < n; i++) {
		fscanf(arq, " %d", &numeros[i]);
	}
	//ordenar vetor
	ordenar(numeros, 0, n, n);

	//imprimir
	valor = numeros[0];
	for(i = 1; i < n; i++) {
		if(valor != numeros[i]) {
			fprintf(arq2, "Numero de vezes %d: %d\n", valor, k);
			valor = numeros[i];
			k = 1;
		} else {
			k++;
		}
	}
	fprintf(arq2, "Numero de vezes %d: %d\n", valor, k);

	fclose(arq);
	fclose(arq2);
	free(numeros);

	return 0;
}

void ordenar(int numeros[], int ini, int fim, int total) {
	int meio;

	if(ini < fim) {
		meio = (ini + fim) /2;
		ordenar(numeros, ini, meio, total);
		ordenar(numeros, meio + 1, fim, total);
		intercalar(numeros, ini, meio, fim, total);
	}
	return;
}

void intercalar(int numeros[], int inicio, int meio, int fim, int total) {
	int *aux;
	int i = inicio, j = meio + 1, k = 0;

	aux = malloc(sizeof(int) * total);

	while(i <= meio && j <= fim) {
		if(numeros[i] <= numeros[j]) {
			aux[k++] = numeros[i++];
		} else {
			aux[k++] = numeros[j++];
		}
	}

	while(i <= meio) {
		aux[k++] = numeros[i++];
	}
	while(j <= fim) {
		aux[k++] = numeros[j++];
	}

	for(i = inicio, k = 0; i <= fim; i++, k++) {
		numeros[i] = aux[k];
	}

	free(aux);

	return;
}
