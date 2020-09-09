#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct GOODS
{
	char name[15];   //����
	char brand[15];  //Ʒ��
	double price;    //����
	int amount;      //����
	struct GOODS* next;
}goods;
//����һ���µĽڵ�,Ϊ�丳ֵ���ҷ���ָ������ڵ��ָ��
goods* Create_newnode()
{
	goods* p;
	p = (goods*)malloc(sizeof(goods));
	if (p == NULL)         //�ж϶�̬�ڴ��Ƿ�����ɹ�
	{
		printf("û���㹻���ڴ�ɹ�����");
	}
	p->next = NULL;
	strcpy(p->name, " ");
	strcpy(p->brand, " ");
	p->price = 1;
	p->amount = 0;
	return p;
}
//Ӫҵ��ʼ����information.txt�ж���ҵ���Ϣ
void Read_file(goods* head)
{
	FILE* fp;
	goods* p = head;
	goods* q;
	q = Create_newnode();
	char name[15], brand[15];
	int price = 0, amount = 0;
	fp = fopen("information.txt", "r");    //��ֻ����ʽ���ļ�information.txt
	if (fp == NULL)
	{
		printf("����ҵ���Ϣʧ�� \n");
		exit(0);
	}
	fseek(fp, 22, 0);
	while (fscanf(fp, "%s", q->name) != EOF)    //��δ�ﵽ�ļ�ĩβǰ�����δ��ļ��ж���ڵ������
	{
		fscanf(fp, "%s", q->brand);
		fscanf(fp, "%lf", &q->price);
		fscanf(fp, "%d\n", &q->amount);
		p->next = q;
		p = q;
		q = Create_newnode();
	}
	p->next = NULL;
	fclose(fp);
}
//����������ĳ����Ʒ�����ݣ���ͬʱ�ÿ����Ƿ������������Ʒ
void Insert_data(goods* head)
{
	goods* p = head;
	goods* s = head;
	goods* q;
	p=Create_newnode();
	printf("��ֱ���������ҵ�����ƣ�Ʒ�ƣ����ۣ������� \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	if (head->next == NULL)  //�ж�head�Ƿ�Ϊβ���,���ǣ�����ָ���½��ڵ�p
	{
		head->next = p;
	}
	else
	{
		while ((p->price)>(s->next->price)) //���������ǵ��������������Բ���λ��ͨ���۸�ıȽϼ���ȷ��Ϊs->next֮ǰ
		{
			s = s->next;
			if (s->next == NULL)
			{
				break;
			}
		}
		if (s->next != NULL)          //��s����β���
		{
			if (strcmp(p->name, s->next->name) == 0 && strcmp(p->brand, s->next->brand) == 0) //�жϽ����ҵ��Ƿ�Ϊ������Ʒ�����ǣ���������һ����
			{
				s->next->amount += p->amount;
			}
			else        //��s->next֮ǰ�����½ڵ�p
			{
				q = s->next;
				s->next = p;
				p->next = q;
			}
		}
		else    //��sΪβ��㣬��ֱ���ڽڵ��������½ڵ�
		{
			s->next = p;
			p->next = NULL;
		}
	}
}
//�����������Ϊ������·��� 
void Insert_data_noinput(goods* head,goods* p)
{
	goods* s = head;
	goods* q;
    if (head->next == NULL)  //�ж�head�Ƿ�Ϊβ���,���ǣ�����ָ���½��ڵ�p
	{
		head->next = p;
	}
	else
	{
		while ((p->price)>(s->next->price)) //���������ǵ��������������Բ���λ��ͨ���۸�ıȽϼ���ȷ��Ϊs->next֮ǰ
		{
			s = s->next;
			if (s->next == NULL)
			{
				break;
			}
		}
		if (s->next != NULL)          //��s����β���
		{
			if (strcmp(p->name, s->next->name) == 0 && strcmp(p->brand, s->next->brand) == 0) //�жϽ����ҵ��Ƿ�Ϊ������Ʒ�����ǣ���������һ����
			{
				s->next->amount += p->amount;
			}
			else        //��s->next֮ǰ�����½ڵ�p
			{
				q = s->next;
				s->next = p;
				p->next = q;
			}
		}
		else    //��sΪβ��㣬��ֱ���ڽڵ��������½ڵ�
		{
			s->next = p;
			p->next = NULL;
		}
	}
}
//�����ͬʱ���Ǵ���Ƿ��㹻�������������������
void Delete_data(goods* head)
{
	goods* q = head;
	goods* p = head;
	goods* s, * r;
	p=Create_newnode();
	printf("��ֱ���������ҵ�����ƣ�Ʒ�ƣ����ۣ������� \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	if (head->next == NULL)  //�����Ҫ��ѯ�ļҵ���β�ڵ㣬��˵���޴���Ʒ
	{
		printf("û�д���Ʒ \n");
	}
	else
	{
		while (strcmp(q->next->brand, p->brand) != 0 || strcmp(q->next->name, p->name) != 0) //���δ�ͷ�����Ƿ��д�ȡ������Ʒֱ����β
		{
			q = q->next;
			if (q->next == NULL)
			{
				break;
			}
		}
		if (q->next != NULL)
		{
			if (q->next->amount == p->amount)  //�����ȡ���������������
			{
				if (q->next->next == NULL)  //������˱�β����ɾ��q->next,���ͷ�q->next
				{
					s = q->next;
					q->next = NULL;
					free(s);
				}
				else     //��û�е����β����ɾ��q->next,���ͷ�q->next
				{
					s = q->next->next;
					r = q->next;
					q->next = s;
					free(r);
				}
			}
			else   //����ȡ�����������治���
			{
				if (q->next->amount < p->amount)  //����ȡ�����������ڿ��
					printf("����ȱ���޷�ʵ�ֲ����������²���\n\n");
				else     //����ȡ��������С�ڿ�棬���ÿ���ȥ��ȡ����������ʣ����
					q->next->amount -= p->amount;
			}
		}
	}
}
//��ѯ��Ϣ�������β�ѯÿ���ڵ����Ϣ
void Watch_data(goods* head)
{
	goods* p = head->next;
	printf("����\tƷ��\t����\t\t����:\n");
	while (p != NULL) //ֻҪû������β
	{
		printf("%s\t%s\t%lf\t%d\n", p->name, p->brand, p->price, p->amount);
		p = p->next;
	}
	printf("\n\n");
}
//������Ϣ�����䶯����Ʒ��Ϣ���¸�ֵ
void Refresh_data(goods* head)
{
	goods* p;
	goods* s;
	goods* q = head;
	goods* m;
	goods* n=head;
	p = Create_newnode();
	printf("��ֱ�������¼ҵ�����ƣ�Ʒ�ƣ����ۣ������� \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	while (strcmp(q->next->brand, p->brand) != 0 || strcmp(q->next->name, p->name) != 0)   //Ѱ������ҵ��������λ�ã�������ȣ���qΪ��һ���ڵ�
	{
		q = q->next;
	}
	if (q->next->next == NULL)//��q->next���˱�β,���ͷ�ԭ�ڵ㣬��ִ����������� 
    {
		s=q->next;
		free(s);
		q->next=NULL;
		Insert_data_noinput(n,p); 
    }
	else//��û�е����β�����ͷ�ԭ�ڵ㣬�ı�ָ��ָ��ִ�����������
	{
		s=q->next;
		m=s->next;
		free(s);
		q->next=m;
		Insert_data_noinput(n,p); 
    }
}	
//Ӫҵ��������information.txt��д��ҵ���Ϣ
int Save_file(goods* head)//��������
{
	FILE* fp;
	goods* p = head->next;
	fp = fopen("information.txt", "w");  //��ֻд��ʽ��information.txt
	if (fp == NULL)
	{
		printf("д��ҵ���Ϣʧ��\n");
		return -1;
	}
	fprintf(fp, "����\t Ʒ��\t �۸�\t ����\n");
	while (p != NULL)
	{
		fprintf(fp, "%s\t %s\t %lf\t %d\n", p->name, p->brand, p->price, p->amount);
		p = p->next;
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}
//������
void Create_list(goods* head)
{
	Read_file(head);
	printf("Ӫҵ��ʼ����Ʒ��Ϣ�Ѷ��룬�����ѡ�����: \n");
}
//�����˵�
int Menu()
{
	int m;
	printf("***********************************\n");
	printf("w e l c o m e\n");
	printf("��ӭ�����̳��ҵ���Ϣά��ϵͳ��\n");
	printf("1.Ӫҵ��ʼ\n");
	printf("2.����\n");
	printf("3.���\n");
	printf("4.��ѯ��Ϣ\n");
	printf("5.������Ϣ\n");
	printf("6.�˳�ϵͳ\n\n");
	printf("***********************************\n");
	printf("��ѡ����Ҫִ�еĲ�����\n");
	scanf("%d", &m);
	printf("\n");
	return m;
}
int main()
{
	goods* head;
	char a;
	head = Create_newnode();
	printf("***********************************\n");
	printf("ע�⣺����ѡ��1����������Ʒ��Ϣ\n");
	while (1)
	{
		a = Menu();
		switch (a)
		{
		case 1:
			Create_list(head);
			break;
		case 2:
			Insert_data(head);
			break;
		case 3:
			Delete_data(head);
			break;
		case 4:
			Watch_data(head);
			break;
		case 5:
			Refresh_data(head);
			break;
		case 6:
			printf("Ӫҵ����,�ҵ���Ϣ�ѱ���\n");
			Save_file(head);
			exit(0);
		default:printf("��������ȷ���!\n");
		}
	}
	return 0;
}
