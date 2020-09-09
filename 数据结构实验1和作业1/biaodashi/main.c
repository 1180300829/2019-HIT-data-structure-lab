#include<stdio.h>
#include<stdlib.h>
#define mysize 200
typedef struct      //�ַ�ջ
{
	char data[mysize];
	int top;
	int base;
}STACK_zifu;

typedef struct      //����ջ
{
	float data[mysize];
	int top;
	int base;
}STACK_shuju;
//���ַ�ջ�ÿ�
void Makenull_zifu(STACK_zifu* s)
{
	s->top = 0;
	s->base = 0;
}
//������ջ�ÿ�
void Makenull_shuju(STACK_shuju* s)
{
	s->top = 0;
	s->base = 0;

}
//�ж��ַ�ջ�Ƿ�Ϊ��
int Empty_zifu(STACK_zifu* s)
{
	if (s->base == s->top)
		return 1;
	else
		return 0;

}
//�ж�����ջ�Ƿ�Ϊ��
int Empty_shuju(STACK_shuju* s)
{
	if (s->base == s->top)
		return 1;
	else
		return 0;

}
//�����ַ�ջջ��Ԫ��
char Top_zifu(STACK_zifu* s)
{
	if (s->top == s->base)
		return 0;
	return (s->data[s->top - 1]);

}
//��������ջջ��Ԫ��
float Top_shuju(STACK_shuju* s)
{
	if (s->top == s->base)
		return 0;
	return (s->data[s->top - 1]);
}
//���ַ�xѹ���ַ�ջ��ջ��
void Push_zifu(char x, STACK_zifu* s)
{
	s->data[s->top] = x;
	s->top++;
}
//������xѹ���ַ�ջ��ջ��
void Push_shuju(float x, STACK_shuju* s)
{
	s->data[s->top] = x;
	s->top++;
}
//ɾ���ַ�ջջ����Ԫ�ز�����ջ��Ԫ��
char Pop_zifu(STACK_zifu* s)
{
	char e;
	if (s->base == s->top)
		return 0;
	else
	{
		e = s->data[s->top - 1];
		s->top--;
	}
	return e;
}
//ɾ������ջջ����Ԫ�ز�����ջ��Ԫ��
float Pop_shuju(STACK_shuju* s)
{
	float e;
	if (s->base == s->top)
		return 0;
	else
	{
		e = s->data[s->top - 1];
		s->top--;
	}
	return e;
}
//����һ���������ϰ���(),+,-,*,/,%
char operation[8] = { '(',')','+','-','*','/','%','!' };  //'!'��Ϊջ�ױ�־ 
//�ж������ַ��Ƿ�����֪�����������,���ǣ��򷵻�1
int Judge(char m, char* test)
{
	int p = 0, i;
	for (i = 0; i < 7; i++)
	{
		if (m == test[i])
		{
			p = 1;
		}
	}
	return p;
}
//�ж������������a,b�����ȼ�
int Level(char a, char b)
{
	int i, the_a, the_b;
	switch (a)
	{
	case'!':
		the_a = 0;
		break;
	case'(':
		the_a = 1;
		break;
	case')':
		the_a = 1;
		break;
	case'+':
		the_a = 2;
		break;
	case'-':
		the_a = 2;
		break;
	case'*':
		the_a = 3;
		break;
	case'/':
		the_a = 3;
		break;
	case'%':
		the_a = 3;
		break;
	}
	switch (b)
	{
	case'!':
		the_a = 0;
		break;
	case'(':
		the_b = 1;
		break;
	case')':
		the_b = 1;
		break;
	case'+':
		the_b = 2;
		break;
	case'-':
		the_b = 2;
		break;
	case'*':
		the_b = 3;
		break;
	case'/':
		the_b = 3;
		break;
	case'%':
		the_b = 3;
		break;
	}
	if (the_a >= the_b)
		return 1;
	else
		return 0;
}
//����׺���ʽת��Ϊ��׺���ʽ
void Transform(char* s1, char* s2)
{
	STACK_zifu one;
	char ch;
	int i = 0, j = 0;
	Makenull_zifu(&one); //��oneջ�ÿ�
	Push_zifu('!', &one);   //��'!'����ջ�� 
	for (; s1[i] != '\0';)
	{
		if (Judge(s1[i], operation) == 0) //�������������ͷ����������s2
		{
			while ((s1[i] >= '0' && s1[i] <= '9') || s1[i] == '.') //С�������������һ����
			{
				s2[j++] = s1[i];
				i++;
			}
			s2[j++] = ' ';   //����һ���ո�
		}
		else    //����������
		{
			switch (s1[i])
			{
			case'(':
				i++;
				if (s1[i] == '-')  //�ж��Ƿ�Ϊ���������ǣ��򽫸�����������s2�������ǣ�������������ջ��
				{
					while (s1[i] != ')')
					{
						s2[j++] = s1[i];
						i++;
					}
					s2[j++] = ' ';//�ո���Ϊ���
					i++;
				}
				else
				{
					i--;
					Push_zifu(s1[i], &one);
					i++;
				}
				break;
			case')':
				ch = Pop_zifu(&one);
				do             //���)��(��ջ�е����������
				{
					s2[j++] = ch;
					s2[j++] = ' ';  //�ո���Ϊ���
					ch = Pop_zifu(&one);
				} while (ch != '(');
				i++;
				break;
			default:
				while (Level(Top_zifu(&one), s1[i]) == 1)  //�ж�����������ȼ���ʹջ��Ԫ����Զ���ȼ����
				{
					s2[j++] = Pop_zifu(&one);
					s2[j++] = ' ';  //�ո���Ϊ���
				}
				Push_zifu(s1[i], &one);
				i++;
			}
		}
	}
	for (; Top_zifu(&one) != '!';)   //s1ɨ����ɺ󣬰�ջ�������������������s2,���ʼ����ջ�е�'!'��Ϊ��־
	{
		s2[j++] = Pop_zifu(&one);
		s2[j++] = ' ';   //�ո���Ϊ���
	}
}
//��a��bִ�����������
float Handle(float a, char panduan, float b)
{
	int d, e;
	switch (panduan)
	{
	case'+':
		return a + b;
	case'-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
		{
			printf("������ɳ�0���� \n");
			return 0;
		}
		return a / b;
		break;
	case'%':
		d = (int)a;
		e = (int)b;
		if (e == 0)
		{
			printf("������ɶ�0��ȡ������\n");
			return 0;
		}
		return (float)(d % e);
		break;
	default:
		printf("���ִ���\n");
		return 0;
	}
}
//�����׺���ʽ��ֵ
int main()
{
	STACK_shuju two;
	char c, ch;
	int i = 0, step = 0, j = 0;
	float a = 0, b = 0, s = 0;
	do
	{
		i = 0;
		char jianpan[200] = { 0 }, shuchu[200] = { 0 };
		Makenull_shuju(&two);
		printf("**************************************\n");
		printf("***����������ת����һ����׺���ʽ��***\n");
		scanf("%s", jianpan);  //����һ����׺���ʽ,���ڸ������������Ҫ������
		Transform(jianpan, shuchu);
		printf("********ת����ĺ�׺���ʽΪ��********\n");
		printf("%s\n", shuchu);  //���ת����ĺ�׺���ʽ
		ch = shuchu[0];
		while(ch != '\0')     //�����׺���ʽ��ֵ
		{
			if (Judge(shuchu[i], operation) == 0) //��������������ѹ��ջ��
			{
				s = 0;
				a = b = step = 0;
				while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != '.' && shuchu[i] != ' ')//���С����ǰ���������ֵ
				{
					s = 10 * s + shuchu[i] - 48;
					i++;
				}
				if (shuchu[i] == '.')  //���С����������ֵ
				{
					i++;
					while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != ' ')
					{
						b = 10 * b + shuchu[i] - 48;
						i++;
						step++;
					}
					for (j = 0; j < step; j++)
					{
						b = b / 10;
					}
				}
				a = s + b;   //��С�������������������
				Push_shuju(a, &two);
				ch = shuchu[++i];
			}
			else if (shuchu[i] == '-')     //�ж�-�Ǽ��Ż��Ǹ���
			{
				i++;
				if (shuchu[i] >= '0' && shuchu[i] <= '9')   //���������Ϊ���ţ�������ø�������ѹ���ջ
				{
					s = 0;
					a = b = step = 0;
					while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != '.' && shuchu[i] != ' ')//���С����ǰ���������ֵ
					{
						s = 10 * s + shuchu[i] - 48;
						i++;
					}

					if (shuchu[i] == '.')//���С����������ֵ
					{
						i++;
						while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != ' ')
						{
							b = 10 * b + shuchu[i] - 48;
							i++;

							step++;
						}
						for (j = 0; j < step; j++)
						{
							b = b / 10;
						}
					}
					a = -(s + b);//�������ֺ�С��������ӣ�����a��ȡ�����õ�����ֵ
					Push_shuju(a, &two);
					ch = shuchu[++i];
				}
				else            //��-Ϊ����ʱ�����������������
				{
					b = Pop_shuju(&two);
					a = Pop_shuju(&two);
					Push_shuju(Handle(a, ch, b), &two);
					ch = shuchu[++i];
				}
			}
			else            //����Ӧ����������м���
			{
				b = Pop_shuju(&two);
				a = Pop_shuju(&two);
				Push_shuju(Handle(a, ch, b), &two);
				i += 2;
				ch = shuchu[i];
			}
		}
		printf("******���õ��ĺ�׺���ʽ��ֵΪ��******\n%g\n", Top_shuju(&two));
		printf("**************************************\n");
		printf("�볢�Ը����ת��������'T'��'t'�ɼ���\n");
        getchar();
        c=getchar();
	}while(c == 'T'||c == 't');     //�����������ж�
	return 0;
}
