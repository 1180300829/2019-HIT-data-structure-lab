#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct
{
	char ch; //储存被编码的字符
	int count; //字符出现次数
	char bits[300]; //字符编码位串
}codenode;
//单个字符编码结构体

typedef struct
{
	codenode weight;
	int lchild;
	int rchild;
	int parent;
}htnode;
//哈夫曼树静态三叉链表

codenode array[128];   //储存各种字符的信息
int number;  //字符的种类个数

void initht(htnode* t)
{
	int i;
	for (i = 0; i < (2 * number - 1); i++)
	{
		t[i].lchild = -1;
		t[i].rchild = -1;
		t[i].parent = -1;
	}
}
//初始化

void input(htnode* t)
{
	int i;
	for (i = 0; i < number; i++)
	{
		t[i].weight.ch = array[i].ch;
		t[i].weight.count = array[i].count;
	}
}
//输入叶节点的权值

void selectmin(htnode* t, int n, int* p1, int* p2)
{
	int i, j;
	for (i = 0; i <= n; i++)
	{
		if (t[i].parent == -1)
		{
			*p1 = i;
			break;
		}
	}
	for (j = i + 1; j <= n; j++)
	{
		if (t[j].parent == -1)
		{
			*p2 = j;
			break;
		}
	}
	for (i = 0; i <= n; i++)
	{
		if ((t[*p1].weight.count > t[i].weight.count) && (t[i].parent == -1) && (*p2 != i))
		{
			*p1 = i;
		}
	}
	for (j = 0; j <= n; j++)
	{
		if ((t[*p2].weight.count > t[j].weight.count) && (t[j].parent == -1) && (*p1 != j))
		{
			*p2 = j;
		}
	}
}
//求两个最小的权值

void createht(htnode* t)
{
	int i, p1, p2;
	initht(t);      //初始化
	input(t);      //输入权值
	for (i = number; i < (2 * number - 1); i++)
	{
		selectmin(t, i - 1, &p1, &p2);
		t[p1].parent = t[p2].parent = i;
		t[i].lchild = p1;
		t[i].rchild = p2;
		t[i].weight.count = t[p1].weight.count + t[p2].weight.count;
		t[p1].weight.count = 1000; //表示该处已被访问过
		t[p2].weight.count = 1000;
	}
}
//构造哈夫曼树

void paixu()
{
	char mm;
	int i, j, temp;
	for (j = 0; j < number - 1; j++)
	{
		for (i = 0; i < number - 1 - j; i++)
		{
			if (array[i].count < array[i + 1].count)
			{
				temp = array[i].count;
				array[i].count = array[i + 1].count;
				array[i + 1].count = temp;
				mm = array[i].ch;
				array[i].ch = array[i + 1].ch;
				array[i + 1].ch = mm;
			}
		}
	}
}
//排序方便观察哈夫曼编码

