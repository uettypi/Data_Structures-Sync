/**********************************************
 Lab2: 栈的表示与实现及栈的应用

 实验内容1：编程实现链式存储的栈（整数栈 + 字符栈，均带头结点）
 实验内容2：后缀表达式求值            —— Calc()
 实验内容3：中缀表达式转后缀表达式    —— InfixToPostfix()
 编程提高：  支持多位数（两位、三位…） —— InfixToPostfix() / CalcEx()

 多位数的处理约定：
   后缀表达式中各个操作数、运算符之间用一个空格分隔，
   例如 (12+34)*2 的后缀形式为 "12 34 + 2 *"，
   这样扫描时才能区分 "12 34"（两个数）和 "1234"（一个数）。
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*============================================
  实验内容1（一）：整数链式栈，带头结点
    pHead 指向不存数据的头结点，栈顶元素是 pHead->next
    只有创建/销毁头结点需要二级指针，其余操作用一级指针即可
============================================*/
typedef int ElemType;

typedef struct node {
    ElemType elm;
    struct node *next;
} SNode;

void StackInit(SNode **ppHead) {
    (*ppHead) = (SNode *)malloc(sizeof(SNode));
    (*ppHead)->next = NULL;
}

int StackEmpty(SNode *pHead) {
    return pHead->next == NULL;
}

int StackPush(SNode *pHead, ElemType elm) {
    SNode *newNode = (SNode *)malloc(sizeof(SNode));
    if (newNode == NULL) {
        return 1;
    }
    newNode->elm = elm;
    newNode->next = pHead->next;
    pHead->next = newNode;
    return 0;
}

int StackPop(SNode *pHead, ElemType *pElm) {
    SNode *temp = pHead->next;
    if (temp == NULL) {
        return 1;
    }
    *pElm = temp->elm;
    pHead->next = temp->next;
    free(temp);
    return 0;
}

int StackGetTop(SNode *pHead, ElemType *pElm) {
    SNode *p = pHead->next;
    if (p == NULL) {
        return 1;
    }
    *pElm = p->elm;
    return 0;
}

void StackClear(SNode **ppHead) {
    SNode *p = (*ppHead)->next;
    while (p != NULL) {
        SNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(*ppHead);
    *ppHead = NULL;
}

/*============================================
  实验内容1（二）：字符链式栈，带头结点
    结构与整数栈完全一致，只是 elm 的类型换成 char，
    专门用于实验内容3中缀转后缀时暂存运算符和左括号
============================================*/
typedef char CElemType;

typedef struct cnode {
    CElemType elm;
    struct cnode *next;
} CSNode;

void CStackInit(CSNode **ppHead) {
    (*ppHead) = (CSNode *)malloc(sizeof(CSNode));
    (*ppHead)->next = NULL;
}

int CStackEmpty(CSNode *pHead) {
    return pHead->next == NULL;
}

int CStackPush(CSNode *pHead, CElemType elm) {
    CSNode *newNode = (CSNode *)malloc(sizeof(CSNode));
    if (newNode == NULL) {
        return 1;
    }
    newNode->elm = elm;
    newNode->next = pHead->next;
    pHead->next = newNode;
    return 0;
}

int CStackPop(CSNode *pHead, CElemType *pElm) {
    CSNode *temp = pHead->next;
    if (temp == NULL) {
        return 1;
    }
    *pElm = temp->elm;
    pHead->next = temp->next;
    free(temp);
    return 0;
}

int CStackGetTop(CSNode *pHead, CElemType *pElm) {
    CSNode *p = pHead->next;
    if (p == NULL) {
        return 1;
    }
    *pElm = p->elm;
    return 0;
}

void CStackClear(CSNode **ppHead) {
    CSNode *p = (*ppHead)->next;
    while (p != NULL) {
        CSNode *temp = p;
        p = p->next;
        free(temp);
    }
    free(*ppHead);
    *ppHead = NULL;
}

/*============================================
  实验内容2：后缀表达式求值（一位数版本，保留框架原有功能）
    输入：只含一位数字和 + - * / 的后缀表达式，如 "53+2*63++"
    返回：表达式的值
============================================*/
int Calc(char *s) {
    SNode *pHead;
    ElemType l, r, result;
    int i;

    StackInit(&pHead);
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            StackPush(pHead, s[i] - '0');   /* 字符数字先减 '0' 转为整数再入栈 */
        } else {
            /* 注意出栈顺序：先弹出的是右操作数，后弹出的是左操作数 */
            StackPop(pHead, &r);
            StackPop(pHead, &l);
            switch (s[i]) {
                case '+': result = l + r; break;
                case '-': result = l - r; break;
                case '*': result = l * r; break;
                case '/': result = l / r; break;
                default:
                    StackClear(&pHead);     /* 出错也要清栈，避免内存泄漏 */
                    return 0;
            }
            StackPush(pHead, result);
        }
    }
    StackPop(pHead, &result);               /* 扫描结束，栈内唯一元素即答案 */
    StackClear(&pHead);
    return result;
}

