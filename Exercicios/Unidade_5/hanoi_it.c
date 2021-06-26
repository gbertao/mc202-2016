//Atividade Unidade 5 - Hanoi iterativo - Giovanni Bertão - ra173325 -mc202ef
//Programa: Realiza hanoi iterativo para mover n peças de A para B.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef enum { fora, dentro1, dentro2} CHAMADA;//3 chamadas
typedef struct pilha {
	int n;
	char ori, dest, aux;
	CHAMADA end;
	struct pilha * prox;
} PILHA;

void hanoi (int n, char ori, char dest, char aux);
void push (PILHA ** p, int n, char ori, char dest, char aux, CHAMADA ca);
void pop (PILHA ** p);
void liberar(PILHA ** p);

int main (void) {
	//Variaveis
	int n;
	
	//Entrada
	printf("Digite o número de peças: ");
	scanf(" %d", &n);

	hanoi(n, 'A', 'B', 'C');

	return 0;
}

//Magica com pilha
void hanoi (int n, char ori, char dest, char aux) {
	int i = 0, k;
	PILHA * p;

	p = NULL;
	push(&p, n , ori, dest, aux, fora);
	k = pow(2, n) - 1;

	while( i < k) {
		if(p->n == 0) {
			pop(&p);
		} else {
			if(p->end == fora) {
				push(&p, p->n, p->ori, p->dest, p->aux, dentro1);//Guardar variaveis locais e chamar nova recursao
				push(&p, (p->n) - 1, p->ori, p->aux, p->dest, fora);//Valores que a nova chamada recebe
			} else if(p->end == dentro1) {//Retorna da primeira chamada
				printf("Mova de %c para %c\n", p->ori, p->dest);
				i++;
				pop(&p);
				push(&p, p->n, p->ori, p->dest, p->aux, dentro2);//Guardar variaveis BLAH ...
				push(&p, (p->n) - 1, p->aux, p->dest, p->ori, fora);//Valores que BLAH ...
			} else if (p->end == dentro2) {
				pop(&p);//Retorna da segunda chamada
				pop(&p);//Retorna da chamada que chamou a segunda chamada
			}
		}
	}

	if(p != NULL) {
		liberar(&p);
	}

	return;
}

void push (PILHA ** p, int n, char ori, char dest, char aux, CHAMADA ca) {
	PILHA * novo;
	novo = malloc(sizeof(PILHA));

	novo->n = n;
	novo->ori = ori;
	novo->dest = dest;
	novo->aux = aux;
	novo->end = ca;

	novo->prox = *p;
	*p = novo;
		
	return;
}

void pop (PILHA ** p) {
	PILHA * a;
	a = *p;
	*p = (*p)->prox;
	free(a);
}

void liberar(PILHA ** p) {
	PILHA * a;
	do{
		a = *p;
		*p = (*p)->prox;
		free(a);
	} while(*p != NULL);

	return;
}
