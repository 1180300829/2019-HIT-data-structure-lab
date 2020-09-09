#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	char verlist[20]; //�����
	int edge[20][20]; //�߱�
	int n, e; //ͼ�Ķ������ͱ���
}mtgraph;
//ͼ���ڽӾ���

typedef struct node
{
	int adjvex;    //�ڽӵ���
	//int cost;      //����Ȩֵ
	struct node* next;
}edgenode;
//�߱���

typedef struct
{
	char vertex;   //����������
	edgenode* firstedge;  //������ͷָ��
}vertexnode;
//�������

typedef struct
{
	vertexnode verlist[20];
	int n, e;   //������������
}adjgraph;
//ͼ���ڽӱ�

void createmgraph(mtgraph* g)
{
	int i, j, m, n;
	FILE* fp;
	fp = fopen("read_picture.txt", "r");
	if (fp == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fscanf(fp, "%d", &g->n);
	fscanf(fp, "%d", &g->e);
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			g->edge[i][j] = 0;
		}
	}
	for (i = 0; i < g->n; i++)
	{
		fscanf(fp, " %c", &g->verlist[i]);
	}
	for (i = 0; i < g->e; i++)
	{
		fscanf(fp, "%d,%d", &m, &n);
		g->edge[m - 1][n - 1] = 1;
		g->edge[n - 1][m - 1] = 1;
	}
	fclose(fp);
}
//���ļ��ж�������ͼ���ڽӾ���洢

void creategraph(adjgraph* g)
{
	int i, j, tail, head;
	FILE* fp;
	fp = fopen("read_picture.txt", "r");
	if (fp == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fscanf(fp, "%d", &g->n);
	fscanf(fp, "%d", &g->e);
	for (i = 0; i < g->n; i++)
	{
		fscanf(fp, " %c", &g->verlist[i].vertex);
		g->verlist[i].firstedge = NULL;
	}
	for (j = 0; j < g->e; j++)
	{
		fscanf(fp, "%d,%d", &tail, &head);
		edgenode* p;
		p = (edgenode*)malloc(sizeof(edgenode));    //�������
		p->adjvex = head - 1;
		p->next = g->verlist[tail - 1].firstedge;
		g->verlist[tail - 1].firstedge = p;
		p = (edgenode*)malloc(sizeof(edgenode));    //��������
		p->adjvex = tail - 1;
		p->next = g->verlist[head - 1].firstedge;
		g->verlist[head - 1].firstedge = p;
	}
}
//���ļ��ж�������ͼ���ڽӱ�洢

void printmgraph(mtgraph* g)
{
	printf("  ");
	for (int i = 0; i < g->n; i++)
	{
		printf("%c ", g->verlist[i]);
		if (i == g->n - 1)
		{
			printf("\n");
		}
	}
	for (int j = 0; j < g->n; j++)
	{
		printf("%c ", g->verlist[j]);
		for (int m = 0; m < g->n; m++)
		{
			printf("%d ", g->edge[j][m]);
			if (m == g->n - 1)
			{
				printf("\n");
			}
		}
	}
}
//��ӡ�ڽӾ���

void printgraph(adjgraph* g)
{
	edgenode* zanshi;
	zanshi = (edgenode*)malloc(sizeof(edgenode));
	for (int i = 0; i < g->n; i++)
	{
		zanshi = g->verlist[i].firstedge;
		printf("%c->", g->verlist[i].vertex);
		while (zanshi != NULL)
		{
			printf("%c->", g->verlist[zanshi->adjvex].vertex);
			//printf("%d\n", g->verlist[i].firstedge->adjvex);
			if (zanshi->next != NULL)
			{
				zanshi = zanshi->next;
			}
			else
			{
				break;
			}
		}
		printf("\n");
	}
}
//��ӡ�ڽӱ�

void trans_to_graph(mtgraph* g, adjgraph* p)
{
	int i, j, m = 0, tail, head;
	p->n = g->n;
	p->e = g->e;
	for (i = 0; i < p->n; i++)
	{
		p->verlist[i].vertex = g->verlist[i];
		p->verlist[i].firstedge = NULL;
	}
	for (i = 0; i < g->n; i++)
	{
		for (j = m; j < g->n; j++)
		{
			if (g->edge[i][j] != 0)
			{
				tail = i;
				head = j;
				edgenode* u;
				u = (edgenode*)malloc(sizeof(edgenode));    //�������
				u->adjvex = head;
				u->next = p->verlist[tail].firstedge;
				p->verlist[tail].firstedge = u;
				u = (edgenode*)malloc(sizeof(edgenode));    //��������
				u->adjvex = tail;
				u->next = p->verlist[head].firstedge;
				p->verlist[head].firstedge = u;
			}
		}
		m++;
	}
}
//�ڽӾ���ת�����ڽӱ�

void trans_to_mgraph(adjgraph* biao, mtgraph* p)
{
	int i, j, k, chang, kuan;
	edgenode* zanshi;
	zanshi = (edgenode*)malloc(sizeof(edgenode));
	p->n = biao->n;
	p->e = biao->e;
	for (i = 0; i < p->n; i++)
	{
		for (j = 0; j < p->n; j++)
		{
			p->edge[i][j] = 0;
		}
	}
	for (i = 0; i < p->n; i++)
	{
		p->verlist[i] = biao->verlist[i].vertex;
	}
	for (k = 0; k < biao->n; k++)
	{
		chang = k;
		zanshi = biao->verlist[k].firstedge;
		while (zanshi != NULL)
		{
			kuan = zanshi->adjvex;
			p->edge[chang][kuan] = 1;
			if (zanshi->next != NULL)
			{
				zanshi = zanshi->next;
			}
			else
			{
				break;
			}
		}
	}
}
//�ڽӱ�ת��Ϊ�ڽӾ���

int visited_1[20]; //�ڽӱ�����ݹ���ʱ������
int dfn_1[20]; //�ڽӱ�����ݹ鶥���������
int visited_2[20]; //�ڽӾ�������ݹ���ʱ������
int dfn_2[20]; //�ڽӾ�������ݹ鶥���������
int count_1 = 1;   //��¼�ڽӱ�ݹ�����ı��
int count_2 = 1;   //��¼�ڽӾ���ݹ�����ı��

void DFS1(adjgraph* g, int i)
{
	edgenode* p;
	p = (edgenode*)malloc(sizeof(edgenode));
	printf("%c ", g->verlist[i].vertex);
	visited_1[i] = 1;
	dfn_1[i] = count_1++;
	p = g->verlist[i].firstedge;
	while (p)
	{
		if (!visited_1[p->adjvex])
		{
			DFS1(g, p->adjvex);
		}
		p = p->next;
	}
}
//�ڽӱ�ݹ���������

void DFStraverse(adjgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_1[i] = 0;            //��������ʼ��
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_1[i])
		{
			DFS1(g, i);
		}
	}
}
//�ڽӱ�����ݹ����㷨

