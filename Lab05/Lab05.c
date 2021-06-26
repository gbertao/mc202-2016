//Lab Semanal 05 - Arvore AVL - Giovanni Bertao - ra173325 - mc202ef
//Funcionamento: o programa recebe 3 comandos diferentes:
//				 touch - insere arquivo na arvore;
//				 rm - remove arquivo da arvore;
//				 ls - lista arquivos da arvore.
//				 Os comandos são utilizados em conjunto com o nome do arquivo que pode ser
//				 uma expressão regular;
//				 O programa utiliza uma arvore AVL.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Estrutura
typedef struct noArv {
	char arquivo[21];
	int copias;
	int fb;
	struct noArv *dir;
	struct noArv *esq;
} NOARV;

//Assinatura de funcoes
int touch (NOARV ** arv, char arq[]);
void balancear(NOARV ** arv);
void rotaciona_esquerda (NOARV ** arv);
void rotaciona_direita (NOARV ** arv);
int profundidade (NOARV * noh);
int maior (int x, int y);
void rm (char arq[], NOARV ** arv);
void remover_regex (char arq[], NOARV ** arv, int i);
void remover(NOARV ** arv, char arq[]);
void rem_caso1 (NOARV ** arv);
void rem_caso2(NOARV ** arv);
void ls (char arq[], NOARV ** arv);
void imprimir_tudo(NOARV * arv);
void imprimir_regex(NOARV * arv, char arq[], int i);
void imprimir(NOARV * arv);
NOARV * buscar (NOARV * arv, char arq[], int i);
void liberar(NOARV ** arv);

int main (void) {
	NOARV * arv;
	char cmd[6], arq[21];
		
	arv = NULL;

	//Entrada, processamento e saida
	while(scanf(" %s", cmd) != EOF) {
		scanf(" %s", arq);

		if(!strcmp(cmd, "touch")) {
			touch(&arv, arq);
		} else if(!strcmp(cmd, "rm")) {
			rm(arq, &arv);
		} else {
			ls(arq, &arv);
		}

	}

	//Liberar memoria alocada dinamicamente
	liberar(&arv);
	return 0;
}

//Funcao: insere um no na arvore avl e balanceia e sor necessario
int touch (NOARV ** arv, char arq[]) {
	int aumentou, r = 0;

	if(*arv == NULL) {//Caso base: no vazio
		(*arv) = malloc(sizeof(NOARV));
		strcpy((*arv)->arquivo, arq);
		(*arv)->copias = 1;
		(*arv)->esq = NULL;
		(*arv)->dir = NULL;
		(*arv)->fb = 0;
		return 1;
	} else {//Caso geral
		r = strcmp(arq, (*arv)->arquivo);
		if(r == 0) {//Caso ja exista um arquivo
			((*arv)->copias)++;
			return 0;
		} else if(r > 0) {//Caminha pela direita
			aumentou = touch(&((*arv)->dir), arq);
			if(aumentou) {//Se a altura da sub arvore foi alterada
				(*arv)->fb = profundidade((*arv)->dir) - profundidade((*arv)->esq);

				if((*arv)->fb > 1 || (*arv)->fb < -1) {
					balancear(arv);
					return 0;
				} else {
					return 1;
				}
			} else {
				return 0;
			}

		} else if(r < 0) {	//Caminha pela esquerda
			aumentou = touch(&((*arv)->esq), arq);
			if(aumentou) {
				(*arv)->fb = profundidade((*arv)->dir) - profundidade((*arv)->esq);

				if((*arv)->fb > 1 || (*arv)->fb < -1) {
					balancear(arv);
					return 0;
				} else {
					return 1;
				}
			} else {
				return 0;
			}
		}
	}
	return 0;
}

//Funcao: balanceia a arvore AVL apos uma remocao ou insercao
void balancear(NOARV ** arv) {

	while((*arv)->fb < -1 || (*arv)->fb > 1) {
		if((*arv)->fb < -1) {
			if((*arv)->esq->fb <= 0) {
				rotaciona_direita(arv);
			} else {
				rotaciona_esquerda(&((*arv)->esq));
				rotaciona_direita(arv);
			}
		} else {
			if((*arv)->dir->fb >= 0) {
				rotaciona_esquerda(arv);
			} else {
				rotaciona_direita(&((*arv)->dir));
				rotaciona_esquerda(arv);
			}
		}
	}
}

//Funcao: rotaciona o no para esquerda
void rotaciona_esquerda (NOARV ** arv) {
	NOARV *a, *b;
	int i;

	b = *arv;
	a = b->dir;

	b->dir = a->esq;
	a->esq = b;
	*arv = a;
	
	for(i = 0; i < 2; i++) {//recalcula o fator de balanceamento
		b->fb = profundidade(b->dir) - profundidade(b->esq);
		b = a;
	}
}

//Funcao: rotaciona o no para direita
void rotaciona_direita (NOARV ** arv) {
	NOARV *a, *b;
	int i;

	b = *arv;
	a = b->esq;

	b->esq = a->dir;
	a->dir = b;
	*arv = a;
	
	for(i = 0; i < 2; i++) {//recalcula fb
		b->fb = profundidade(b->dir) - profundidade(b->esq);
		b = a;
	}
}

//Funcao: auxilia na aquisicao do tamanho de uma subarvore
int profundidade (NOARV * noh) {
	int x = 0;
	if(noh == NULL) {
		return 0;
	} else {
		x = maior(profundidade(noh->esq), profundidade(noh->dir)) + 1;
	}
	return x;
}

//Funcao: retornao maior entre 2 numeros
int maior (int x, int y) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}

