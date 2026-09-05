#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[20];
    float score;
};

struct Student *createStudent(void)
{
    struct Student *p;

    p = malloc(sizeof(struct Student));

    if (p == NULL) {
        return NULL;
    }

    printf("请输入学号：");
    scanf("%d", &p->id);

    printf("请输入姓名：");
    scanf("%19s", p->name);

    printf("请输入成绩：");
    scanf("%f", &p->score);

    return p;
}

int main(void)
{
    struct Student *p;

    p = createStudent();

    if (p == NULL) {
        printf("内存申请失败\n");
        return 1;
    }

    printf("\n学生信息：\n");
    printf("学号：%d\n", p->id);
    printf("姓名：%s\n", p->name);
    printf("成绩：%.2f\n", p->score);

    free(p);
    p = NULL;

    return 0;
}