void DFS2(mtgraph* g, int i)
{
	int j;
	printf("%c ", g->verlist[i]);
	visited_2[i] = 1;
	dfn_2[i] = count_2++;
	for (j = 0; j < g->n; j++)
	{
		if (g->edge[i][j] == 1 && !visited_2[j])
		{
			DFS2(g, j);
		}
	}
}
//�ڽӾ���ݹ���������

void DFStraverse_m(mtgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_2[i] = 0;            //��������ʼ��
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_2[i])
		{
			DFS2(g, i);
		}
	}
}
//�ڽӾ�������ݹ����㷨

typedef struct
{
	int zifu[20];
	int top;
}stack;
//����һ��ջ

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

void push(int x, stack* s)
{
	s->top = s->top + 1;
	s->zifu[s->top]=x;
}
//���ַ�xѹ���ַ�ջ��ջ��

int top(stack* s)
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

int visited_5[20]; //�ڽӱ�����ǵݹ���ʱ������
int dfn_5[20]; //�ڽӱ�����ǵݹ鶥���������
int visited_6[20]; //�ڽӾ�������ǵݹ���ʱ������
int dfn_6[20]; //�ڽӾ�������ǵݹ鶥���������
int count_5 = 1;   //��¼�ڽӱ�ǵݹ�����ı��
int count_6 = 1;   //��¼�ڽӾ���ǵݹ�����ı��

