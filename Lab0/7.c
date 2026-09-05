#include <stdio.h>
#include <stdlib.h>

int n;

void reverse(int *p, int n){
	int *q = p + n - 1;

	for(int i = 1; i <= n/2; i ++){
		int tmp = *p;
		*p = *q;
		*q = tmp;

		p++;
		q--;
	}
}

int main(){
	scanf("%d", &n);
	
	int *a = malloc(n * sizeof(int));
	if(a == NULL){
		return 1;
	}
	
	int *tmp_in = a;
	
	for(int i = 1; i <= n; i ++){
		scanf("%d", tmp_in);
		tmp_in++;
	}
	
	reverse(a, n);
	
	int *tmp_out = a;
	
	for(int i = 1; i <= n; i ++){
		printf("%d ", *tmp_out);
		tmp_out++;
	}
	
	free(a);
	return 0; 
}