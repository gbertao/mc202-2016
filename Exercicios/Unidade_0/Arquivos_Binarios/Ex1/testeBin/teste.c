#include<stdio.h>

int main(void) {
	FILE *arq;
	int n;
	arq = fopen("num.bin", "rb");

	fseek(arq, -1*sizeof(int), SEEK_END);

	while(!feof(arq)) {
		fread(&n, sizeof(int), 1, arq);
		printf("num: %d\n", n);
	}
	fclose(arq);
	return 0;
}
