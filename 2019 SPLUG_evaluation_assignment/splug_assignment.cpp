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
	char *ptrAryMenu[]={"모든 주소록 정보 출력","회원 등록","회원 정보 검색","회원 정보 수정", "회원 삭제","프로그램 종료"};
	int size_menu;
	size_menu=(sizeof(ptrAryMenu)/sizeof(ptrAryMenu[0]));
	createList(&list);
	callFile(&list);
	while(1)
	{
		Menu(ptrAryMenu,size_menu);
		printf("================================\n");
		printf("선택할 기능을 입력하세요 : ");
		scanf("%d",&menuSelect);
		while(menuSelect<1 || menuSelect>6)
		{
			while(getchar()!='\n');
			printf("선택할 기능을 입력하세요 : ");
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
		printf("#%d\n이름 : %s\n주소 : %s\n전화번호 : %s\n",i,curp->name,curp->address,curp->phoneNum);
		curp=curp->next;
		i++;
		printf("================================\n");
	}
}
void callFile(List *lp)
{
	FILE *sp=fopen("스플럭_명단_관리.txt","r+");
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
	printf("이름 : ");
	scanf("%[^\n]s",myclient->name);
	getchar();
	printf("주소 : ");
	scanf("%[^\n]s",myclient->address);
	getchar();
	printf("전화번호 : ");
	scanf("%[^\n]s",myclient->phoneNum);
	getchar();
	printf("\n추가되었습니다.\n");
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
	printf("찾으시는 회원의 이름을 입력하세요 : ");
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
			printf("이름 : %s\n주소: %s\n전화번호 : %s\n",curp->name,curp->address,curp->phoneNum);
			printf("================================\n");
			t++;
		}
		curp=curp->next;
	}
	if(t==0)
	{

		printf("회원이 존재하지 않습니다.\n");
		printf("================================\n");
	}
}
void ModifyClient(List *lp)
{
	char data[10];
	int t=0,real;
	Client *curp;
	Client *tp;
	printf("수정할 회원의 이름을 입력하세요 : ");
	scanf("%s",data);
	getchar();
	tp=lp->head;
	curp=lp->head->next;
	while(curp!=lp->tail)
	{
		if(strcmp(curp->name,data)==0)
		{
			t=1;
			printf("%s를 정말 수정하시겠습니까?[Yes(1)/No(0)] ",data);
			scanf("%d",&real);
			while(real!=1 && real!=0)
			{
				while(getchar()!='\n');
				printf("%s를 정말 수정하시겠습니까?[Yes(1)/No(0)] ",data);
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
				printf("이름 : ");
				scanf("%[^\n]s",myclient->name);
				getchar();
				printf("주소 : ");
				scanf("%[^\n]s",myclient->address);
				getchar();
				printf("전화번호 : ");
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
		printf("회원이 없습니다.\n");
	}
	printf("================================\n");
}
void removeClient(List *lp)
{
	char data[10];
	int t=0,real;
	printf("수정할 회원의 이름을 입력하세요 : ");
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
			printf("%s를 정말 수정하시겠습니까?[Yes(1)/No(0)] : ",data);
			scanf("%d",&real);
			while(real!=1 && real!=0)
			{
				while(getchar()!='\n');
				printf("%s를 정말 수정하시겠습니까?[Yes(1)/No(0)] : ",data);
				scanf("%d",&real);
			}
			if(real==1)
			{
				tp->next=curp->next;
				free(curp);
				printf("정보가 삭제되었습니다.\n");
				return ;
			}
		}
		tp=curp;
		curp=curp->next;
	}
	if(t==0)
	{
		printf("회원이 없습니다.\n");
	}
	printf("================================\n");
}
void saveData(List *lp)
{
	FILE *sp=fopen("스플럭_명단_관리.txt","w+");
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