void no_DFS1(adjgraph* g, int i)
{
	stack* s;
	s = (stack*)malloc(sizeof(stack));
	makenull(s);
	edgenode* p;
	p = (edgenode*)malloc(sizeof(edgenode));
	int data;
	printf("%c ", g->verlist[i].vertex);
	dfn_5[i] = count_5++;
	visited_5[i] = 1;
	push(i, s);
	while (!empty(s))
	{
		data = top(s);
		p = g->verlist[data].firstedge;   //ͷָ��
		while (p)   //ĳ������������ڽӵ㶼������
		{
			if (!visited_5[p->adjvex])
			{
				visited_5[p->adjvex] = 1;
				printf("%c ", g->verlist[p->adjvex].vertex);
				dfn_5[p->adjvex] = count_5++;
				push(p->adjvex, s);
				data = top(s);
				p = g->verlist[data].firstedge;
			}
			else
				p = p->next;
		}
		if (p == NULL)
			pop(s);
	}
}
//�ڽӱ�ǵݹ���������

void no_DFStraverse(adjgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_5[i] = 0;            //��������ʼ��
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_5[i])
		{
			no_DFS1(g, i);
		}
	}
}
//�ڽӱ�����ǵݹ����㷨

void no_DFS2(mtgraph* g, int i)
{
	stack* s;
	s = (stack*)malloc(sizeof(stack));
	makenull(s);
	int data,j;
	printf("%c ", g->verlist[i]);
	dfn_6[i] = count_6++;
	visited_6[i] = 1;
	push(i, s);
	while (!empty(s))
	{
		data = top(s);   //����ȡջ��Ԫ��
		for (j = 0; j < g->n; j++)
		{
			if (g->edge[data][j]&&!visited_6[j])
			{
				printf("%c ", g->verlist[j]);   //��ӡѹջ
				visited_6[j] = 1;
				dfn_6[j] = count_6++;
				push(j,s);
				break;
			}
		}
		if (j==g->n)
			pop(s);      //�����data���ڽ����ʽ����˾͵���
	}
}
//�ڽӾ���ǵݹ���������

void no_DFStraverse_m(mtgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_6[i] = 0;            //��������ʼ��
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_6[i])
		{
			no_DFS2(g, i);
		}
	}
}
//�ڽӾ�������ǵݹ����㷨

int visited_3[20]; //�ڽӱ��ȹ���ʱ������
int dfn_3[20]; //�ڽӱ��ȹ㶥���������
int visited_4[20]; //�ڽӾ����ȹ���ʱ������
int dfn_4[20]; //�ڽӾ����ȹ㶥���������
int count_3 = 1;   //��¼�ڽӱ��ȹ�ı��
int count_4 = 1;   //��¼�ڽӾ����ȹ�ı��

typedef struct node22
{
	int word;
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

void enqueue_q(int T, queue* duilie)
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

int front_q(queue* duilie)
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

void BFS1(adjgraph* g,int k)
{
	int i;
	edgenode* p;
	p = (edgenode*)malloc(sizeof(edgenode));
	queue* q;
	q = (queue*)malloc(sizeof(queue));
	makenull_q(q);
	printf("%c ", g->verlist[k].vertex);
	dfn_3[k] = count_3++;
	visited_3[k] = 1;
	enqueue_q(k, q);             //������
	while (!empty_q(q))          //�ӿ���������
	{
		i = front_q(q);
		dequeue_q(q);            //vi����
		p = g->verlist[i].firstedge;      //ȡvi�ı߱�ͷָ��
		while (p)              //��vi���ڽӵ�vj���ڣ���������
		{
			if (!visited_3[p->adjvex])  //��vjδ�����ʹ�
			{
				printf("%c ", g->verlist[p->adjvex].vertex);
				dfn_3[p->adjvex] = count_3++;
				visited_3[p->adjvex] = 1;
				enqueue_q(p->adjvex, q);  //���ʹ���vj���
			}
			p = p->next;
		}
	}
}
//�ڽӱ��ȹ�����

void BFStraverse(adjgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_3[i] = 0;
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_3[i])
		{
			BFS1(g, i);
		}
	}
}
//�ڽӱ��ȹ����㷨

