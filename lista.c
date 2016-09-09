#include<stdio.h>
#include<stdlib.h>

struct lista{
	int valor;
	struct lista *proximo;
};

//Assinatura
void liberar_lista(struct lista * inicio);
struct lista * procurar_lista(int n, struct lista * inicio);
void imprimir_lista(struct lista *comeco, struct lista *fim);

int main (void) {
	//Variaveis
	struct lista *inicio, *ultimo, *novo;
	struct lista *parte1, *parte2, *lista3;
	int dado, m, n , p;
	char c = 0;

	inicio = NULL;

	while(c != '\n' && c != '\r' ) {
		scanf("%d%c", &dado, &c);
		novo = (struct lista*)malloc(sizeof(struct lista));
		novo->valor = dado;
		novo->proximo = NULL;

		if(inicio == NULL) {
			inicio = novo;
		} else {
			ultimo = inicio;
			while(ultimo->proximo != NULL) {
				ultimo = ultimo->proximo;
			}

			ultimo->proximo = novo;
			ultimo = novo;
		}
		
	}

	scanf(" %d %d %d", &m, &n, &p);


	//Original
	printf("original ");
	imprimir_lista(inicio, ultimo);
	printf("\n");
	
	//Saida
	printf("m=%d, n=%d, p=%d\n", m, n, p);

	//Primeira Lista
	parte1 = procurar_lista(m, inicio);
	if(parte1 == NULL) {
		parte1 = inicio;
	}
	parte2 = procurar_lista(n, parte1);
	if(parte2 == NULL) {
		parte2 = procurar_lista(p, parte1);
		if(parte2 == NULL) {
			parte2 = ultimo;
		}
	}
	printf("primeira ");
	imprimir_lista(parte1, parte2);
	printf("\n");
	
	//Segunda Lista
	parte1 = procurar_lista(n, parte1);
	if(parte1 == NULL) {
		parte1 = procurar_lista(m, inicio);
		if(parte1 == NULL) {
			parte1 = inicio;
		}
	}
	parte2 = procurar_lista(p, parte1);
	if(parte2 == NULL) {
		parte2 = ultimo;
	}
	printf("segunda ");
	imprimir_lista(parte1, parte2);
	printf("\n");

	//Terceira Lista
	lista3 = procurar_lista(p, parte2);
	if(lista3 == NULL) {
		lista3 = procurar_lista(n, parte1);
		if(lista3 == NULL) {
			lista3 = procurar_lista(m, inicio);
			if(lista3 == NULL) {
				lista3 = inicio;
			}
		}
	} else {
		parte2 = ultimo;
	}

	printf("terceira ");
	imprimir_lista(lista3, parte2);
	printf("\n");

	liberar_lista(inicio);

	return 0;
}

void liberar_lista(struct lista * inicio) {
	struct lista * alvo;

	alvo = inicio;

	while(inicio->proximo != NULL) {
		inicio = inicio->proximo;
		free(alvo);
		alvo = inicio;
	}
	free(inicio);
	return;
}

struct lista * procurar_lista(int n, struct lista * inicio) {
	struct lista *endereco;

	endereco = inicio;

	while(endereco != NULL) {
		if(endereco->valor == n) {
			break;
		} else {
			endereco = endereco->proximo;
		}
	}

	return endereco;
}

void imprimir_lista(struct lista *comeco, struct lista *fim) {
	struct lista * printer;
	printer = comeco;
	do {
		printf("%d ", printer->valor);
		printer = printer->proximo;		
	}while(printer != fim->proximo);

	return;
}
