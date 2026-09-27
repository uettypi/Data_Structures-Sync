#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 任务1，在这里补充链式栈的类型定义和操作函数
typedef int ElemType;

typedef struct node {
    ElemType elm;
    struct node *next;
} SNode;

void StackInit(SNode **ppTop) {
    (*ppTop) = (SNode *)malloc(sizeof(SNode));
    (*ppTop)->next = NULL;
}

int StackEmpty(SNode *pTop) {
    return pTop->next == NULL;
}

int StackPush(SNode *pTop, ElemType elm) {
    SNode *p = pTop;
    SNode *newNode = (SNode *)malloc(sizeof(SNode));
    newNode->elm = elm;
    newNode->next = p->next;
    p->next = newNode;
    return 0;
}

int StackPop(SNode *pTop, ElemType *pElm) {
    SNode *p = pTop;
    if (p->next == NULL) {
        return 1;
    }
    *pElm = p->next->elm;
    SNode *temp = p->next;
    p->next = p->next->next;
    free(temp);
    return 0;
}

int StackGetTop(SNode *pTop, ElemType *pElm) {
    SNode *p = pTop->next;
    if (p == NULL) {
        return 1;
    }
    *pElm = p->elm;
    return 0;
}

void StackClear(SNode **ppTop) {
    SNode *p = (*ppTop)->next;
    while (p != NULL) {
        SNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(*ppTop);
    *ppTop = NULL;
}

// 任务2，补充Calc函数体
int Calc(char *s) {
// 注意计算时，最好用一个整数型的栈，字符数字入栈前，先转换为整数（即减去'0'）再入栈
    SNode *pTop;
    StackInit(&pTop);
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            StackPush(pTop, s[i] - '0');
        }
        else {
            ElemType l, r;
            StackPop(pTop, &r);
            StackPop(pTop, &l);
            ElemType result;
            switch (s[i]) {
                case '+':
                    result = l + r;
                    break;
                case '-':
                    result = l - r;
                    break;
                case '*':
                    result = l * r;
                    break;
                case '/':
                    result = l / r;
                    break;
                default:
                    StackClear(&pTop);
                    return 0;
            }
            StackPush(pTop, result);
        }
    }

    ElemType ans;
    StackPop(pTop, &ans);
    StackClear(&pTop);
    return ans;
}

int main() {
  // (5+3)*2+(6+3) = 25
  char str1[100] = "53+2*63++";
  char str2[100] = "53+";
  char str3[100] = "53+2*63++";
  char str4[100] = "53+2*63++";
  int rst;
  rst = Calc(str1);
  printf("the result1 is: %d\n", rst);
  rst = Calc(str2);
  printf("the result2 is: %d\n", rst);
  rst = Calc(str3);
  printf("the result3 is: %d\n", rst);
  rst = Calc(str4);
  printf("the result4 is: %d\n", rst);
  return 0;
}