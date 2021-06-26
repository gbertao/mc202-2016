#include<stdio.h>

int main (void) {
	FILE *arq;
	int n = 0, i = 0;
	char op;
	printf("Quantos números?\n");
	scanf(" %d", &n);

	printf("Par ou impar?\n");
	scanf(" %c", &op);

	if(op == 'p') {
		i = 2;
		arq = fopen("numeros1.txt", "wb");
	} else {
		i = 1;
		arq = fopen("numeros2.txt", "wb");
	}


	while(n > 0) {
		n--;
		fwrite(&i, sizeof(int), 1, arq);
		printf("%d ", i);
		i = i + 2;
	}
	printf("\n");

	fclose(arq);

	return 0;
}