//Funcao: Encontra o tipo de remocao e o aplica
void rm (char arq[], NOARV ** arv) {
	int i = 0;
	NOARV * busca;

	//Checar existencia de *
	while(arq[i] != '\0') {
		if(arq[i] == '*') {
			break;
		}
		i++;
	}

	if(i == 0) {//Apagar tudo
		if(*arv) {
			liberar(arv);
		} else {
			printf("nao existem arquivos com essa expressao\n");
		}
	} else if (i < strlen(arq)) {//Regex
		busca = buscar(*arv, arq, i);
		if(busca == NULL) {
			printf("nao existem arquivos com essa expressao\n");
		} else {
			do {//Loop garante remocao de todos os arquivos compativeis com o regex
				busca = buscar(*arv, arq, i);
				if(busca != NULL) {
					remover(&busca, busca->arquivo);
				} else {
					break;
				}
			} while(!0);
		}
	} else {//Sem * -> remocao normal
		busca = buscar(*arv, arq, i);
		if(busca) {
			remover(arv, arq);
		} else {
			printf("nao existem arquivos com essa expressao\n");
		}
	}
}

//Funcao: remove um no da arvore AVL e a balanceia
void remover(NOARV ** arv, char arq[]) {
	if(*arv == NULL) {
		return;
	}

	//Remover normalmente
	while(strcmp(arq, (*arv)->arquivo) != 0) {
		if(strcmp(arq, (*arv)->arquivo) < 0) {
			arv = &(*arv)->esq;
		} else {
			arv = &(*arv)->dir;
		}
	}

	//Caso1 = 1 ou 0 filhos; Caso 2 = 2 filhos
	if((*arv)->dir == NULL || (*arv)->esq == NULL){
		rem_caso1(arv);
	} else {
		rem_caso2(arv);
	}

	//Balancear
	if(*arv == NULL) {
		return;
	} else {
		(*arv)->fb = profundidade((*arv)->dir) - profundidade((*arv)->esq);
		if((*arv)->fb > 1 || (*arv)->fb < -1) {
			balancear(arv);
		}
	}
}

//Funcao: remove um no caso ele tenha 1 ou 0 filhos
void rem_caso1 (NOARV ** arv) {
	NOARV * rem;
	rem = *arv;

	if(rem->esq == NULL) {
		*arv = rem->dir;
	} else {
		*arv = rem->esq;
	}

	free(rem);
}

//Funcao: remove um no caso ele tenha 2 filhos, encontrando o sucessor do no a ser removido e chamando pelo caso1
void rem_caso2(NOARV ** arv) {
	NOARV ** suc;

	suc = &((*arv)->dir);
	while((*suc)->esq) {
		suc = &((*suc)->esq);
	}

	strcpy((*arv)->arquivo, (*suc)->arquivo);

	rem_caso1(suc);
}

//Funcao: escolhe um dos 3 tipos para listar os arquivos
void ls (char arq[], NOARV ** arv) {
	NOARV * busca;
	int i = 0;
	
	//Checar existencia de *
	while(arq[i] != '\0') {
		if(arq[i] == '*') {
			break;
		}
		i++;
	}

	if(i == 0) { //Somente *
		if(*arv) {
			imprimir_tudo(*arv);
		} else {
			printf("nao existem arquivos com essa expressao\n");
		}
	} else if(i < strlen(arq)) { //Regex
	
		busca = buscar(*arv, arq, i);
		if(busca != NULL) {
			imprimir_regex(*arv, arq, i);		
		} else {
			printf("nao existem arquivos com essa expressao\n");
		}
	} else { //Sem *
		busca = buscar(*arv, arq, i);
		if(busca != NULL) {
			imprimir(busca);
		} else {
			printf("nao existem arquivos com essa expressao\n");
		}
	}	
}

//Funcao: usado para ls *, imprime toda a arvore de maneira sequencial
void imprimir_tudo(NOARV * arv) {
	int i = 0;

	if(arv) {
		imprimir_tudo(arv->esq);
		for(i = 0; i < arv->copias; i++) {
			printf("%s\n", arv->arquivo);
		}
		imprimir_tudo(arv->dir);
	}
}

//Funcao: encontra os arquivos compativeis com a expressao regular e os imprime
void imprimir_regex(NOARV * arv, char arq[], int i) {
	int r, k;

	if(arv != NULL) {
		r = strncmp(arq, arv->arquivo, i);

		if(r < 0) {
			imprimir_regex(arv->esq, arq, i);
		} else if(r == 0) {
			imprimir_regex(arv->esq, arq, i);
			for(k = 0; k < arv->copias; k++) {
				printf("%s\n", arv->arquivo);
			}
			imprimir_regex(arv->dir, arq, i);
		} else {
			imprimir_regex(arv->dir, arq, i);
		}
	}
}

//Funcao: imprime um unico no da arvore e suas copias
void imprimir(NOARV * arv) {
	int i;

	if(arv != NULL) {
		for(i = 0; i < arv->copias; i++) {
			printf("%s\n", arv->arquivo);
		}
	}
}

//Funcao: utilizada para buscar um no compativel com o nome do arquivo, auxilia ls e rm
NOARV * buscar (NOARV * arv, char arq[], int i) {
	int r;
	NOARV * busca;

	busca = arv;

	while (busca != NULL) {
		r = strncmp(arq, busca->arquivo, i);
		
		if(r == 0) {
			break;
		} else if(r < 0) {
			busca = busca->esq;
		} else {
			busca = busca->dir;
		}
	}

	return busca;						
}

//Funcao: libera memoria alocada dinamicamente
void liberar(NOARV ** arv) {
	if(*arv) {
		liberar(&((*arv)->esq));
		liberar(&((*arv)->dir));
		free(*arv);
		*arv = NULL;
	}
}
