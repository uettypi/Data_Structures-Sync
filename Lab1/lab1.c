#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#include <string.h>
#include <stdbool.h>

typedef struct student
{
	char name[20];
	int  score;
}STU;

typedef STU ElemType;

typedef struct list {
  ElemType a[MAXSIZE + 1];
  int len;
} SeqList;

/**********************************/
/* 顺序表操作相关的函数从这里开始 */
/*********************************/
SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

void InitList2(SeqList **ppList) {
  *ppList = malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

int ListFull(SeqList *pList) {
  if (pList->len == MAXSIZE)
    return 1;
  else
    return 0;
}

int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

int ListLen(SeqList *pList) {
  return pList->len;
}

void Error(char *msg) {
  printf("error: %s\n", msg);
}

int GetElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("Get element from empty list");
    return 0;
  }
  if (i < 1 || i > MAXSIZE) {
    Error("Get element from illegal position!");
    return 0;
  }
  *pElm = pList->a[i];
  return 1;
}

int InsertElem(SeqList * pList, int i, ElemType elm) {
  int k;
  if (ListFull(pList)) {
    Error("Insert element to a full list!");
    return 0;
  }
  if (i < 1 || i > pList->len + 1) {
    Error("insert element out of range!");
    return 0;
  }
  for (k = pList->len; k >= i; k--) pList->a[k + 1] = pList->a[k];
  // assert(i == k + 1);
  pList->a[i] = elm;
  pList->len += 1;
  return 1;
}

int DelElem(SeqList *pList, int i, ElemType *pElm) {
  int k;
  if (ListEmpty(pList)) {
    Error("delete element from an empty list");
    return 0;
  }
  if (i < 1 || i > pList->len) {
    Error("delete element out of range");
    return 0;
  }
  *pElm = pList->a[i];
  for (k = i; k < pList->len; k++)
    pList->a[k] = pList->a[k + 1];
  pList->len -= 1;
  return 1;
}

void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++)
    printf("name: %-10s score:%-5d\n",
           ((pList->a[i])).name,
           ((pList->a[i])).score);
  putchar('\n');
}
/**********************************/
/* 顺序表操作相关的函数在这里结束 */
/*********************************/


/**********************************/
/* 学生数据的相关操作从这里开始  */
/*********************************/

void PrintStu(SeqList *pList)
{
  PrintList(pList);
}


// 用户输入学生个数n，然后利用循环把学生逐个加入到学生线形表中
void AddStu(SeqList *pList)
{
  int n, i;
  STU tmp;
  puts("Please input the number of students that you want to add: ");
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%s%d", tmp.name, &tmp.score);
    InsertElem(pList, 1, tmp);
  }
}

// 请把DelStu函数补充完整
// 要求：补充DelStu函数（应该考虑输入参数有哪些？有没有返回值，如果有，返回值的类型是什么？
//       怎样在删除完一个学生后，把删除掉的学生信息打印到屏幕上。），
//	 实现学生信息系统的学生删除功能（按学生在顺序表中的序号来删除）。
void DelStu(SeqList *pList)
{
	int i;
	scanf("%d", &i);

	STU tmp;
	if(DelElem(pList, i, &tmp)){
		printf("%s %d\n", tmp.name, tmp.score);
	}
}


// 请把DelByName函数补充完整
// 要求：补充DelByName函数，实现学生按姓名删除的功能。
void DelByName(SeqList *pList)
{
	char tmp_name[114514];
	scanf("%s", tmp_name);

	int deleted = 0;
	for(int i = 1; i <= pList->len; ){
		if(!strcmp(tmp_name, pList->a[i].name)){
			STU tmp;
			DelElem(pList, i, &tmp);
			printf("%s %d\n", tmp.name, tmp.score);
			deleted++;
		}
        else{
			i++;
		}
	}

	if(!deleted){
		printf("找到了滚木\n");
	}
}

// 请把SearchByName函数补充完整
// 要求：实现SearchByName函数，完成按姓名查找成绩信息的功能，同时打印出找到的学生在顺序表的位置号码，如果没有找到，则给出相应的提示信息。
void SearchByName(SeqList *pList)
{
	char tmp_name[114514];
	scanf("%s", tmp_name);

	bool flag = false;
	for(int i = 1; i <= pList->len; i++){
		if(!strcmp(tmp_name, pList->a[i].name)){
			printf("%d %s %d\n", i, pList->a[i].name, pList->a[i].score);
			flag = true;
		}
	}

	if(!flag){
		printf("找到了滚木\n");
	}
}

/**********************************/
/* 学生数据的相关操作在这里结束  */
/*********************************/

void menu()
{
  printf("1 add student\n");
  printf("2 delete student by location of array number\n");
  printf("3 delete student by name\n");
  printf("4 search student by name\n");
  printf("5 print the list\n");
  printf("6 exit \n");
  printf("your choice: ");
}

int main()
{
  int choice;
  SeqList *pList;
  InitList2(&pList);
  printf("*************************************This is a simple student management system!************************************\n");
  while (1) {
    menu();
    scanf("%d", &choice);
    switch (choice) {
    case 1: AddStu(pList); break;
    case 2: DelStu(pList); break;
    case 3: DelByName(pList);break;
    case 4: SearchByName(pList);break;
    case 5: PrintStu(pList); break;
    case 6: puts("Bye!Thanks for using!"); exit(0); break;
    }; // end of switch
  } // end of while
  return 0;
}
