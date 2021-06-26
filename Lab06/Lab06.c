#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

//Estruturas
typedef enum { congelador, descongelando, pronto}ESTADO;

typedef struct ing {
	char nome[20];
	ESTADO estado;
	int tempo;
} INGREDIENTE;

typedef struct pizza {
	int tot_ing;
	int senha;
	INGREDIENTE * ingredientes[MAX];
} PIZZA;

typedef struct nofila {
	PIZZA * pedido;
	struct nofila * prox;
} FILA;

typedef struct forno {
	PIZZA * pedido;
	int tempo;
}FORNO;

typedef struct noarv {
	INGREDIENTE *ing;
	struct noarv *esq;
	struct noarv *dir;
	struct noarv *pai;
} NOARV;

//Assinatura de Funcoes
void passar_tempo(NOARV *arv);
void tirar_forno(FORNO * f);
void colocar_forno(FORNO * f, FILA ** fila);
PIZZA * checar_fila(FILA ** fila);
FILA * criar_fila (void);
void inserir_fila (FILA ** inicio, PIZZA * pz);
NOARV * inserir_arv (NOARV ** arv, char ingred[]);
void remover_fila(FILA ** inicio, FILA * no);
NOARV * buscar_arv (NOARV ** arv, char ingred[]);
void afunilar (NOARV * x);
void rotacionar_esq(NOARV * x);
void rotacionar_dir(NOARV * x);
void imprimir_lista(FILA * espera);
void liberar_arvore(NOARV * arv);
void liberar_fila(FILA *esp);

int main (void) {
	int tempo_atual = 0, tempo, total = 0, prontos = 0, senha = 1, i = 0;
	char ingrediente[100];
	NOARV *arv, *ing;
	PIZZA *pedido;
	FILA * espera;
	FORNO forno;

	arv = NULL;
	espera = criar_fila();
	forno.pedido = NULL;
	forno.tempo = 0;

	while(scanf(" %d", &tempo) == 1) {
		pedido = malloc(sizeof(PIZZA));
		pedido->tot_ing = 0;
		pedido->senha = senha;
		total = 0;
		prontos = 0;

		tempo = tempo - tempo_atual;
		tempo_atual = tempo_atual + tempo;

		if(tempo > 0) {
			for(i = 0; i < tempo; i ++) {
				passar_tempo(arv);
				if(forno.pedido != NULL) {
					(forno.tempo)++;
					if(forno.tempo == 1) {
						tirar_forno(&forno);
						colocar_forno(&forno, &espera);
					}
				}
			}
		}
		i = 0;

		while(scanf(" %s", ingrediente) == 1) {
			if(ingrediente[0] != '\r' && ingrediente[0] != '\n') {
				ing = buscar_arv(&arv, ingrediente);
				if(ing == NULL) {
					ing = inserir_arv(&arv, ingrediente);
					if(senha <= 2) {
						ing->ing->estado = pronto;
					}
					total++;
				} else {
					if(ing->ing->estado == 	pronto) {
						ing->ing->tempo = 0;
						total++;
						prontos++;
					} else if(ing->ing->estado == congelador) {
						ing->ing->estado = descongelando;
						total++;
					} else {
						total++;
					}
				}
				pedido->ingredientes[i++] = ing->ing;

			} else {
				break;
			}
		}
		pedido->tot_ing = total;
		
		if(senha <= 2) {
			prontos = total;
		}

		if(total == prontos) {
			if(forno.pedido == NULL) {				
				forno.pedido = pedido;
				forno.tempo = 0;
			} else {
				inserir_fila(&espera, pedido);
			}
		} else {
			inserir_fila(&espera, pedido);
		}

		senha++;
	}

	//Imprimir resto da fila
	imprimir_lista(espera);

	liberar_arvore(arv);
	liberar_fila(espera);
	

	return 0;
}

void passar_tempo(NOARV * arv) {
	if(arv != NULL) {
		passar_tempo(arv->esq);
		passar_tempo(arv->dir);
		(arv->ing->tempo)++;
		if(arv->ing->estado == pronto && arv->ing->tempo > 5) {
			arv->ing->estado = congelador;
			arv->ing->tempo = 0;
		}
		if(arv->ing->estado == descongelando && arv->ing->tempo >= 2) {
			arv->ing->estado = pronto;
			arv->ing->tempo = 0;
		}
	}
}

void tirar_forno(FORNO * f) {
	printf("%d ", f->pedido->senha);
	free(f->pedido);
	f->pedido = NULL;
	f->tempo = 0;
}

void colocar_forno(FORNO * f, FILA ** fila) {
	PIZZA * pedido;
	pedido = checar_fila(fila);
	if(pedido != NULL) {
		f->pedido = pedido;
		f->tempo = 0;
	}
}

PIZZA * checar_fila(FILA ** fila) {
	int i;
	FILA * buscar;
	PIZZA *ret;

	buscar = (*fila)->prox->prox;

	while(buscar->pedido != NULL) {
		for(i = 0; i < buscar->pedido->tot_ing; i++) {
			if(buscar->pedido->ingredientes[i]->estado != pronto) {
				break;
			}
		}
		if(i == buscar->pedido->tot_ing) {
			ret = buscar->pedido;
			remover_fila(fila, buscar);
			return ret;
		} else {
			buscar = buscar->prox;
		}
	}
	return buscar->pedido;
}

