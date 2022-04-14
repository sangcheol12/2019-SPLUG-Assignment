#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Client
{
	char name[10];
	char address[30];
	char phoneNum[20];
	struct Client *next;
}Client;
typedef struct list
{
	Client *head;
	Client *tail;
}List;
void Menu(char **munuPtr,int size_menu);
void createList(List *lp);
void callFile(List *lp);
void displayList(List *lp);
void addClient(List *lp);
void searchClient(List *lp);
void ModifyClient(List *lp);
void removeClient(List *lp);
void saveData(List *lp);
void destoryList(List *lp);
int main()
{
	char ch;
	int dn,menuSelect=0;
	List list;
	Client *tp;
	char *ptrAryMenu[]={"��� �ּҷ� ���� ���","ȸ�� ���","ȸ�� ���� �˻�","ȸ�� ���� ����", "ȸ�� ����","���α׷� ����"};
	int size_menu;
	size_menu=(sizeof(ptrAryMenu)/sizeof(ptrAryMenu[0]));
	createList(&list);
	callFile(&list);
	while(1)
	{
		Menu(ptrAryMenu,size_menu);
		printf("================================\n");
		printf("������ ����� �Է��ϼ��� : ");
		scanf("%d",&menuSelect);
		while(menuSelect<1 || menuSelect>6)
		{
			while(getchar()!='\n');
			printf("������ ����� �Է��ϼ��� : ");
			scanf("%d",&menuSelect);
		}
		getchar();
		printf("================================\n");
		if(menuSelect==6)
			break;
		switch(menuSelect)
		{
			case 1:
				displayList(&list);
				break;
			case 2:
				addClient(&list);
				break;
			case 3:
				searchClient(&list);
				break;
			case 4:
				ModifyClient(&list);
				break;
			case 5:
				removeClient(&list);
				break;
		}
		saveData(&list);
	}
	destoryList(&list);
}
void Menu(char **menuPtr,int size_menu)
{
	int i;
	for(i=0; i<size_menu; i++)
		printf("%d. %s\n",i+1,menuPtr[i]);
}
void createList(List *lp)
{
	lp->head=(Client *)malloc(sizeof(Client));
	lp->tail=(Client *)malloc(sizeof(Client));
	lp->head->next=lp->tail;
	lp->tail->next=lp->tail;
}
void displayList(List *lp)
{
	int i=1;
	Client *curp;
	curp=lp->head->next;
	while(curp!=lp->tail)
	{
		printf("#%d\n�̸� : %s\n�ּ� : %s\n��ȭ��ȣ : %s\n",i,curp->name,curp->address,curp->phoneNum);
		curp=curp->next;
		i++;
		printf("================================\n");
	}
}
void callFile(List *lp)
{
	FILE *sp=fopen("���÷�_���_����.txt","r+");
	int dn;
	Client *tp;
	char c;
	while(1)
	{
		dn=0;
		Client *myclient;
		myclient=(Client *)malloc(sizeof(Client));
		dn+=fscanf(sp,"%[^,]s",myclient->name);
		fscanf(sp,"%c",&c);
		dn+=fscanf(sp,"%[^,]s",myclient->address);
		fscanf(sp,"%c",&c);
		dn+=fscanf(sp,"%[^\n]s",myclient->phoneNum);
		fscanf(sp,"%c",&c);
		if(dn!=3)
		{
			free(myclient);
			fclose(sp);
			return ;
		}
		tp=lp->head;
		while(1)
		{
			if(tp->next==lp->tail)
			{
				myclient->next=lp->tail;
				tp->next=myclient;
				break;
			}
			if(strcmp(tp->next->name,myclient->name)>=0)
			{
				myclient->next=tp->next;
				tp->next=myclient;
				break;
			}
			else
			{
				tp=tp->next;
			}
		}
	}
}
void addClient(List *lp)
{
	Client *tp;
	Client *myclient;
	myclient=(Client *)malloc(sizeof(Client));
	printf("�̸� : ");
	scanf("%[^\n]s",myclient->name);
	getchar();
	printf("�ּ� : ");
	scanf("%[^\n]s",myclient->address);
	getchar();
	printf("��ȭ��ȣ : ");
	scanf("%[^\n]s",myclient->phoneNum);
	getchar();
	printf("\n�߰��Ǿ����ϴ�.\n");
	printf("================================\n");
	tp=lp->head;
	while(1)
	{
		if(tp->next==lp->tail)
		{
			myclient->next=lp->tail;
			tp->next=myclient;
			break;
		}
		if(strcmp(tp->next->name,myclient->name)>=0)
		{
			myclient->next=tp->next;
			tp->next=myclient;
			break;
		}
		else
		{
			tp=tp->next;
		}
	}
}
void searchClient(List *lp)
{
	char data[10];
	int t=0,datalen,namelen,p,k;
	char *cmpData;
	printf("ã���ô� ȸ���� �̸��� �Է��ϼ��� : ");
	scanf("%[^\n]s",data);
	getchar();
	Client *curp;
	curp=lp->head->next;
	datalen=strlen(data);
	while(curp!=lp->tail)
	{
		k=p=0;
		namelen=strlen(curp->name);
		while(p<=namelen-datalen)
		{
			if((*(curp->name)+p)==data[0])
			{
				for(int i=0; i<datalen; i++)
				{
					if((*(curp->name)+p)==data[i])
						k=1;
				}
			}
			p++;
		}
		if(k==1)
		{
			printf("#%d\n",t+1);
			printf("�̸� : %s\n�ּ�: %s\n��ȭ��ȣ : %s\n",curp->name,curp->address,curp->phoneNum);
			printf("================================\n");
			t++;
		}
		curp=curp->next;
	}
	if(t==0)
	{

		printf("ȸ���� �������� �ʽ��ϴ�.\n");
		printf("================================\n");
	}
}
void ModifyClient(List *lp)
{
	char data[10];
	int t=0,real;
	Client *curp;
	Client *tp;
	printf("������ ȸ���� �̸��� �Է��ϼ��� : ");
	scanf("%s",data);
	getchar();
	tp=lp->head;
	curp=lp->head->next;
	while(curp!=lp->tail)
	{
		if(strcmp(curp->name,data)==0)
		{
			t=1;
			printf("%s�� ���� �����Ͻðڽ��ϱ�?[Yes(1)/No(0)] ",data);
			scanf("%d",&real);
			while(real!=1 && real!=0)
			{
				while(getchar()!='\n');
				printf("%s�� ���� �����Ͻðڽ��ϱ�?[Yes(1)/No(0)] ",data);
				scanf("%d",&real);
			}
			getchar();
			if(real==1)
			{
				tp->next=curp->next;
				free(curp);
				char c;
				Client *myclient;
				myclient=(Client *)malloc(sizeof(Client));
				printf("�̸� : ");
				scanf("%[^\n]s",myclient->name);
				getchar();
				printf("�ּ� : ");
				scanf("%[^\n]s",myclient->address);
				getchar();
				printf("��ȭ��ȣ : ");
				scanf("%[^\n]s",myclient->phoneNum);
				getchar();
				tp=lp->head;
				while(1)
				{
					if(tp->next==lp->tail)
					{
						myclient->next=lp->tail;
						tp->next=myclient;
						break;
					}
					if(strcmp(tp->next->name,myclient->name)>=0)
					{
						myclient->next=tp->next;
						tp->next=myclient;
						break;
					}
					else
					{
						tp=tp->next;
					}
				}
				return ;
			}
		}
		tp=curp;
		curp=curp->next;
	}
	if(t==0)
	{
		printf("ȸ���� �����ϴ�.\n");
	}
	printf("================================\n");
}
void removeClient(List *lp)
{
	char data[10];
	int t=0,real;
	printf("������ ȸ���� �̸��� �Է��ϼ��� : ");
	scanf("%s",data);
	Client *curp;
	Client *tp;
	tp=lp->head;
	curp=lp->head->next;
	while(curp!=lp->tail)
	{
		if(strcmp(curp->name,data)==0)
		{
			t=1;
			printf("%s�� ���� �����Ͻðڽ��ϱ�?[Yes(1)/No(0)] : ",data);
			scanf("%d",&real);
			while(real!=1 && real!=0)
			{
				while(getchar()!='\n');
				printf("%s�� ���� �����Ͻðڽ��ϱ�?[Yes(1)/No(0)] : ",data);
				scanf("%d",&real);
			}
			if(real==1)
			{
				tp->next=curp->next;
				free(curp);
				printf("������ �����Ǿ����ϴ�.\n");
				return ;
			}
		}
		tp=curp;
		curp=curp->next;
	}
	if(t==0)
	{
		printf("ȸ���� �����ϴ�.\n");
	}
	printf("================================\n");
}
void saveData(List *lp)
{
	FILE *sp=fopen("���÷�_���_����.txt","w+");
	Client *curp;
	curp=lp->head->next;
	while(curp!=lp->tail)
	{
		fprintf(sp,"%s,%s,%s\n",curp->name,curp->address,curp->phoneNum);
		curp=curp->next;
	}
	fclose(sp);
}
void destoryList(List *lp)
{
	free(lp->tail);
	free(lp->head);
}
