#include<stdio.h>
#include<stdlib.h>

struct lista {
	int valor;
	struct lista * prox;
};

int main (void) {
	struct lista *inicio, *novo, *ultimo;
	int n;

	inicio = NULL;
	scanf("%d", &n);

	while(n > 0) {
		novo = malloc(sizeof(struct lista));
		scanf(" %d", &novo->valor);
		if(inicio == NULL) {
			novo->prox = NULL;
			inicio = novo;
		} else {
			ultimo = inicio;
			while(ultimo->prox != NULL) {
				ultimo = ultimo->prox;
			}
			ultimo->prox =novo;
			novo->prox =NULL;
		}
	}

	return 0;
}
