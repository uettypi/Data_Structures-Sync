#include <stdio.h>

int n, a[114514];

void doubleArray(int *p, int m){
	for(int i = 1; i <= m; i ++){
		*p *= 2;
		p++;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
	}
	doubleArray(a+1, n);
	for(int i = 1; i <= n; i ++){
		printf("%d ", a[i]);
	}
	return 0;
}