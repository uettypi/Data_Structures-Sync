#include <stdio.h>

int a, b;

void swap(int *p, int *q){
	int tmp = 0;
	tmp = *p;
	*p = *q;
	*q = tmp;
}

int main(){
	scanf("%d%d", a, b);
	printf("a = %d, b = %d", a, b);
	swap(&a, &b);
	printf("a = %d, b = %d", a, b);
	return 0;
}