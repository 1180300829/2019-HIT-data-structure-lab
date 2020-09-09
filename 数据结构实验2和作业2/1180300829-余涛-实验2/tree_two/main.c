#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node* lchild;
	struct node* rchild;
	char data;
}btree;
//�������Ľڵ�
typedef struct
{
	btree* zifu[100];
	int flag[100];
	int top;
}stack;
//����һ���ַ�ջ
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
//����һ������
void makenull_q(queue* duilie)
{
	duilie->front = (node2*)malloc(sizeof(node2));
	duilie->front->next = NULL;
	duilie->rear = duilie->front;
}
//�������ÿ�
void enqueue_q(btree* T, queue* duilie)
{
	node2* q;
	q = (node2*)malloc(sizeof(node2));
	q->word = T;
	q->next = NULL;
	duilie->rear->next = q;
	duilie->rear = q;
}
//�ڶ��к������T
int empty_q(queue* duilie)
{
	if (duilie->front == duilie->rear)
		return 1;
	else
		return 0;
}
//�ж϶����Ƿ�Ϊ��
btree* front_q(queue* duilie)
{
	if (duilie->front->next)
		return duilie->front->next->word;
}
//���ض��еĵ�һ��Ԫ��
void dequeue_q(queue* duilie)
{
	node2* p;
	p = (node2*)malloc(sizeof(node2));
	if (duilie->rear == duilie->front)
	{
		printf("���п�\n");
	}
	p = duilie->front->next;
	duilie->front->next = p->next;
	if (p->next == NULL)
	{
		duilie->rear = duilie->front;
	}
	free(p);
}
//ɾ�����еĵ�һ��Ԫ��
void makenull(stack* s)
{
	s->top = -1;
}
//���ַ�ջ�ÿ�
int empty(stack* s)
{
	if (s->top < 0)
		return 1;
	else
		return 0;
}
//�ж��ַ�ջ�Ƿ��ÿ�
void push(btree* x, stack* s)
{
	s->top = s->top + 1;
	s->zifu[s->top] = x;
}
//���ַ�xѹ���ַ�ջ��ջ��
btree* top(stack* s)
{
	if (s->top == -1)
	{
		return NULL;
	}
	else
		return s->zifu[s->top];
}
//�����ַ�ջջ��Ԫ��
void pop(stack* s)
{
	if (s->top < 0)
	{
		printf("ջ��\n");
	}
	else
	{
		s->top = s->top - 1;
	}
}
//ɾ���ַ�ջջ����Ԫ��
char widechart[100];//������������
int i; //����ȫ�ֱ���ָʾ������Ԫ��
btree* createbtree_pre()
{
	char ch;
	btree* T;
	ch = getchar();
	if (ch == '#')
	{
		T = NULL;  //���롮#������Ϊ�սڵ�
	}
	else
	{
		T = (btree*)malloc(sizeof(btree));
		if (T == NULL)
		{
			printf("�����ڴ�ʧ��\n");
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
//������ʽ����������
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
//�������ʽ����������1--�ݹ齨�������������ŵĹ����
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
//�������ʽ����������2--�����������ź�'\0'
void print_inchart()
{
	int i;
	printf("�����չ�����ӡΪ: ");
	for (i = 0; widechart[i] != '\0'; i++)
	{
		printf("%c", widechart[i]);
	}
	printf("\n");
}
//��ӡ�����
void pre_order1(btree* T)
{
	if (T != NULL)
	{
		printf("%c", T->data);
		pre_order1(T->lchild);
		pre_order1(T->rchild);
	}
}
//����ݹ����
void in_order1(btree* T)
{
	if (T != NULL)
	{
		in_order1(T->lchild);
		printf("%c", T->data);
		in_order1(T->rchild);
	}
}
//����ݹ����
void post_order1(btree* T)
{
	if (T != NULL)
	{
		in_order1(T->lchild);
		in_order1(T->rchild);
		printf("%c", T->data);
	}
}
//����ݹ����
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
//����ǵݹ����
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
//����ǵݹ����
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
//����ǵݹ����
void lever_order(btree* T)
{
	queue* duilie;
	duilie = (queue*)malloc(sizeof(queue));//����duilie��ʼ��
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
//��������㷨
char store_ancestors[100]; //����һ�����鰴�ղ��򴢴����нڵ�����
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
//�ж����Ƿ�Ϊ��ȫ������
void make_alltrees(btree* T,int j)
{
	if (T != NULL)
	{
		store_ancestors[j] = T->data;
		make_alltrees(T->lchild, 2 * j);
		make_alltrees(T->rchild, 2 * j + 1);
	}
}
//�����нڵ����ݴ�������store_ancestors1[100]��
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
//�ҵ���Ҫ����'\0'��λ��
void bring_0(char a[])
{
	for (int q = 0; q < 100; q++)
	{
		a[q] = '(';
	}
}
//���ַ�����store_ancestors1[100]ȫ��Ϊ'('
char find_ancestors(char shu[], char a, char b)
{
	int m, k = 0, j = 0, n, p;
	char zuxian='0';
	for (m = 1; shu[m] != '\0'; m++)   //���ҵ���Ҫ���ҵĽڵ�a�������е�λ��
	{
		if (a == shu[m])
		{
			k = m;
			break;
		}
	}
	for (m = 1; shu[m] != '\0'; m++)   //���ҵ���Ҫ���ҵĽڵ�b�������е�λ��
	{
		if (b == shu[m])
		{
			j = m;
			break;
		}
	}
	if (k == 0 || j == 0)
	{
		printf("û���ҵ���Ҫ���ҵĽڵ㣬û�й�������\n");
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
//Ѱ�������ڵ�Ĺ�������
int main()
{
	btree* t;
	t = (btree*)malloc(sizeof(btree));
	int c, shifou,p;
	char m, n,o;
		printf("**********************************************\n");
		printf("��ӭ�������Ĳ���ϵͳ\n");
		printf("1.��������ʽ����������(����#��������Ϊ��)\n");
		printf("2.��������ݹ鷽ʽ����������\n");
		printf("3.��������ݹ鷽ʽ����������\n");
		printf("4.���պ���ݹ鷽ʽ����������\n");
		printf("5.��������ǵݹ鷽ʽ����������\n");
		printf("6.��������ǵݹ鷽ʽ����������\n");
		printf("7.���պ���ǵݹ鷽ʽ����������\n");
		printf("8.���ղ���ʽ����������\n");
		printf("9.���չ����ʽ��ӡ������\n");
		printf("10.�ж����Ƿ�Ϊ��ȫ������\n");
		printf("11.�������������ڵ�Ĺ�������\n");
		printf("**********************************************\n");
    while (1)
	{
		printf("��ѡ������Ҫִ�еĲ�����");
		scanf("%d", &c);
		getchar();
		switch (c)
		{
		case 1:
			printf("�밴������ʽ������Ľڵ�(����#��������Ϊ��)��");
			t = createbtree_pre();
			printf("\n");
			break;
		case 2:
			printf("��������Ϊ��");
			pre_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 3:
			printf("��������Ϊ��");
			in_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 4:
			printf("��������Ϊ��");
			post_order1(t);
			printf("\n");
			printf("\n");
			break;
		case 5:
			printf("��������Ϊ��");
			pre_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 6:
			printf("��������Ϊ��");
			in_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 7:
			printf("��������Ϊ��");
			post_order2(t);
			printf("\n");
			printf("\n");
			break;
		case 8:
			printf("��������Ϊ��");
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
				printf("������ȫ������\n");
			else
				printf("��������ȫ������\n");
			printf("\n");
			break;
		case 11:
			bring_0(store_ancestors);
			make_alltrees(t,1);
			p = find_last(store_ancestors);
			store_ancestors[p + 1] = '\0';
			printf("����������Ҫ��������ڵ�: ");
			scanf(" %c %c", &m, &n);
			printf("��������Ϊ��");
			find_ancestors(store_ancestors, m, n);
			printf("\n");
			printf("\n");
			break;
		default:
			printf("��������ȷ��Ϣ\n");
			printf("\n");
			printf("\n");
			break;
		}
	}
	return 0;
}