/*============================================
  实验内容3：中缀表达式 --> 后缀表达式（使用字符栈，支持多位数）

  算法：从左到右扫描中缀表达式
    1) 操作数    ：连续的数字整体输出，后面补一个空格作为分隔符
    2) 左括号 '(' ：直接入栈
    3) 右括号 ')' ：不断出栈输出，直到遇到 '(' 为止，'(' 出栈但不输出
    4) 运算符    ：当栈顶不是 '(' 且栈顶优先级 >= 当前运算符时，反复出栈输出；
                   然后把当前运算符入栈
    5) 扫描结束  ：栈中剩余运算符全部出栈输出

  输入：infix   中缀表达式字符串（可含空格）
        postfix 输出缓冲区，由调用方提供足够空间
  返回：0 表示转换成功，1 表示表达式非法（括号不匹配或含非法字符）
============================================*/

/* 运算符优先级：乘除高于加减，左括号最低（保证它不会被 4) 弹出） */
int Priority(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default:  return 0;     /* '(' */
    }
}

int InfixToPostfix(char *infix, char *postfix) {
    CSNode *pHead;
    CElemType op;
    int i, j = 0;               /* j 为 postfix 的写入位置 */

    CStackInit(&pHead);
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (ch == ' ') {                            /* 忽略中缀里的空格 */
            continue;
        } else if (isdigit((unsigned char)ch)) {    /* 1) 操作数：整体输出 */
            while (isdigit((unsigned char)infix[i])) {
                postfix[j++] = infix[i++];
            }
            i--;                                    /* 抵消 for 里的 i++ */
            postfix[j++] = ' ';                     /* 数字结束，补分隔符 */
        } else if (ch == '(') {                     /* 2) 左括号直接入栈 */
            CStackPush(pHead, ch);
        } else if (ch == ')') {                     /* 3) 右括号：弹到 '(' 为止 */
            while (CStackGetTop(pHead, &op) == 0 && op != '(') {
                CStackPop(pHead, &op);
                postfix[j++] = op;
                postfix[j++] = ' ';
            }
            if (CStackPop(pHead, &op) != 0) {       /* 栈已空却没找到 '(' */
                CStackClear(&pHead);
                return 1;                           /* 括号不匹配 */
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            /* 4) 运算符：先弹出栈中优先级不低于它的运算符 */
            while (CStackGetTop(pHead, &op) == 0 && op != '(' &&
                   Priority(op) >= Priority(ch)) {
                CStackPop(pHead, &op);
                postfix[j++] = op;
                postfix[j++] = ' ';
            }
            CStackPush(pHead, ch);
        } else {
            CStackClear(&pHead);
            return 1;                               /* 非法字符 */
        }
    }

    /* 5) 栈中剩余运算符全部出栈 */
    while (CStackPop(pHead, &op) == 0) {
        if (op == '(') {                            /* 还剩左括号说明少了 ')' */
            CStackClear(&pHead);
            return 1;
        }
        postfix[j++] = op;
        postfix[j++] = ' ';
    }

    if (j > 0) {
        j--;                                        /* 去掉末尾多余的空格 */
    }
    postfix[j] = '\0';
    CStackClear(&pHead);
    return 0;
}

