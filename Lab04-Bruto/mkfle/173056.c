#include <stdio.h>
#include <stdlib.h>

void troca(int *a,int *b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

int prefixo(int v[],int m,int n,char *tabuleiro){
	int i;
	for(i=0;i<m-1;i++) {
		//caso esteja na diagonal 
		if((m-1)-i == abs(v[m-1]-v[i]))
			return 0;
		//casas iguais
		if(tabuleiro[v[i]*n+i] == tabuleiro[v[m-1]*n+m-1]){
			return 0;		
		}
	}
	return 1;
}

void permutar(int v[] ,int m ,int n,char *tabuleiro){
	int i;
	//Caso o prefixo nao for valido nao permuta
	if(prefixo(v,m,n,tabuleiro)) {
		if (n == m){
				//É valido pois se o prefixo de vetor preechido é valido
				printf("Tem solucao.");
				free(tabuleiro);
				free(v);
				exit(0);				
		}else{
			for (i = m; i < n; i++) {
				//permuta o vetor
				troca(&v[m], &v[i]);
				permutar(v, m + 1, n,tabuleiro);
				troca(&v[m], &v[i]); 			
			}
		}
	}
}

int main(){
	int *v,i,n;
	scanf("%d",&n);
	char *tabuleiro;
	
	//Aloca o vetor de posiçoes e a matriz do sudoku
	v = malloc(sizeof(int)*n);
	tabuleiro = malloc(n*n*sizeof(char));
	//Recebe a matriz
	for(i=0;i<n*n;i++) {
			scanf("%c",&tabuleiro[i]);
			if(tabuleiro[i] == '\n'|| tabuleiro[i] == '\r'){
				scanf("%c",&tabuleiro[i]);
			}
			if(tabuleiro[i] == '\n'|| tabuleiro[i] == '\r'){
				scanf("%c",&tabuleiro[i]);				
			} 
	}
	//Posiçao inicial
	for(i=0;i<n;i++) {
		v[i]=i;	
	}
	
	permutar(v,0,n,tabuleiro);
	printf("Sem solucao.\n");
	free(tabuleiro);
	free(v);
	return 0;
}