void BFS2(mtgraph* g,int k)
{
	int i, j;
	queue* q;
	q = (queue*)malloc(sizeof(queue));
	makenull_q(q);
	printf("%c ", g->verlist[k]);
	dfn_4[k] = count_4++;
	visited_4[k] = 1;
	enqueue_q(k, q);  //������
	while (!empty_q(q))
	{
		i = front_q(q);
		dequeue_q(q);            //vi����
		for (j = 0; j < g->n; j++)       //��������vi���ڽӵ�vj
		{
			if (g->edge[i][j] == 1 && !visited_4[j])  //��vjδ�����ʹ�
			{
				printf("%c ", g->verlist[j]);
				dfn_4[j] = count_4++;
				visited_4[j] = 1;
				enqueue_q(j, q);  //���ʹ���vj���
			}
		}
	}
}
//�ڽӾ����ȹ�����

void BFStraverse_m(mtgraph* g)
{
	int i;
	for (i = 0; i < g->n; i++)
	{
		visited_4[i] = 0;
	}
	for (i = 0; i < g->n; i++)
	{
		if (!visited_4[i])
		{
			BFS2(g, i);
		}
	}
}
//�ڽӾ����ȹ����㷨

void menu()
{
	printf("================================\n");
	printf("1.���ļ��ж�������ͼ���ڽӾ���洢\n");
	printf("2.���ļ��ж�������ͼ���ڽӱ�洢\n");
	printf("3.��ӡ�ڽӾ���\n");
	printf("4.��ӡ�ڽӱ�\n");
	printf("5.�ڽӾ���ת�����ڽӱ�\n");
	printf("6.�ڽӱ�ת��Ϊ�ڽӾ���\n");
	printf("7.�ڽӾ���ݹ���������\n");
	printf("8.�ڽӱ�ݹ���������\n");
	printf("9.�ڽӾ���ǵݹ���������\n");
	printf("10.�ڽӱ�ǵݹ���������\n");
	printf("11.�ڽӾ����ȹ�����\n");
	printf("12.�ڽӱ��ȹ�����\n");
	printf("================================\n");
}
//�˵�

int main()
{
	int a,i;
	mtgraph* k;
	k = (mtgraph*)malloc(sizeof(mtgraph));
	adjgraph* k2;
	k2 = (adjgraph*)malloc(sizeof(adjgraph));
	//
	adjgraph* p;
	p = (adjgraph*)malloc(sizeof(adjgraph));
	mtgraph* p2;
	p2 = (mtgraph*)malloc(sizeof(mtgraph));
	menu();
	while (1)
	{
		printf("��������Ĳ�����");
		scanf(" %d", &a);
		switch (a)
		{
		case 1:
            createmgraph(k);
			break;
		case 2:
			creategraph(p);
			break;
		case 3:
			printmgraph(k);
			printf("\n");
			break;
		case 4:
			printgraph(p);
			printf("\n");
			break;
		case 5:
			trans_to_graph(k, k2);
			printf("ת������ڽӱ�Ϊ��\n");
			printgraph(k2);
			printf("\n");
			break;
		case 6:
			trans_to_mgraph(p, p2);
			printf("ת������ڽӾ���Ϊ��\n");
			printmgraph(p2);
			printf("\n");
			break;
		case 7:
			printf("�ڽӾ���ݹ���������Ϊ��");
			DFStraverse_m(k);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_2[i]);
			printf("\n\n");
			break;
		case 8:
			printf("�ڽӱ�ݹ���������Ϊ��");
			DFStraverse(p);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_1[i]);
			printf("\n\n");
			break;
		case 9:
			printf("�ڽӾ���ǵݹ���������Ϊ��");
			no_DFStraverse_m(k);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_6[i]);
			printf("\n\n");
			break;
		case 10:
			printf("�ڽӱ�ǵݹ���������Ϊ��");
			no_DFStraverse(p);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_5[i]);
			printf("\n\n");
			break;
		case 11:
			printf("�ڽӾ����ȹ�����Ϊ��");
			BFStraverse_m(k);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_4[i]);
			printf("\n\n");
			break;
		case 12:
			printf("�ڽӱ��ȹ�����Ϊ��");
			BFStraverse(p);
			printf("\n��Ӧ�ı��Ϊ��");
			for (i = 0; i < p->n; i++)
				printf("%d ", dfn_3[i]);
			printf("\n\n");
			break;
		default:
			printf("��������ȷ����!\n");
		}
	}
	return 0;
}
