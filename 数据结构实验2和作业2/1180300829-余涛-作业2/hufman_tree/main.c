#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct
{
	char ch; //���汻������ַ�
	int count; //�ַ����ִ���
	char bits[300]; //�ַ�����λ��
}codenode;
//�����ַ�����ṹ��

typedef struct
{
	codenode weight;
	int lchild;
	int rchild;
	int parent;
}htnode;
//����������̬��������

codenode array[128];   //��������ַ�����Ϣ
int number;  //�ַ����������

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
//��ʼ��

void input(htnode* t)
{
	int i;
	for (i = 0; i < number; i++)
	{
		t[i].weight.ch = array[i].ch;
		t[i].weight.count = array[i].count;
	}
}
//����Ҷ�ڵ��Ȩֵ

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
//��������С��Ȩֵ

void createht(htnode* t)
{
	int i, p1, p2;
	initht(t);      //��ʼ��
	input(t);      //����Ȩֵ
	for (i = number; i < (2 * number - 1); i++)
	{
		selectmin(t, i - 1, &p1, &p2);
		t[p1].parent = t[p2].parent = i;
		t[i].lchild = p1;
		t[i].rchild = p2;
		t[i].weight.count = t[p1].weight.count + t[p2].weight.count;
		t[p1].weight.count = 1000; //��ʾ�ô��ѱ����ʹ�
		t[p2].weight.count = 1000;
	}
}
//�����������

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
//���򷽱�۲����������

int readcompress()
{
	FILE* fp;
	char ch;
	int flag, i, counter = 0;
	fp = fopen("read_to_compress.txt", "rb");
	if (fp == NULL)
	{
		printf("�����ļ�read_to_compress.txtʧ��\n");
		exit(0);
	}
	printf("��ѹ���ļ��Ѿ��ɹ�����\n");
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
		printf("�ַ�%c���ִ���Ϊ��%d   ��Ӧascii��Ϊ%d\n", array[i].ch, array[i].count, array[i].ch);
	}
	printf("��ѹ���ļ������ֽ���Ϊ��%d\n", counter);
	printf("\n");
	return counter;
}
//�����ѹ���ļ��������ض������ֽ���

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
			c = p;  //��������;
		}
		strcpy(t[i].weight.bits, &cd[start]);
	}
	for (int m = 0; m < number; m++)
	{
		printf("�ַ�%c�Ĺ��������룺%s\n", t[m].weight.ch, t[m].weight.bits);
	}
}
//���б��룬�����뱣�浽weight.bits[300]�У�����ӡÿ���ַ��Ĺ���������

int write_hufman(htnode* t)
{
	FILE* fp_r, * fp_w;
	int i;
	char c;
	fp_r = fopen("read_to_compress.txt", "rb");
	fp_w = fopen("write_in_hufmancode.txt", "wb");
	if (fp_r == NULL)
	{
		printf("�����ļ�read_to_compress.txtʧ�ܣ�\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("�Թ���������д���ļ�write_in_hufmancode.txtʧ�ܣ�\n");
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
//�Թ�����������ʽ��ԭ�ĵ�д��write_in_hufmancode.txt��

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
		printf("�����ļ�read_to_compress.txtʧ�ܣ�\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("д���ļ�write_in_hufmancode.txtʧ�ܣ�\n");
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
	printf("\nѹ������ֽ���Ϊ%d\n", zu + 1);
	fclose(fp_r);
	fclose(fp_w);
	return zu + 1;
}
//ѹ��д���ļ�write_to_compress.txt��

void menu()
{
	printf("--------------------------------------");
	printf("1.����ѹ���ļ�\n");
	printf("2.������������\n");
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
		printf("�����ļ�write_in_hufmancodeʧ�ܣ�\n");
		exit(0);
	}
	if (fp_w == NULL)
	{
		printf("д���ļ�write_to_decompress.txtʧ�ܣ�\n");
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
	printf("�ɹ���ѹѹ���ļ�\n");
}
//��ѹ��д��write_to_compress.txt��

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
	printf("\nѹ����Ϊ%f\n", (float)q / (float)p);
	printf("\n");
	decompress(HT); 
	return 0;
}

