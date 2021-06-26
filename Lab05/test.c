#include<stdio.h>
#include<string.h>

int main (void) {
	char str1[10], str2[10];
	int num;

	do {
		scanf(" %s %s", str1, str2);
		scanf(" %d", &num);

		if(num >= 0) {
			printf(" %d\n", strncmp(str1, str2, num));
		}
	} while(num != -1);
	return 0;
}
