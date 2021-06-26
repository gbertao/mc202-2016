#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main (void) {
	int n, d, i = 0, j = 0, k = 0;
	float *pontos, *centroide, *componentes, soma = 0, distancia = 0;

	//Dimensão
	printf("Dimensões: ");
	scanf(" %d", &d);

	//Numero de pontos
	printf("Pontos: ");
	scanf(" %d", &n);

	//Pontos
	pontos = (float*)malloc(sizeof(float) * d * n);

	while(i < n) {
		while(j < d) {
			scanf(" %f", &pontos[k++]);
			j++;
		}
		i++;
		j = 0;
	}

	//centroide
	centroide = (float*)malloc(sizeof(float) * d);
	for(i = 0; i < d; i++) {
		centroide[i] = 0;
	}

	k = 0;
	for(i = 0; i < n; i++) {
		for(j = 0; j < d; j++) {
			centroide[d] = centroide[d] + pontos[k++];
		}
	}
	for(i = 0; i < d; i++) {
		centroide[d] = centroide[d] / n;
	}

	//Soma das distancias
	componentes =(float*) malloc(sizeof(float) * d);

	k = 0;
	for(i= 0; i < n; i++) {
		for(j = 0; j < d; j++) {
			componentes[d] = centroide[d] - pontos[k++];
			componentes[d] = componentes[d] * componentes[d];
			soma = soma + componentes[d];
		}
		distancia = distancia + sqrt(soma);
	}
	printf("Centroide:\n");
	for(i = 0; i < d; i++) {
		printf("Cordenada %d: %f.\n", i, centroide[i]);
	}
	printf("Soma das Distancias: %f\n", distancia);

	free(pontos);
	free(centroide);
	free(componentes);
	return 0;
}
