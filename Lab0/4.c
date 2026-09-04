#include <stdio.h>

int main(){
	int a = 10;
	int *p = &a;
	int **pp = &p;
	
	printf("%d\n", a);
	printf("%d\n", *p);
	printf("%d\n", **pp);
	
	**pp = 20;
	printf("%d\n", a);
	return 0;
}