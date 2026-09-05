#include <stdio.h>
#include <stdlib.h>

int n, sum = 0;

int main(){
	scanf("%d", &n);
    
	int *p = malloc(n * sizeof(int));
	if(p == NULL){
		return 1;
	}

    int *tmp = p;
	
	for(int i = 1; i <= n; i ++){
		scanf("%d", tmp);
		sum += *tmp;
		tmp++;
	}
	
	printf("平均值 = %.2f", (float)sum/n);

	free(p);
    return 0;
}