//Funcoes da Fila:
//Funcao: Criar fila com no dummy
FILA * criar_fila (void) {
	FILA * dummy;

	dummy = malloc(sizeof(FILA));

	dummy->pedido = NULL;
	dummy->prox = dummy;

	return dummy;
}

//Funcao: Inserir elemento na fila
void inserir_fila (FILA ** inicio, PIZZA * pz) {
	FILA * p;
	
	p = malloc(sizeof(FILA));

	p->pedido = pz;
	p->prox = (*inicio)->prox;
	(*inicio)->prox = p;
	*inicio = p;	
}

//Funcao: Remover no especifico da fila
void remover_fila(FILA ** inicio, FILA * no) {
	FILA * ant;
	ant = *inicio;

	while(ant->prox != no) {
		ant = ant->prox;
	}

	if(no == *inicio) {
		*inicio = ant;
	}

	ant->prox = no->prox;
	free(no);
}

//Funcoes da Arvore:
//Funcao: inserir no da arvore
NOARV * inserir_arv (NOARV ** arv, char ingred[]) {
	int r;
	NOARV * pai, *buscar;
	INGREDIENTE * novo;

	pai = NULL;
	buscar = *arv;
	novo = NULL;

	while(buscar != NULL) {
		r = strcmp(ingred, buscar->ing->nome);

		pai = buscar;

		if (r < 0) {
			buscar = pai->esq;
		} else if (r > 0) {
			buscar = pai->dir;
		} else {
			afunilar(buscar);
			return buscar;
		}
	}

	novo = malloc(sizeof(INGREDIENTE));
	strcpy(novo->nome, ingred);
	novo->estado = descongelando;
	novo->tempo = 0;

	buscar = malloc(sizeof(NOARV));
	buscar->ing = novo;
	buscar->esq = NULL;
	buscar->dir = NULL;
	buscar->pai = pai;

	afunilar(buscar);
	
	return buscar;
}

//Funcao: Buscar por um ingrediente na arvore
NOARV * buscar_arv (NOARV ** arv, char ingred[]) {
	int r;
	NOARV * buscar;
	buscar = *arv;

	while(buscar != NULL) {
		r = strcmp(ingred, buscar->ing->nome);
		if(r == 0) {
			afunilar(buscar);
			*arv = buscar;
			break;
		} else if (r < 0) {
			buscar = buscar->esq;
		} else {
			buscar = buscar->dir;
		}
	}
	return buscar;
}

//Funcao: Tornar o no como raiz
void afunilar (NOARV * x) {
	NOARV *pai, *avo;

	pai = x->pai;

	while(pai != NULL) {
		if(pai->pai == NULL) {//Caso Zig
			if(pai->esq == x) {
				rotacionar_dir(x);
			} else {
				rotacionar_esq(x);
			}
		} else {
			avo = x->pai->pai;

			if((avo->dir == pai && pai->dir == x) || //Caso Zig-zig
			   (avo->esq == pai && pai->esq == x)) {
				if(pai->esq == x) {
					rotacionar_dir(pai);
					rotacionar_dir(x);
				} else {
					rotacionar_esq(pai);
					rotacionar_esq(x);
				}
			} else { //Caso Zig-zag
				if(pai->esq == x) {
					rotacionar_dir(x);
					rotacionar_esq(x);
				} else {
					rotacionar_esq(x);
					rotacionar_dir(x);
				}
			}

		}

		pai = x->pai;
	}

	return;
}

//Funcao: Rotacionar um no para esquerda
void rotacionar_esq(NOARV * x) {
	NOARV *pai, *avo;

	pai = x->pai;
	avo = pai->pai;

	pai->dir = x->esq;
	if(x->esq != NULL) {
		x->esq->pai = pai;
	}
	x->esq = pai;
	pai->pai = x;
	x->pai = avo;

	if(avo != NULL) {
		if(avo->esq == pai) {
			avo->esq = x;
		} else {
			avo->dir = x;
		}
	}
}

//Funcao: Rotacionar um no para direita
void rotacionar_dir(NOARV * x) {
	NOARV *pai, *avo;

	pai = x->pai;
	avo = pai->pai;

	pai->esq = x->dir;
	if(x->dir != NULL) {
		x->dir->pai = pai;
	}
	x->dir = pai;
	pai->pai = x;
	x->pai = avo;

	if(avo != NULL) {
		if(avo->esq == pai) {
			avo->esq = x;
		} else {
			avo->dir = x;
		}
	}
}

void imprimir_lista(FILA * espera) {
	FILA * imprimir;
	
	imprimir = espera->prox->prox;

	while(imprimir->pedido != NULL) {
		printf(" %d", imprimir->pedido->senha);
		imprimir = imprimir->prox;
	}
}

void liberar_arvore(NOARV * arv) {
	if(arv != NULL) {
		liberar_arvore(arv->dir);
		liberar_arvore(arv->esq);
		free(arv->ing);
		free(arv);
	}
}

void liberar_fila(FILA *esp) {
	FILA * alvo, *prox;

	alvo = esp->prox->prox;

	while(alvo->pedido != NULL) {
		prox = alvo->prox;
		free(alvo->pedido);
		free(alvo);
		alvo = prox;				
	}
	free(alvo);
}
