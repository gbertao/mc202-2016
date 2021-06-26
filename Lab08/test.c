#include<stdio.h>

void hash (char * str) {
	int a;
	unsigned long int hash = 5381;

	a = *str++;
	//while(a = (*str)++) {
		hash = ((hash << 5) + hash) + a;
	//}
}

int main (void) {
	char str[10];
	
	scanf("%s", str);

	hash(str);


}
