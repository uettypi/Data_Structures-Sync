#include <stdio.h>

void changePointer(int **pp, int *q){
	*pp = q;
}

int main(void){
	int a = 10, b = 20;
	int *p = &a;
	changePointer(&p, &b);
	printf("%d\n", *p);
	return 0;
}