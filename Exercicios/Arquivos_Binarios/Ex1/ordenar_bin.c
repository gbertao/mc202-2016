#include<stdio.h>

int main (void) {
	FILE *arq1, *arq2, *saida;
	int n1, n2;

	arq1 = fopen("numeros1.txt", "rb");
	arq2 = fopen("numeros2.txt", "rb");
	saida = fopen("saida.txt", "w");

	fseek(arq1, 0, SEEK_SET);
	fseek(arq2, 0, SEEK_SET);

	while(fread(&n1, sizeof(int), 1, arq1) == 1 && fread(&n2, sizeof(int), 1, arq2) == 1) {

		if(n1 <= n2) {
			fprintf(saida, " %d\n", n1);
			fseek(arq2, -1 * sizeof(int), SEEK_CUR);
		} else {
			fprintf(saida, " %d\n", n2);
			fseek(arq1, -1 * sizeof(int), SEEK_CUR);
		}
	}

	if(n1 <= n2) {
		fseek(arq2, -1 * sizeof(int), SEEK_CUR);
	} else {
		fseek(arq1, -1 * sizeof(int), SEEK_CUR);
	}

	while(fread(&n1, sizeof(int), 1, arq1) == 1) {
		fprintf(saida, " %d\n", n1);
	}
	
	while(fread(&n2, sizeof(int), 1, arq2) == 1) {
		fprintf(saida, " %d\n", n2);
	}
			
	fclose(arq1);
	fclose(arq2);
	fclose(saida);

	return 0;
}