/*============================================
  编程提高：后缀表达式求值（多位数版本）
    与 Calc() 的唯一区别：遇到数字时把连续数字拼成一个整数再入栈，
    空格只作分隔符跳过。
    输入：s 空格分隔的后缀表达式，如 "12 34 + 2 *"
          pResult 带回计算结果
    返回：0 表示计算成功，1 表示表达式非法（操作数不足、除零、非法字符）
============================================*/
int CalcEx(char *s, int *pResult) {
    SNode *pHead;
    ElemType l, r, result;
    int i = 0;

    StackInit(&pHead);
    while (s[i] != '\0') {
        if (s[i] == ' ') {                          /* 分隔符，跳过 */
            i++;
        } else if (isdigit((unsigned char)s[i])) {  /* 多位数：逐位累加 */
            int num = 0;
            while (isdigit((unsigned char)s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            StackPush(pHead, num);
        } else {
            /* 运算符：连弹两个操作数，先弹出的是右操作数 */
            if (StackPop(pHead, &r) != 0 || StackPop(pHead, &l) != 0) {
                StackClear(&pHead);
                return 1;                           /* 操作数不足 */
            }
            switch (s[i]) {
                case '+': result = l + r; break;
                case '-': result = l - r; break;
                case '*': result = l * r; break;
                case '/':
                    if (r == 0) {
                        StackClear(&pHead);
                        return 1;                   /* 除数为 0 */
                    }
                    result = l / r;
                    break;
                default:
                    StackClear(&pHead);
                    return 1;                       /* 非法字符 */
            }
            StackPush(pHead, result);
            i++;
        }
    }

    /* 合法的后缀表达式扫描完后，栈中应当恰好剩一个元素 */
    if (StackPop(pHead, &result) != 0 || !StackEmpty(pHead)) {
        StackClear(&pHead);
        return 1;
    }
    StackClear(&pHead);
    *pResult = result;
    return 0;
}

/*============================================
  中缀表达式求值：先转后缀，再对后缀求值（实验内容3 + 编程提高的合成）
============================================*/
void EvalInfix(char *infix) {
    char postfix[256];
    int result;

    if (InfixToPostfix(infix, postfix) != 0) {
        printf("中缀: %-24s -> 转换失败（括号不匹配或含非法字符）\n", infix);
        return;
    }
    if (CalcEx(postfix, &result) != 0) {
        printf("中缀: %-24s -> 后缀: %-24s -> 求值失败（表达式非法或除数为0）\n",
               infix, postfix);
        return;
    }
    printf("中缀: %-24s -> 后缀: %-24s = %d\n", infix, postfix, result);
}

int main() {
    /* ---------- 实验内容2：一位数后缀表达式求值 ---------- */
    char str[100] = "53+2*63++";    /* (5+3)*2+(6+3) = 25 */
    int rst;

    puts("===== 实验内容2：后缀表达式求值（一位数）=====");
    rst = Calc(str);
    printf("后缀: %-24s = %d\n", str, rst);

    /* ---------- 实验内容3：中缀转后缀 ---------- */
    puts("\n===== 实验内容3：中缀转后缀（一位数）=====");
    EvalInfix("(5+3)*2+(6+3)");     /* = 25 */
    EvalInfix("1+2*3-4/2");         /* = 5  */
    EvalInfix("2*(3+4)-5");         /* = 9  */
    EvalInfix("8/(4-2)/2");         /* = 2，验证同级运算符的左结合 */

    /* ---------- 编程提高：多位数 ---------- */
    puts("\n===== 编程提高：支持多位数 =====");
    EvalInfix("12+34*2");                /* = 80  */
    EvalInfix("(12+34)*2+(100-58)/6");   /* = 99  */
    EvalInfix("100/(2+3)-8");            /* = 12  */
    EvalInfix("(1000-1)*(2+3)");         /* = 4995 */

    /* ---------- 非法输入测试 ---------- */
    puts("\n===== 非法输入测试 =====");
    EvalInfix("(1+2))*3");          /* 括号不匹配 */
    EvalInfix("(1+2*3");            /* 括号不匹配 */
    EvalInfix("8/(4-4)");           /* 除数为 0   */
    EvalInfix("1+2a");              /* 非法字符   */

    return 0;
}
