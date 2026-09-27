#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef char ElemType;
typedef struct stack {
  ElemType a[MAX];
  int top;
} Stack;

void InitStack(Stack *p) {
    p->top = -1;
}

int StackEmpty(Stack *p) {
    return p->top == -1;
}

int StackFull(Stack *p) {
    return p->top == MAX - 1;
}

void Push(Stack *p, ElemType x) {
    if (!StackFull(p)) {
        p->top++;
        p->a[p->top] = x;
    }
}

void Pop(Stack *p, ElemType *q) {
    if (!StackEmpty(p)) {
        *q = p->a[p->top];
        p->top--;
    }
}

int StackTop(Stack *p, ElemType *q) {
    if (!StackEmpty(p)) {
        *q = p->a[p->top];
        return 1;
    }
    return 0;
}

void StackClear(Stack *p) {
    p->top = -1;
}

// 待判断的字符串保存在数组a中，数组的有效长度保存在n中
// 通过计算返回0，表示括号不匹配，返回1表示匹配
int Match(char a[], int n) {
    Stack s;
    InitStack(&s);
    for (int i = 0; i < n; i++) {
        if (a[i] == '(' || a[i] == '[' || a[i] == '{') {
            Push(&s, a[i]);
        }
        else {
            if (StackEmpty(&s)) {
                return 0;
            }
            else {
                ElemType topElem;
                StackTop(&s, &topElem);
                if ((a[i] == ')' && topElem == '(') || (a[i] == ']' && topElem == '[') || (a[i] == '}' && topElem == '{')) {
                    Pop(&s, &topElem);
                }
                else {
                    return 0;
                }
            }
        }
    }
    if (!StackEmpty(&s)) {
        return 0;
    }
    return 1;
}


int main() {
  char str1[100] = "()[]{}";
  printf("%d\n", Match(str1, strlen(str1)));

  char str2[100] = "{[()][(()())]}";
  printf("%d\n", Match(str2, strlen(str2)));

  char str3[100] = "([)]{}";
  printf("%d\n", Match(str3, strlen(str3)));

  char str4[100] = "{[)(]{}}";
  printf("%d\n", Match(str4, strlen(str4)));

  return 0;
}