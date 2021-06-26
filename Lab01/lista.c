//Lab 01 - Lista - Giovanni Bertão ra173325 - MC202ef
//Funcionamento: O programa recebe duas linhas com uma sequencia de n números na primeira e 3 números na segunda;
//				 Apartir dessa sequencia o programa irá armazenar a primeira linha em formato de listaligada;
//				 Serão feitos testes utilizando a segunda linha para que o programa retorne 3 listas diferentes.

#include<stdio.h>
#include<stdlib.h>

//Estrutura de Dados
struct lista{
	int valor;
	struct lista *proximo;
};

//Assinatura de Funções
void inserir_lista(struct lista **inicio, struct lista **ultimo, int dado);
struct lista * procurar_lista(int n, struct lista * inicio);
void imprimir_lista(struct lista *comeco, struct lista *fim);
void liberar_lista(struct lista * inicio);

int main (void) {
	//Variaveis
	struct lista *inicio, *ultimo;
	struct lista *parte1, *parte2, *lista3;
	int dado, m, n , p;
	char c = 0;

	//Inicio da lista, ou seja a lista esta vazia
	inicio = NULL;

	//Entrada
	while(c != '\n' && c != '\r' ) {
		scanf("%d%c", &dado, &c);
		inserir_lista(&inicio, &ultimo, dado);
	}
	scanf(" %d %d %d", &m, &n, &p);

	//Saida
	//Original
	printf("original ");
	imprimir_lista(inicio, ultimo);
	printf("\n");
	
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

	//Liberar memória alocada
	liberar_lista(inicio);

	return 0;
}

//Função: Inserir dados
void inserir_lista(struct lista **inicio, struct lista **ultimo, int dado) {
	struct lista * novo;
	novo = malloc(sizeof(struct lista));
	novo->valor = dado;
	novo->proximo = NULL;

	if(*inicio == NULL) {
		*inicio = novo;
	} else {
		*ultimo = *inicio;
		while((*ultimo)->proximo != NULL) {
			*ultimo = (*ultimo)->proximo;
		}
		(*ultimo)->proximo = novo;
		*ultimo = novo;
	}
	return;
}

//Função: Procura na lista a primeira ocorrencia de n partindo do elemento apontado pelo ponteiro inicio,
//		  Se encontrar um valor de n, ela retorna o endereço do elemento que contem n.
//		  Se não encontrar, ela retorna NULL
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

//Função: Imprime os dados do ponteiro começo até o ponteiro fim
void imprimir_lista(struct lista *comeco, struct lista *fim) {
	struct lista * printer;
	printer = comeco;
	do {
		printf("%d ", printer->valor);
		printer = printer->proximo;		
	}while(printer != fim->proximo);

	return;
}

//Função: Libera a memória alocada na criação da lista
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
