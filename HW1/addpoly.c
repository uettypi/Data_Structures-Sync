
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
// 在这里补充一个结构体，包括系数和指数两项
typedef struct {
  double coef;
  int expn;
} Term;



// 把下面的double替换为自己定义的结构体类型（即顺序表中元素的类型是自己定义的）
typedef Term ElemType;

typedef struct list {
  ElemType a[MAXSIZE + 1];
  int len;
} SeqList;

SeqList * InitList();
void InitList2(SeqList **ppList);
int ListFull(SeqList *pList);
int ListEmpty(SeqList *pList);
int ListLen(SeqList *pList);
void Error(char *msg);
int GetElem(SeqList *pList, int i, ElemType *pElm);
int InsertElem(SeqList * pList, int i, ElemType elm);
int DelElem(SeqList *pList, int i, ElemType *pElm);
void PrintList(SeqList *pList);


int main() {
  int i, j, k;
  SeqList *A, *B, *C;
  // 下面的a 和 b表示了两个多项式，数组中的数据是多项式系数，
  // 它们在数组中的位置表示多少次方，例如a表示的是：
  // 0*X^0 + 0*X^1 + 7*X^2 + 0*X^3 + 3*X^4 + 1*X^5 + 9*X^6 + ...
  // b表示的是：
  // 0*X^0 + 0*X^1 + 8*X^2 + 1*X^3 + 22*X^4 + 7*X^5 ...
  int a[] = {0, 0, 7, 0, 3, 1, 9, 8, 5, 17, -8, 100}, b[] = {0, 0, 8, 1, 22, 7, -9, 8};
  int na = sizeof(a) / sizeof(a[0]), nb = sizeof(b) / sizeof(b[0]);
  ElemType x;

  InitList2(&A);
  InitList2(&B);
  InitList2(&C);

  for (j = 0; j < na; j++) {
    if (a[j] != 0) {
      x.coef = a[j];
      x.expn = j;
      InsertElem(A, A->len + 1, x);
    }
  }
  for (j = 0; j < nb; j++) {
    if (b[j] != 0) {
      x.coef = b[j];
      x.expn = j;
      InsertElem(B, B->len + 1, x);
    }
  }

  PrintList(A);
  PrintList(B);

  i = 1;
  k = 1;
  while (i <= A->len && k <= B->len) {
    if (A->a[i].expn < B->a[k].expn) {
      InsertElem(C, C->len + 1, A->a[i]);
      i++;
    } else if (A->a[i].expn > B->a[k].expn) {
      InsertElem(C, C->len + 1, B->a[k]);
      k++;
    } else {
      x.coef = A->a[i].coef + B->a[k].coef;
      x.expn = A->a[i].expn;
      if (x.coef != 0)
        InsertElem(C, C->len + 1, x);
      i++;
      k++;
    }
  }
  while (i <= A->len) {
    InsertElem(C, C->len + 1, A->a[i]);
    i++;
  }
  while (k <= B->len) {
    InsertElem(C, C->len + 1, B->a[k]);
    k++;
  }

  PrintList(C);

  return 0;
}


/* 输入：无
   返回：指向顺序表的指针，通过返回值，把申请到的、指向内存空间的指针带回调用方。
   功能：为顺序表申请内存空间，并把顺序表的大小置为0。
*/
SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

/* 输入：指向顺序表结构体的二级指针，调用方需要准备一个顺序表指针变量，然后把该
         变量的地址传递进来（即一个二级地址）
   返回：无
   功能：为顺序表申请内存空间，并把顺序表的大小置为0。
*/
void InitList2(SeqList **ppList) {
  *ppList = (SeqList *)malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量1，表示顺序表已满，否则未满。
   功能：判断顺序表是否已满。
*/
int ListFull(SeqList *pList) {
  /*
  if (pList->len == MAXSIZE)
    return 1;
  else
    return 0;
  */
  return (pList->len == MAXSIZE) ? 1 : 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量1，表示顺序表是空表，否则非空。
   功能：判断顺序表是否已空。
*/
int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量，表示顺序表有效元素个数
   功能：提供顺序表有效元素个数
*/
int ListLen(SeqList *pList) {
  return pList->len;
}

/* 输入：字符指针
   返回：无
   功能：输出自定义的出错消息定义
*/
void Error(char *msg) {
  printf("[错误]：%s\n", msg);
}

int GetElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("从空表中读取数据元素");
    return 0;
  }
  if (i < 1 || i > MAXSIZE) {
    Error("读取位置错误！");
    return 0;
  }
  *pElm = pList->a[i];
  return 1;
}

int InsertElem(SeqList * pList, int i, ElemType elm) {
  int k;
  if (ListFull(pList)) {
    Error("无法向已经满了的顺序表插入数据元素!");
    return 0;
  }
  if (i < 1 || i > pList->len + 1) {
    Error("插入位置越界!");
    return 0;
  }
  for (k = pList->len; k >= i; k--)
    pList->a[k + 1] = pList->a[k];
  pList->a[i] = elm;
  pList->len += 1;
  return 1;
}

int DelElem(SeqList *pList, int i, ElemType *pElm) {
  // 补充完整
  int k;
  if (ListEmpty(pList)) {
    Error("从空表中删除元素");
    return 0;
  }
  if (i < 1 || i > pList->len) {
    Error("删除位置越界");
    return 0;
  }
  *pElm = pList->a[i];
  for (k = i; k < pList->len; k++) {
    pList->a[k] = pList->a[k + 1];
  }
  pList->len -= 1;
  return 1;
}

void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++)
    printf("%g*x^%d ", pList->a[i].coef, pList->a[i].expn);
  putchar('\n');
}
