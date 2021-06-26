//Lab 03 - Matrioskha - Giovanni Bertão - ra173325 - mc202ef
//Programa: O programa recebe um inteiro N e uma sequencia de N números(representando as matrioskas);
//			Usando estrutura de dados pilha para armazenar a representação das matrioscas e lista ligada
//			 para "catalogar" os brinquedos, o programa codifica as caracteristicas de cada brinquedo;
//			O programa retorna se é possivel fabricar os brinquedos. Se sim, ele imprime a cor de cada tipo em ordem.

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
			if(catalogo != NULL) {//Impede 2 bonecas fora de 1 maior
				ok = 0;
				n--;
				while(n > 0) {
					scanf(" %*d");
					n--;
				}
			}
		} else {
			ok = validade(&pilha, x);//se o movimento eh permitido: ok = 1
			if(ok) {
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

	//Saida - Se todos os itens foram adicionos e nenhum ficou "pela metade"
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
	if(catalogo != NULL) {
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
	novo->N = 0;
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

//Funcao: verifica se as configuracoes de matrioska sao validas ou se ja existem;
//		  adiciona matrioska no catologo em ordem;
//		  retorna 0 ou 1 se foi possivel adicionar ou nao.
int produzir(MATRI ** p, MATRI ** c) {
	MATRI * cat, * ant, * nova;
	COR corM;
	
	cat = *c;
	ant = NULL;

	//Procurar matrioska no catalogo
	if(cat == NULL) {//catalogo vazio
		nova = malloc(sizeof(MATRI));
		nova->valor = -(*p)->valor;
		nova->N = (*p)->N;
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
				if(corM != cat->cor) {
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
		nova->N = (*p)->N;
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
