#include<stdio.h>
#define MAX_LETRAS 30
int main (void) {
	FILE *arq, *sing, *plural;
	char palavra[MAX_LETRAS], c = 1;
	int i = 0;

	for(i = 0; i < MAX_LETRAS; i++) {
		palavra[i] = '\0';
	}

	arq = fopen("palavras.txt", "r");
	sing = fopen("singurales.txt", "w");
	plural = fopen("plurais.txt", "w");

	while(fscanf(arq, "%s", palavra) != EOF) {
		i = 0;
		c = 1;
		while(c != '\0') {
			c = palavra[i];
			i++;
		}
		if(palavra[i-2] == 's') {
			fprintf(plural, "%s\n", palavra);
		} else {
				fprintf(sing, "%s\n", palavra);
		}
		while(i >= 0) {
			palavra[i--] = '\0';
		}
	
	}

	fclose(arq);
	fclose(sing);
	fclose(plural);

	return 0;
}

	

