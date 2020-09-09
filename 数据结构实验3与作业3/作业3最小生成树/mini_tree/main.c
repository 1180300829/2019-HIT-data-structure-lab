#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

#define chang 12
#define bian 39

typedef struct
{
	char verlist[20]; //�����
	int edge[20][20]; //�߱�
	int n, e; //ͼ�Ķ������ͱ���
}mtgraph;
//ͼ���ڽӾ���

typedef struct edge
{
	int bgn;
	int end;
	int wet;
}EGDE;
//�ߵĽڵ�

int c[chang+1][chang+1];  //����Prim�㷨��Ҫ�ĳ�������c

void prim(mtgraph *g)
{
	int lowcost[chang+1], closset[chang+1], i, j, k, min,m=0,n=0;
	for (i = 2; i <= chang; i++)   //��ʼ������lowcost��closset
	{
		lowcost[i] = c[1][i];
		closset[i] = 1;
	}
	for (i = 2; i <= chang; i++)
	{
		min = lowcost[i];
		k = i;
		for (j = 2; j <= chang; j++)  //��lowcost��ѡ��̱ߣ�����closset�ж�Ӧ�Ķ������k
		{
			if (lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		lowcost[k] = 10000;     //�ѷ��ʹ��õ������Ϊ10000
		for (j = 2; j <= chang; j++)
		{
			if (c[k][j] < lowcost[j]&& lowcost[j]!=10000)
			{
				lowcost[j] = c[k][j];
				closset[j] = k;
			}
		}
	}
	printf("Prim�㷨��С�������ĸ��ߵ����ӵ�Ϊ��\n");
	for (i = 2; i <= chang; i++)   //����С�������ıߵ����ӵ����������Ϣ����������point��
	{
		printf("(%c,%c)\n", g->verlist[i-1], g->verlist[closset[i]-1]);
	}
}
//Prim�㷨����С������

void createmgraph(mtgraph* g)
{
	int i, j, m, n,o;
	FILE* fp;
	fp = fopen("read_mini_picture.txt", "r");
	if (fp == NULL)
	{
		printf("���ļ���ʧ��\n");
		exit(0);
	}
	fscanf(fp, "%d", &g->n);
	fscanf(fp, "%d", &g->e);
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			g->edge[i][j] = INT_MAX;
		}
	}
	for (i = 0; i < g->n; i++)
	{
		fscanf(fp, " %c", &g->verlist[i]);
	}
	for (i = 0; i < g->e; i++)
	{
		fscanf(fp, "%d,%d,%d", &m, &n, &o);
		g->edge[m - 1][n - 1] = o;
		g->edge[n - 1][m - 1] = o;
	}
}
//���ļ��ж�������ͼ���ڽӾ���洢

void create_c(mtgraph* g)
{
	int i,j;
	for (i = 1; i <= g->n; i++)   //�е�ĳ�ʼ��
	{
		c[0][i] = i;
	}
	for (i = 1; i <= g->n; i++)   //�е�ĳ�ʼ��
	{
		c[i][0] = i;
	}
	for (i = 1; i <= g->n; i++)
	{
		for (j = 1; j <= g->n; j++)
		{
			c[i][j] = g->edge[i - 1][j - 1];  //�����ڽӾ����е���Ϣ
		}
	}
}
//�ö�����ڽӾ�����Prim�㷨��Ҫ�ĳ�������c

int find(int father[], int v)
{
	int f = v;
	while (father[f] > 0)
	{
		f = father[f];
	}
	return f;
}
//Ѱ������

void sort(EGDE edge[],int e)
{
	int i, j, temp1,temp2,temp3;
	for (i = 0; i < e; i++)
	{
		for (j = 0; j <e - i; j++)
		{
			if (edge[j].wet > edge[j + 1].wet)
			{
				temp1 = edge[j + 1].bgn;
				edge[j + 1].bgn = edge[j].bgn;
				edge[j].bgn = temp1;
				temp2 = edge[j + 1].end;
				edge[j + 1].end = edge[j].end;
				edge[j].end = temp2;
				temp3 = edge[j + 1].wet;
				edge[j + 1].wet = edge[j].wet;
				edge[j].wet = temp3;
			}
		}
	}
}
//��EGDE����������㷨

void kruskal(EGDE edge[], int e,mtgraph *g)
{
	printf("Kruskal�㷨��С�������ĸ��ߵ����ӵ�Ϊ��\n");
	int father[bian-chang+1], bnf, edf, i;
	for (i = 1; i <= e; i++)
	{
		father[i] = 0;
	}
	for (i = 1; i <= e; i++)
	{
		bnf = find(father, edge[i-1].bgn);   //�ж�����һ���ߵ��Ƿ�������ͬ����ͨ����
		edf = find(father, edge[i-1].end);
		if (bnf != edf)   //����������ͬ����ͨ�����������ӳ�һ����ͨ����
		{
			father[bnf] = edf;
			printf("(%c,%c)\n", g->verlist[edge[i-1].bgn-1], g->verlist[edge[i-1].end-1]);
		}
	}
}
//Kruskal�㷨����С������

void getedges(EGDE edge[],mtgraph *g)
{
	int i, j, k=0,m=0;
	for (i = 0; i < g->n; i++)
	{
		for (j = m; j < g->n; j++)
		{
			if (g->edge[i][j] != INT_MAX && g->edge[i][j] != 0)
			{
				edge[k].bgn = i + 1;
				edge[k].end = j + 1;
				edge[k].wet = g->edge[i][j];
				//printf("%d %d %d\n", edge[k].bgn, edge[k].end, edge[k].wet);
				k++;
			}
		}
		m++;
	}

}
//���Ѿ�������ڽӾ����еõ��������ֵ

int main()
{
	mtgraph* p;
	p = (mtgraph*)malloc(sizeof(mtgraph));
	createmgraph(p);
	create_c(p);
	prim(p);
	//
	printf("\n");
	mtgraph* k;
	EGDE edges[bian-chang];
	int e;
	k = (mtgraph*)malloc(sizeof(mtgraph));
	createmgraph(k);
	getedges(edges, k);
	e = bian - chang;
	sort(edges, e);
	kruskal(edges, e,k);
	return 0;
}
