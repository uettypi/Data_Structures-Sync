#include <stdio.h>
#include <stdlib.h>

struct Student{
	int id;
	char name[20];
	float score;
};

int main(){
	struct Student stu;
	struct Student *p = &stu;
	
	scanf("%d", &(p -> id));
	scanf("%s", p -> name);
	scanf("%f", &(p -> score));
	
	printf("%d\n", p -> id);
	printf("%s\n", p -> name);
	printf("%f\n", p -> score);
	
	return 0;
}