int readcompress()
{
	FILE* fp;
	char ch;
	int flag, i, counter = 0;
	fp = fopen("read_to_compress.txt", "rb");
	if (fp == NULL)
	{
		printf("读入文件read_to_compress.txt失败\n");
		exit(0);
	}
	printf("待压缩文件已经成功读入\n");
	number = 0;
	while (1)
	{
		if ((ch = fgetc(fp)) == EOF)
		{
			break;
		}
		counter++;
		flag = 0;
		for (i = 0; i < number; i++)
		{
			if (ch == array[i].ch)
			{
				array[i].count++;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			array[number].ch = ch;
			array[number].count = 1;
			number++;
		}
	}
	fclose(fp);
	for (i = 0; i < number; i++)
	{
		printf("字符%c出现次数为：%d   对应ascii码为%d\n", array[i].ch, array[i].count, array[i].ch);
	}
	printf("待压缩文件的总字节数为：%d\n", counter);
	printf("\n");
	return counter;
}
//读入待压缩文件，并返回读入总字节数

void hufmanencoding(htnode* t)
{
	int c, p, i;
	char cd[300]= { 'm' };
	int start;
	cd[299] = '\0';
	for (i = 0; i < number; i++)
	{
		c = i;
		start = number - 1;
		while ((p = t[c].parent) >= 0)
		{
			cd[--start] = (t[p].lchild == c) ? '0' : '1';
			c = p;  //继续上溯;
		}
		strcpy(t[i].weight.bits, &cd[start]);
	}
	for (int m = 0; m < number; m++)
	{
		printf("字符%c的哈夫曼编码：%s\n", t[m].weight.ch, t[m].weight.bits);
	}
}
//进行编码，将编码保存到weight.bits[300]中，并打印每个字符的哈夫曼编码

int write_hufman(htnode* t)
{
	FILE* fp_r, * fp_w;
	int i;
	char c;
	fp_r = fopen("read_to_compress.txt", "rb");
	fp_w = fopen("write_in_hufmancode.txt", "wb");
	if (fp_r == NULL)
	{
		printf("读入文件read_to_compress.txt失败！\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("以哈夫曼编码写入文件write_in_hufmancode.txt失败！\n");
		exit(0);
	}
	while (1)
	{
		if ((c = fgetc(fp_r)) == EOF)
		{
			break;
		}
		for (i = 0; i < number; i++)
		{
			if (t[i].weight.ch == c)
			{
				fputs(t[i].weight.bits, fp_w);
			}
		}
	}
	fclose(fp_r);
	fclose(fp_w);
}
//以哈夫曼编码形式把原文档写入write_in_hufmancode.txt中

int writecompress()
{
	FILE* fp_r, * fp_w;
	int i,j,zongshu=0,zushu,yuxia,zu=0;
	char c='\0',ch;
	char m[8];
	fp_r = fopen("write_in_hufmancode.txt", "rb");
	fp_w = fopen("write_to_compress.txt", "wb");
	if (fp_r == NULL)
	{
		printf("读入文件read_to_compress.txt失败！\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("写入文件write_in_hufmancode.txt失败！\n");
		exit(0);
	}
	do
	{
		ch = fgetc(fp_r);
		zongshu++;
	} while (ch != EOF);
	zongshu--;
	fclose(fp_r);
	fp_r = fopen("write_in_hufmancode.txt", "rb");
	zushu = zongshu / 8;
	yuxia = zongshu % 8;
	//printf("%d\n%d\n%d\n", zongshu, zushu, yuxia);
	while (!feof(fp_r))
	{
		if (zu <= zushu)
		{
			for (i = 0; i < 8; i++)
			{
				m[i] = fgetc(fp_r);
			}
			for (j = 0; j < 8; j++)
			{
				if (m[j] == '1')
				{
					c = (c << 1) | 1;
				}
				else
				{
					c = c << 1;
				}
			}
			fputc(c, fp_w);
			zu++;
			c = '\0';
		}
		else
		{
			for (i = 0; i < yuxia; i++)
			{
				m[i] = fgetc(fp_r);
			}
			for (j = 0; j < yuxia; j++)
			{
				if (m[j] == '1')
				{
					c = (c << 1) | 1;
				}
				else
				{
					c = c << 1;
				}
			}
			fputc(c, fp_w);
			c = '\0';
		}
	}
	printf("\n压缩后的字节数为%d\n", zu + 1);
	fclose(fp_r);
	fclose(fp_w);
	return zu + 1;
}
//压缩写入文件write_to_compress.txt中

void menu()
{
	printf("--------------------------------------");
	printf("1.读入压缩文件\n");
	printf("2.构建哈夫曼树\n");
	printf("3.");
}

void decompress(htnode* t)
{
	FILE* fp_r, *fp_w;
	int i = 0,j,k;
	char p[100] = {'\0'};
	fp_r = fopen("write_in_hufmancode.txt","rb");
	fp_w = fopen("write_to_decompress.txt","wb");
	if (fp_r == NULL)
	{
		printf("读入文件write_in_hufmancode失败！\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("写入文件write_to_decompress.txt失败！\n");
		exit(0);
	}
	while (1)
	{
		if ((p[i] = fgetc(fp_r)) == EOF) 
		{ 
			break;
		}
		i++;
		for (j = 0; j < number; j++)
		{
			if (strcmp(p, t[j].weight.bits) == 0)
			{
				fputc(t[j].weight.ch, fp_w);
				i = 0;
				for (k = 0; k < 100; k++)
				{
					p[k] = '\0';
				}
			}
		}	
	}
	fclose(fp_r);
	fclose(fp_w);
	printf("成功解压压缩文件\n");
}
//解压缩写入write_to_compress.txt中

int main()
{
	htnode* HT;
	int p, q;
	p=readcompress();
	//paixu();
	HT = (htnode*)malloc((2 * number - 1) * sizeof(htnode));
	createht(HT);
	hufmanencoding(HT);
	write_hufman(HT);
	q=writecompress();
	printf("\n压缩率为%f\n", (float)q / (float)p);
	printf("\n");
	decompress(HT); 
	return 0;
}

