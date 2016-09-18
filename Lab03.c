//Lab 03 - Matrioskha - Giovanni Bertão - ra173325 - mc202ef
//Programa:
//

#include<stdio.h>
#include<stdlib.h>

//Estruturas
typedef enum {vermelho, azul} COR;
typedef struct matri {
	int valor, N;
	COR cor;
	struct matri * prox;
} MATRI;

//Assinatura de funcoes
void iniciar (MATRI ** p);
int validade (MATRI ** p, int x);
void push (MATRI ** p, int x);
int produzir(MATRI ** p, MATRI ** c);
void pop (MATRI ***p);
COR cor_matri(int M, int N);
void imprimir (MATRI ** c);
void liberar (MATRI ** p);

int main (void) {
	//Variaveis
	MATRI *pilha, *catalogo;
	int n, x, ok = 1;

	iniciar(&pilha);
	iniciar(&catalogo);

	scanf(" %d", &n);

	//Completar Lista
	do {
		scanf(" %d", &x);
		
		if(pilha == NULL) {//Se pilha vazia
			push(&pilha, x);
		} else {
			ok = validade(&pilha, x);
			if(ok) {//se o movimento eh permitido
				if(pilha->valor != -x) {
					push(&pilha, x);
				} else {
					ok = produzir(&pilha, &catalogo);
				}
			} else {
				n--;
				while(n > 0) {
					scanf(" %*d");
					n--;
				}
			}
		}
		n--;
	} while(n > 0 && ok != 0);

	//Saida - Se todos os itens foramadicionos e nenhum ficou "pela metade"
	if(ok && pilha == NULL) {
		printf("sequencia valida pode ser colorida\n");
		imprimir(&catalogo);
	} else {
		printf("sequencia invalida ou nao pode colorir\n");
	}

	//Liberar Memoria alocada dinamicamente
	if(pilha != NULL) {
		liberar(&pilha);
	}
	if(ok) {
		liberar(&catalogo);
	}

	return 0;
}
//Funcao: Iniciar estrutura
void iniciar (MATRI ** p) {

	*p = NULL;

	return;
}

//Funcao: Verificar se movimento é valido, retorna 0 ou 1.
int validade (MATRI ** p, int x) {
	int r;
	if(x > 0) {
		if((*p)->valor != -x) {
			r = 0;
		} else {
			r = 1;
		}
	} else {
		r = 1;
	}
	return r;
}

//Funcao: Inserir elemento na pilha
void push (MATRI ** p, int x) {
	MATRI * novo;

	novo = malloc(sizeof(MATRI));
	novo->valor = x;
	novo->prox = *p;
	*p = novo;

	return;
}

//Funcao: Remover elemento da pilha
void pop (MATRI ***p) {
	MATRI * a;

	a = **p;
	**p = (**p)->prox;
	
	free(a);

	return;
}

//Funcao: retorna 0 ou 1 se a matrioska é valida
int produzir(MATRI ** p, MATRI ** c) {
	MATRI * cat, * ant, * nova;
	COR corM;
	
	cat = *c;
	ant = NULL;

	//Procurar matrioska no catalogo
	if(cat == NULL) {//catalogo vazio
		nova = malloc(sizeof(MATRI));
		nova->valor = -(*p)->valor;
		nova->prox = NULL;
		nova->cor = cor_matri(nova->valor, (*p)->N);
		
		*c = nova;
		
		pop(&p);
		
		if(nova->cor == azul) {
			if((*p) != NULL) {
				(*p)->N++;
			}
		}

		return 1;
	} else {
		while(cat->valor <= -(*p)->valor) {
			if(cat->valor == -(*p)->valor) {//Verificar cor dupla
				corM = cor_matri(-(*p)->valor, (*p)->N);
				if(corM != cor_matri(cat->valor, cat->N)) {
					return 0;
				} else {
					pop(&p);
					if(corM == azul) {
						if(((*p)) != NULL) {
							((*p))->N++; 
						}
					}
					return 1;
				}
			} else {
				ant = cat;
				cat = cat->prox;
				if(cat == NULL) {//Final da lista
					break;
				}
			}
		}

		//Adicionar no catalogo
		nova = malloc(sizeof(MATRI));
		nova->valor = -(*p)->valor;
		nova->cor = cor_matri(nova->valor, (*p)->N);
		nova->prox = cat;
		if(ant != NULL) {
			ant->prox = nova;
		} else {
			*c = nova;
		}

		//Remover da pilha
		pop(&p);

		if(nova->cor == azul) {
			if((*p) != NULL) {
				(*p)->N++;
			}
		}


		return 1;
	}

}

//Funcao: Calcula o tipo da cor da matrioska
COR cor_matri(int M, int N) {
	if((M + N) % 2 == 0) {
		return azul;
	} else {
		return vermelho;
	}
}

//Funcao: Imprimir todas as matrioskas registradas
void imprimir(MATRI ** c) {
	MATRI * printer;
	printer = *c;

	while(printer != NULL) {
		printf("%d: ", printer->valor);
		switch(printer->cor) {
			case azul:
				printf("azul\n");
				break;
			case vermelho:
				printf("vermelho\n");
				break;
			default:
				break;
		}
		printer = printer->prox;
	}
	return;
}

//Funcao: Liberar memoria alocada
void liberar (MATRI ** p) {
	MATRI * a;

	do {	
		a = *p;
		*p = (*p)->prox;
		free(a);
	} while(*p != NULL);

	return;
}
