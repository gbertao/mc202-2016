//Lab 02 - Lista - Giovanni Bertão ra173325 - MC202ef
//Funcionamento: O programa recebe N números que formam uma lista e M comandos;
//				 A lista é representada por uma lista ligada simples com nó cabeça;
//				 Seguindo dois algoritmos diferentes para o mesmo comando o programa calcula o custo de cada algoritmo;
//				 O programa imprime os custos e como ficou a lista de cada algoritmo.

#include<stdio.h>
#include<stdlib.h>

//Elementos da lista
typedef struct lista {
	int valor;
	struct lista *prox;
}LISTA;

//Assinatura de funções
LISTA * criar_lista();
void inserir_lista(LISTA * lista, int valor);
int aMTF(LISTA * lista, int chave);
int iMTF(LISTA * lista, int chave);
int aTR(LISTA * lista, int chave);
int iTR(LISTA *lista, int chave);
void transpose(LISTA * inicio, LISTA ** p);
int remover(LISTA * lista, int chave);
void imprimir_lista(LISTA * lista);
void liberar_lista(LISTA * lista);

int main (void) {
	//Variaveis
	LISTA *MTF, *TR;
	int N, R, i, valor, chave, custoMTF = 0, custoTR = 0;
	char c;

	//Criar listas
	MTF = criar_lista();
	TR = criar_lista();

	//Entrada
	scanf(" %d %d", &N, &R);

	for(i = 0; i < N; i++) {
		scanf(" %d", &valor);
		inserir_lista(MTF, valor);
		inserir_lista(TR, valor);
	}

	//Comandos e execução dos Algoritmos
	for(i = 0; i < R; i++) {
		scanf(" %c%d", &c, &chave);
		switch(c) {
			case 'a':
				custoMTF = custoMTF + aMTF(MTF, chave);
				custoTR = custoTR + aTR(TR, chave);
				break;
			case 'i':
				custoMTF = custoMTF + iMTF(MTF, chave);
				custoTR = custoTR + iTR(TR, chave);
				break;
			case 'r':
				custoMTF = custoMTF + remover(MTF, chave);
				custoTR = custoTR + remover(TR, chave);
				break;
			default:
				break;
		}
	}

	//Saida
	//MTF
	printf("%d\n", custoMTF);
	imprimir_lista(MTF);
	printf("\n");

	//TR
	printf("%d\n", custoTR);
	imprimir_lista(TR);
	printf("\n");


	//Liberar Memória
	liberar_lista(MTF);
	liberar_lista(TR);

	return 0;
}

//Função: Criar o nó dummy para iniciar a lista
LISTA * criar_lista() {
	LISTA * dummy;
	
	dummy = malloc(sizeof(LISTA));
	dummy->prox = NULL;

	return dummy;
}

//Função: Inserir valores iniciais na lista
void inserir_lista(LISTA * lista, int valor) {
	LISTA * novo;
	
	while(lista->prox != NULL) {
		lista = lista -> prox;
	}

	novo = malloc(sizeof(LISTA));
	novo->valor = valor;
	novo->prox = NULL;
	lista->prox = novo;
	
	return;
}

//Funções que seguem o algoritmo MTF
//Função: Acessar elemento da lista
int aMTF(LISTA * lista, int chave) {
	LISTA * p, *anterior;
	int custo = 1;
	
	p = lista->prox;
	anterior = lista->prox;

	if(p != NULL) {//Caso Lista vazia
		while(p->valor != chave) {
			custo++;
			p = p->prox;
			if(p == NULL) {//Caso arquivo não encontrado
				return custo;
			}
		}

		//Deslocar
		if(lista->prox != p) {
			while(anterior->prox != p) {
				anterior = anterior->prox;
			}
			anterior->prox = p->prox;
			p->prox = lista->prox;
			lista->prox = p;
		}
		return custo;
	}
	return 0;
}

//Função: Inserir novo elemento
int iMTF(LISTA * lista, int chave) {
	LISTA * final, * novo;
	int custo = 1;

	novo = malloc(sizeof(LISTA));
	novo->valor = chave;

	final = lista->prox;

	if(final == NULL) {
		lista->prox = novo;
		novo->prox = NULL;
	} else {
		while(final->prox != NULL) {
			custo++;
			final = final->prox;
		}
		custo++;
		novo->prox = final->prox;
		final->prox = novo;
	}

	return custo;
}

//Funcoes que seguem o algoritmo TR
//Função: acessar elemento da lista
int aTR(LISTA * lista, int chave) {
	LISTA * p;
	int custo = 1;

	p  = lista->prox;

	if(p != NULL) {//Lista não vazia
		while(p->valor != chave) {
			custo++;
			p = p->prox;
			if(p == NULL) {//Elemento nao pertence a lista
				return custo;
			}
		}

		if(lista->prox != p) {
			transpose(lista, &p);
		}

		return custo;
	}
	return 0;
}

//Função: Adicionar elemento
int iTR(LISTA *lista, int chave) {
	LISTA *final, *novo;
	int custo = 1;

	novo = malloc(sizeof(LISTA));
	novo->valor = chave;

	final = lista->prox;

	while(final->prox != NULL) {
		custo++;
		final = final->prox;
	}

	custo++;
	novo->prox = final->prox;
	final->prox = novo;

	transpose(lista, &novo);
	

	return custo;
}

//Função para transpor os elemento(Utilizada pelo algoritmo TR):
void transpose(LISTA * inicio, LISTA ** p) {
	LISTA *anterior, *aux;

	anterior = inicio->prox;

	while(anterior->prox != *p) {
		aux = anterior;
		anterior = anterior->prox;
	}
	
	if(inicio->prox->prox != *p) {
		aux->prox = (*p);
	} else {
		inicio->prox = *p;
	}

	anterior->prox = (*p)->prox;
	(*p)->prox = anterior;

	return;
}

//Função: Remover elemento da lista (Usada pelos 2 algoritmos):
int remover(LISTA * lista, int chave) {
	LISTA * p, *anterior;
	int custo = 1;

	p = lista->prox;

	if(p != NULL) {//Caso Lista vazia
		while(p->valor != chave) {
			anterior = p;
			p = p->prox;
			custo++;
			if(p == NULL) {//Caso elemento não seja encontrado
				return custo;
			}
		}
		if(lista->prox != p) {
			anterior->prox = p->prox;
		} else {
			lista->prox = p->prox;
		}

		free(p);

		return custo;
	}
	return 0;
}

//Função: Imprimir Lista
void imprimir_lista(LISTA * lista) {
	LISTA *printer;
	printer = lista->prox;

	while(printer != NULL) {
		printf("%d ", printer->valor);
		printer = printer->prox;
	}

	return;
}

//Função: Liberar a memória alocada ao montar a lista
void liberar_lista(LISTA * lista) {
	LISTA * alvo;

	do{
		alvo = lista;
		lista = lista->prox;
		free(alvo);
	} while(lista != NULL);

	return;
}
