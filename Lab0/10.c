#include <stdio.h>
#include <stdlib.h>

int n, sum = 0;
int maxn = -1, maxm;

struct Student{
	int id;
	char name[20];
	float score;
};

int main(){
	scanf("%d", &n);
	
	struct Student *students;
	students = malloc(n * sizeof(struct Student));

    struct Student *tmp_in = students;
	
	for(int i = 0; i < n; i ++){
		scanf("%d", &(*tmp_in).id);
		scanf("%s", (*tmp_in).name);
		scanf("%f", &(*tmp_in).score);
		
		sum += (*tmp_in).score;
		
		if((*tmp_in).score > maxn){
			maxn = (*tmp_in).score;
			maxm = i;
		}
		
		tmp_in++;
	}

    struct Student *tmp_out_all = students;
	
	for(int i = 0; i < n; i ++){
		printf("%d ", (*tmp_out_all).id);
		printf("%s ", (*tmp_out_all).name);
		printf("%f ", (*tmp_out_all).score);
        printf("\n");
        tmp_out_all++;
	}
	
	printf("%f\n", (float)sum/n);

    struct Student *tmp_out_max = &students[maxm];
	
	printf("%d ", (*tmp_out_max).id);
	printf("%s ", (*tmp_out_max).name);
	printf("%f ", (*tmp_out_max).score);
	
	free(students);
	return 0;
}