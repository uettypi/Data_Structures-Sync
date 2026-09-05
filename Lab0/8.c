#include <stdio.h>
#include <stdlib.h>

int n;

void createArray(int **p, int n){
	*p = malloc(n * sizeof(int));
}

int main(void){
	int *a = NULL;
	int n;
	scanf("%d", &n);
	createArray(&a, n);
	
	int *tmp_in = a;
	for(int i = 1; i <= n; i ++){
		scanf("%d", tmp_in);
		tmp_in++;
	}
	
	int *tmp_out = a;
	for(int i = 1; i <= n; i ++){
		printf("%d ", *tmp_out);
        tmp_out++;
	}
	
	free(a);
	return 0;
}