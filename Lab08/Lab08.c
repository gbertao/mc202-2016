#include<stdio.h>
#define MAX 1738

//Estruturas
typedef struct {
	char chave[10];
	int dado;
}NO;

typedef struct {
	No vetor[MAX];
}THASH;

//Assinatura de funcoes
void inserir_tabela(THASH *t, char *chave, int dado);
void remover_tabela(THASH *t, char *chave);

int main (void) {
	int n, rodadas, jogadores, r, j, palavras;
	char str[10], tentativa[10];

	scanf("%d", &n);//numero de palavras

	//Ler palavras e executar Hash
	
	//Jogo
	scanf(" %d %d", &rodadas, &jogadores);

	for(r = 0; r < rodadas; r++) {
		//Ler numero de palavras e palavras
		for(j = 0; j < jogadores; j++) {
			scanf(" %s", tentativa);
			//verificar tentativa
		}
	}
}

//Funcao da Hash
void inserir_tabela(THASH *t, char *chave, int dado) {
	int n = hash(chave);
	inserir_lista(&(t->vetor[n]), chave, dado);
}

void remover_tabela(THASH *t, char *chave) {
	int n = hash(chave);
	remover_lista(&(t->vetor[n]), n);
}
