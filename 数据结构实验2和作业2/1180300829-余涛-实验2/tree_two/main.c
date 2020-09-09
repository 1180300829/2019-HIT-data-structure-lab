#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node* lchild;
	struct node* rchild;
	char data;
}btree;
//定义树的节点
typedef struct
{
	btree* zifu[100];
	int flag[100];
	int top;
}stack;
//定义一个字符栈
typedef struct node22
{
	btree* word;
	struct node22* next;
}node2;
typedef struct queue22
{
	node2* front;
	node2* rear;
}queue;
//定义一个队列
void makenull_q(queue* duilie)
{
	duilie->front = (node2*)malloc(sizeof(node2));
	duilie->front->next = NULL;
	duilie->rear = duilie->front;
}
//将队列置空
void enqueue_q(btree* T, queue* duilie)
{
	node2* q;
	q = (node2*)malloc(sizeof(node2));
	q->word = T;
	q->next = NULL;
	duilie->rear->next = q;
	duilie->rear = q;
}
//在队列后面插入T
int empty_q(queue* duilie)
{
	if (duilie->front == duilie->rear)
		return 1;
	else
		return 0;
}
//判断队列是否为空
btree* front_q(queue* duilie)
{
	if (duilie->front->next)
		return duilie->front->next->word;
}
//返回队列的第一个元素
void dequeue_q(queue* duilie)
{
	node2* p;
	p = (node2*)malloc(sizeof(node2));
	if (duilie->rear == duilie->front)
	{
		printf("队列空\n");
	}
	p = duilie->front->next;
	duilie->front->next = p->next;
	if (p->next == NULL)
	{
		duilie->rear = duilie->front;
	}
	free(p);
}
//删除队列的第一个元素
void makenull(stack* s)
{
	s->top = -1;
}
//将字符栈置空
int empty(stack* s)
{
	if (s->top < 0)
		return 1;
	else
		return 0;
}
//判断字符栈是否置空
void push(btree* x, stack* s)
{
	s->top = s->top + 1;
	s->zifu[s->top] = x;
}
//将字符x压入字符栈的栈顶
btree* top(stack* s)
{
	if (s->top == -1)
	{
		return NULL;
	}
	else
		return s->zifu[s->top];
}
//返回字符栈栈顶元素
void pop(stack* s)
{
	if (s->top < 0)
	{
		printf("栈空\n");
	}
	else
	{
		s->top = s->top - 1;
	}
}
//删除字符栈栈顶的元素
char widechart[100];//定义广义表数组
int i; //定义全局变量指示广义表的元素
btree* createbtree_pre()
{
	char ch;
	btree* T;
	ch = getchar();
	if (ch == '#')
	{
		T = NULL;  //输入‘#’代表为空节点
	}
	else
	{
		T = (btree*)malloc(sizeof(btree));
		if (T == NULL)
		{
			printf("申请内存失败\n");
		}
		else
		{
			T->data = ch;
			T->lchild = createbtree_pre();
			T->rchild = createbtree_pre();
		}
	}
	return T;
}
//用先序方式建立二叉树
void keep_inchart1(btree* T)
{
	if (T != NULL)
	{
		if (T->lchild == NULL && T->rchild == NULL)
		{
			widechart[i] = T->data;
			i++;
		}
		else
		{
			widechart[i] = T->data;
			i++;
			widechart[i] = '(';
			i++;
			keep_inchart1(T->lchild);
			widechart[i] = ',';
			i++;
			keep_inchart1(T->rchild);
			widechart[i] = ')';
			i++;
		}
	}
}
//按广义表方式储存树步骤1--递归建立除了两边括号的广义表
void keep_inchart2(btree* T)
{
	btree* t = T;
	i = 0;
	widechart[i] = '(';
	i++;
	keep_inchart1(t);
	widechart[i] = ')';
	i++;
	widechart[i] = '\0';
}
//按广义表方式储存树步骤2--加上两边括号和'\0'
void print_inchart()
{
	int i;
	printf("树按照广义表打印为: ");
	for (i = 0; widechart[i] != '\0'; i++)
	{
		printf("%c", widechart[i]);
	}
	printf("\n");
}
//打印广义表
void pre_order1(btree* T)
{
	if (T != NULL)
	{
		printf("%c", T->data);
		pre_order1(T->lchild);
		pre_order1(T->rchild);
	}
}
//先序递归遍历
void in_order1(btree* T)
{
	if (T != NULL)
	{
		in_order1(T->lchild);
		printf("%c", T->data);
		in_order1(T->rchild);
	}
}
//中序递归遍历
void post_order1(btree* T)
{
	if (T != NULL)
	{
		in_order1(T->lchild);
		in_order1(T->rchild);
		printf("%c", T->data);
	}
}
//后序递归遍历
void pre_order2(btree* T)
{
	stack* s;
	s = (stack*)malloc(sizeof(stack));
	makenull(s);
	while (T != NULL || !empty(s))
	{
		while (T != NULL)
		{
			printf("%c", T->data);
			push(T, s);
			T = T->lchild;
		}
		if (!empty(s))
		{
			T = top(s);
			pop(s);
			T = T->rchild;
		}
	}
}
//先序非递归遍历
void in_order2(btree* T)
{
	stack* s;
	s = (stack*)malloc(sizeof(stack));
	makenull(s);
	while (T != NULL || !empty(s))
	{
		while (T != NULL)
		{
			push(T, s);
			T = T->lchild;
		}
		if (!empty(s))
		{
			T = top(s);
			pop(s);
			printf("%c", T->data);
			T = T->rchild;
		}
	}
}
//中序非递归遍历
void post_order2(btree* T)
{
	stack* s;
	s = (stack*)malloc(sizeof(stack));
	makenull(s);
	while (T != NULL || !empty(s))
	{
		while (T != NULL)
		{
			push(T, s);
			s->flag[s->top] = 1;
			T = T->lchild;
		}
		while (!empty(s) && s->flag[s->top] == 2)
		{
			printf("%c", top(s)->data);
			s->top--;
		}
		if (!empty(s))
		{
			s->flag[s->top] = 2;
			T = top(s)->rchild;
		}

	}
}
//后序非递归遍历
void lever_order(btree* T)
{
	queue* duilie;
	duilie = (queue*)malloc(sizeof(queue));//队列duilie初始化
	makenull_q(duilie);
	btree* q;
	q = (btree*)malloc(sizeof(btree));
	if (T == NULL)
	{
		return;
	}
	enqueue_q(T, duilie);
	while (!empty_q(duilie))
	{
		q = front_q(duilie);
		printf("%c", q->data);
		dequeue_q(duilie);
		if (q->lchild != NULL)
		{
			enqueue_q(q->lchild, duilie);
		}
		if (q->rchild != NULL)
		{
			enqueue_q(q->rchild, duilie);
		}
	}
}
//层序遍历算法
char store_ancestors[100]; //定义一个数组按照层序储存所有节点数据
int judge_fulltree()
{
    int pp,ll=0;
    for(pp=1;store_ancestors[pp]!='\0';pp++)
    {
        if(store_ancestors[pp]=='(')
        {
            ll=1;
            break;
        }
    }
    if(ll==1)
        return 0;
    if(ll==0)
        return 1;
}
//判断树是否为完全二叉树
void make_alltrees(btree* T,int j)
{
	if (T != NULL)
	{
		store_ancestors[j] = T->data;
		make_alltrees(T->lchild, 2 * j);
		make_alltrees(T->rchild, 2 * j + 1);
	}
}
//把所有节点数据存入数组store_ancestors1[100]中
int find_last(char a[])
{
	int last;
	for (int q = 99; q >0; q--)
	{
		if (a[q] != '(')
		{
			last = q;
			break;
		}
	}
	return last;
}
//找到需要存入'\0'的位置
void bring_0(char a[])
{
	for (int q = 0; q < 100; q++)
	{
		a[q] = '(';
	}
}
//让字符数组store_ancestors1[100]全部为'('
char find_ancestors(char shu[], char a, char b)
{
	int m, k = 0, j = 0, n, p;
	char zuxian='0';
	for (m = 1; shu[m] != '\0'; m++)   //先找到需要查找的节点a在数组中的位置
	{
		if (a == shu[m])
		{
			k = m;
			break;
		}
	}
	for (m = 1; shu[m] != '\0'; m++)   //先找到需要查找的节点b在数组中的位置
	{
		if (b == shu[m])
		{
			j = m;
			break;
		}
	}
	if (k == 0 || j == 0)
	{
		printf("没有找到需要查找的节点，没有公共祖先\n");
		return;
	}
	else
	{
		for (n = k / 2; n != 0;)
		{
			p = j;
			for (p = j / 2; p != 0;)
			{
				if (shu[n] == shu[p])
				{
					zuxian = shu[n];
					printf("%c ", zuxian);
				}
				p = p / 2;
			}
			n = n / 2;
        }
	}
	return zuxian;
}
//寻找两个节点的公共祖先
int main()
{
	btree* t;
	t = (btree*)malloc(sizeof(btree));
	int c, shifou,p;
	char m, n,o;
		printf("**********************************************\n");
		printf("欢迎来到树的操作系统\n");
		printf("1.按照先序方式建立二叉树(输入#代表输入为空)\n");
		printf("2.按照先序递归方式遍历二叉树\n");
		printf("3.按照中序递归方式遍历二叉树\n");
		printf("4.按照后序递归方式遍历二叉树\n");
		printf("5.按照先序非递归方式遍历二叉树\n");
		printf("6.按照中序非递归方式遍历二叉树\n");
		printf("7.按照后序非递归方式遍历二叉树\n");
		printf("8.按照层序方式遍历二叉树\n");
		printf("9.按照广义表方式打印二叉树\n");
		printf("10.判断树是否为完全二叉树\n");
		printf("11.求树任意两个节点的公共祖先\n");
		printf("**********************************************\n");
    while (1)
	{
		printf("请选择你需要执行的操作：");
		scanf("%d", &c);
		getchar();
		switch (c)
		{
		case 1:
			printf("请按照先序方式输入你的节点(输入#代表输入为空)：");
			t = createbtree_pre();
			printf("\n");
			break;
		case 2:
			printf("先序排列为：");
			pre_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 3:
			printf("中序排列为：");
			in_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 4:
			printf("后序排列为：");
			post_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 5:
			printf("先序排列为：");
			pre_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 6:
			printf("中序排列为：");
			in_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 7:
			printf("后序排列为：");
			post_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 8:
			printf("层序排列为：");
			lever_order(t);
			printf("\n");
			printf("\n");
			break;
		case 9:
			keep_inchart2(t);
			print_inchart();
			printf("\n");
			break;
		case 10:
		    bring_0(store_ancestors);
			make_alltrees(t,1);
			p = find_last(store_ancestors);
			store_ancestors[p + 1] = '\0';
			shifou = judge_fulltree();
			if (shifou == 1)
				printf("树是完全二叉树\n");
			else
				printf("树不是完全二叉树\n");
			printf("\n");
			break;
		case 11:
			bring_0(store_ancestors);
			make_alltrees(t,1);
			p = find_last(store_ancestors);
			store_ancestors[p + 1] = '\0';
			printf("请输入你需要求的两个节点: ");
			scanf(" %c %c", &m, &n);
			printf("公共祖先为：");
			find_ancestors(store_ancestors, m, n);
			printf("\n");
			printf("\n");
			break;
		default:
			printf("请输入正确信息\n");
			printf("\n");
			printf("\n");
			break;
		}
	}
	return 0;
}

