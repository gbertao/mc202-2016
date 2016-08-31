/*Lab0: Operação com Matrizes - Giovanni Bertão - ra173325 - MC202EF
 Programa
 Funcionamento: O programa irá receber a entrada de 2 arquivos;
				Um teste para checar se as matrizes são multiplicaveisserá realizado;
				Se mutiplicaveis ele as multiplicará e imprimirá a matriz resultante na tela;
				Caso não seja possivel realiar a multiplicação uma mensagem será obtida na saída.
*/				 
#include<stdio.h>
#include<stdlib.h>

//Declaração das matrizes
struct matriz {
	int linha;
	int coluna;
	int **matriz;
}mA, mB, mR;

//Assinatura de funções
int identidade(struct matriz m);

int main (void) {
	//Declaração de variaveis
	FILE *matrizA, *matrizB;
	int  i, j, k, elemento = 0;

	matrizA = fopen("matrizA.txt", "r");
	matrizB = fopen("matrizB.txt", "r");

	//Ler o número de linhas e colunas decada matriz
	fscanf(matrizA," %d", &mA.linha);
	fscanf(matrizA," %d", &mA.coluna);
	fscanf(matrizB," %d", &mB.linha);
	fscanf(matrizB," %d", &mB.coluna);

	if(mA.coluna == mB.linha && mA.coluna != 0) {
		//Criar Matrizes Dinamicas
		mA.matriz = malloc(sizeof(int*) * mA.linha);
		for(i = 0; i < mA.linha; i++) {
			mA.matriz[i] = malloc(sizeof(int) * mA.coluna);
		}

		mB.matriz = malloc(sizeof(int*) * mB.linha);
		for(i = 0; i < mB.linha; i++) {
			mB.matriz[i] = malloc(sizeof(int) * mB.coluna);
		}

		//Ler valores das matrizes
		//Matriz A
		for(i = 0; i < mA.linha; i++) {
			for(j = 0; j < mA.coluna; j++) {
				fscanf(matrizA," %d", &elemento);
				mA.matriz[i][j] = elemento;
			}
		}
		//Matriz B
		for(i = 0; i < mB.linha; i++) {
			for(j = 0; j < mB.coluna; j++) {
				fscanf(matrizB," %d", &elemento);
				mB.matriz[i][j] = elemento;
			}
		}
		elemento = 0;

		//Verificar se uma das matriz é matriz identidade
		if(identidade(mA) == 0) {
			mR = mB;
		} else if(identidade(mB) == 0) {
			mR = mA;
		} else {
			//Preparar Matriz Resultado
			mR.linha = mA.linha;
			mR.coluna = mB.coluna;

			
			mR.matriz = malloc(mR.linha * sizeof(int*));
			for(i = 0; i < mR.linha; i++) {
				mR.matriz[i] = malloc(mR.coluna * sizeof(int));
			}

			//Multiplicar MatrizA e B
			for(i = 0; i < mR.linha; i++) {
				for(j = 0; j < mR.coluna; j++) {
					for(k = 0; k < mA.coluna; k++) {
						elemento = elemento + mA.matriz[i][k]*mB.matriz[k][j];
					}
					mR.matriz[i][j] = elemento;
					elemento = 0;
				}
			}
		}

		//Imprimindo Matriz Resultante
		printf("%d %d\n", mR.linha, mR.coluna);
		for(i = 0; i < mR.linha; i++) {
			for(j = 0; j < mR.coluna; j++) {
				printf("%d ", mR.matriz[i][j]);
			}
			printf("\n");
		}

		//Liberar memória alocada dinâmicamente
		//Precisa verificar se umas das matrizes foi identidade para evitar um double free
		if(identidade(mA) != 0 && identidade(mB) !=0) {
			for(i = 0; i < mR.linha; i++) {
				free(mR.matriz[i]);
			}
			free(mR.matriz);
		}

		for(i = 0; i < mA.linha; i++) {
			free(mA.matriz[i]);
		}
		free(mA.matriz);
		for(i = 0; i < mB.linha; i++) {
			free(mB.matriz[i]);
		}
		free(mB.matriz);

	} else {
		printf("As matrizes nao seguem as propriedades necessarias para realizar a multiplicacao.\n");
	}

	//Fechar arquivos
	fclose(matrizA);
	fclose(matrizB);

	return 0;
}

//Função: recebe uma matriz, verifica se ela é uma matriz identidade e retorna 0 se verdadeiro ou !0 se falso
int identidade(struct matriz m) {
	int i, j, r = 0;
	if(m.linha == m.coluna) {
		for(i = 0; i < m.linha; i++) {
			for(j =0; j < m.coluna; j++) {
				if(i == j) {
					if(m.matriz[i][j] != 1) {
						r++;
					}
				} else {
					if(m.matriz[i][j] != 0) {
						r++;
					}
				}
			}
		}
	} else {
		r++;
	}
	return r;
}
