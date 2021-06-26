/* Lab 07 - Giovanni Bertão - ra173325 - MC202
	Funcionamento: O programa recebe uma sequencia de numeros e cada numero e alocado na fila de prioridade;
				   Quando a fila estiver cheia o programa removerá o elemento mais antigo(maior prioridade);
				   Se um arquivo antigo e revistado ele tem sua prioridade reduzida;
				   Ao final o programa retorna a quantidade de alterações na fila de prioridades.
*/
#include<stdio.h>
#include<stdlib.h>

//Estruturas
typedef struct {
	int valor;
	int prioridade;
}DADOS;

typedef struct {
	DADOS * fila;
	int tamanho;
} CACHE;

//Assinatura de funcoes
void criar_lista( CACHE **c, int capacidade);
int procurar_lista(CACHE *c, int arq);
void inserir_lista(CACHE * c, int arq, int pos, int *prAtual);
void descer(CACHE * c, int pos);
int esq (int i);
int dir(int i);
void trocar (DADOS * a, DADOS * b);
void renovar_acesso(CACHE * c, int pos, int * prAtual);
void liberar(CACHE * c);

int main (void) {
	//Variaveis
	CACHE *cache;
	int n, a, c, i, arq, r, prAtual = 20000, solucao = 0;

	//Entrada
	scanf("%d %d %d", &c, &n, &a);

	criar_lista(&cache, c);

	//Processamento
	for(i = 0; i < a; i++) {
		scanf(" %d", &arq);

		r = procurar_lista(cache, arq);

		if(r >= cache->tamanho) {//Se o arquivo nao for encontrado na cache
			if(cache->tamanho >= c) {//cache cheia, deve-se remover o mais antigo acessado
				(cache->tamanho)--;
				inserir_lista(cache, arq, 0, &prAtual);
				descer(cache, 0);
			} else {
				inserir_lista(cache, arq, r, &prAtual);//cache vazia
			}
			solucao++;
		} else {
			renovar_acesso(cache, r, &prAtual);//Elemento na cache
		}
	}
	
	//Saida
	printf("%d\n", solucao);

	//Liberar memoria alocada
	liberar(cache);
}

//Funcao: Criar e iniciar a lista de prioridades
void criar_lista (CACHE ** c, int capacidade) {
	CACHE * nova;
	DADOS * f;

	nova = malloc(sizeof(CACHE));
	f = malloc(sizeof(DADOS) * capacidade);
	nova->fila = f;
	nova->tamanho = 0;
	*c = nova;
}

//Funcao: procurar elemento na lista, se encontrar retorna o indice dele
int procurar_lista(CACHE *c, int arq) {
	int i;

	for(i = 0; i < c->tamanho; i++) {
		if(c->fila[i].valor == arq) {
			break;
		}
	}

	return i;
}

//Funcao: inserir elemento na lista
void inserir_lista(CACHE * c, int arq, int pos, int *prAtual) {
	c->fila[pos].valor = arq;
	c->fila[pos].prioridade = *prAtual;
	(c->tamanho)++;
	(*prAtual)--;
}

//Funcao: desce o elemento na fila de prioridades ate que sua prioridade seja maior que as de seus filhos
void descer(CACHE * c, int pos) {
	int maior = pos;

	if(esq(pos) < c->tamanho && c->fila[esq(pos)].prioridade > c->fila[maior].prioridade) {//verifica existencia de filhos
		maior = esq(pos);
	}
	if(dir(pos) < c->tamanho && c->fila[dir(pos)].prioridade > c->fila[maior].prioridade) {
		maior = dir(pos);
	}

	if(pos != maior) {
		trocar(&(c->fila[pos]), &(c->fila[maior]));
		descer(c, maior);
	}
}

//Funcao: retorna o indice do filho esquerdo
int esq (int i) {
	return 2*i + 1;
}

//Funcao: retorna o indice do filho direito
int dir(int i) {
	return 2*i + 2;
}

//Funcao: trocar dois dados no vetor de dados
void trocar (DADOS * a, DADOS * b) {
	DADOS aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

//Funcao: renovar acesso do elemnto re-visitado, (altera a prioridade e depois desce ela na arvore)
void renovar_acesso(CACHE * c, int pos, int * prAtual) {
	c->fila[pos].prioridade = *prAtual;
	descer(c, pos);
}

//Funcao: liberar espaco alocado dinamicamente
void liberar(CACHE * c) {
	free(c->fila);
	free(c);
}
