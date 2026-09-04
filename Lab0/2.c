#include <stdio.h>

int n, a[114514];

int maxValue(int *p, int m){
	int maxn = -1;
	for(int i = 1; i <= m; i ++){
		if(*p > maxn){
			maxn = *p;
		}
		p++;
	}
	return maxn;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
	}
	printf("%d", maxValue(a+1, n));
	return 0;
}