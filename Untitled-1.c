#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct  user
{
	string[30] name;
	string[10] pass;
	int status;
	int login=0;
	
}user;


typedef struct node
{
	user data;
	Node *next;
}Node;


typedef struct list 
{
	Node* head;
	Node* tail;
}List;

void CreateList(List *l)
{
	l->head=l->tail=NULL;
}

user input()
{	user x;
	printf("Name : ");
	gets(x.name);
	printf("Password : ");
	gets(x.pw);
	
	return x;
}

Node *CreateNode(user x)
{
	Node *p = new Node;
	p = (Node *) malloc (sizeof (Node));
	strcpy(p->data.name,x.name);
	strcpy(p->data.pass,x.pass);
	p->data.status=x.status;
	p->data.login=x.login;
	p->next = NULL;
	return p;
}

void AddTail(Node *p,List *l)
{
	if(l->head == NULL)
	{
		l->head = p;
	}
	else
	{
		l->tail->next = p;
		l->tail = p;
	}

}

int CheckAcc(char name[30], List *l)
{
	int i;
	if(l->head == NULL)
		i=0;
	else
	{
		for(p=l->head;p->next!=NULL;p=p->next)
		{
			if(strcmp(p->data.name,name) == 0)
			{
				i=1;
				break;
			}
		}
	}
	return i;
}

Node *Search(char name[30], List *l)
{
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	if(l->head==NULL) return NULL;
	else
		for(cur=l->head;cur->next!=NULL;cur=cur->next)
		{
			if(strcmp(cur->data.name,name) == 0)
			{
				return cur;
			
			}
		}
}

void PrintNode(Node *p)
{
	printf("Name : %s\n",p->data.name );
	if(p->status==1)	
		printf("Status : Active\n");
	else
		printf("Status : Blocked\n" );
}

void SignIn(List *l)
{
	int i=3;
	printf("-------Sign In--------\n");
	char name[30], pass[30]; 
	printf("User name : \n");
	scanf("%s",&name);
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur = Search(name,l);
	if(cur==NULL) 
		printf("Account is not exist\n");
	else if(cur->data.status==0)
		printf("Your account has been blocked\n");
	else if(cur!=NULL&&cur->data.status==1)
		{
			printf("Password : \n");
			scanf("%s",&pass);
			while(strcmp(cur->data.pass,pass)!=0&&i>0)
			{
				printf("Wrong password. Enter again : \n");
				scanf("%s",&pass);
				i--;
			}
			if(i==0)
			{
				printf("Your account has been blocked\n");
				cur->data.status=0;
			}
			if(i>0)
			{
				printf("Hello %s\n",cur->data.name);
				cur->data.login=1;
			}
		}

}

void SignOut(List *l)
{
	char name[30];
	printf("-------Sign Out--------\n");
	printf("User name : \n");
	scanf("%s",&name);
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur = Search(name,l);
	if(cur==NULL) 
		printf("Cannot find account\n");
	else if(cur!=NULL&&cur->data.login==0)
		printf("Account is noi sign in\n");
	else
	{
		cur->data.login=0;
		printf("Good bye %s\n",cur->data.name );
	}


}

void Register(List *l)
{
	user x;
	
	printf("-------Register--------\n");
	printf("User name : \n");
	scanf("%s",x.name);
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur = Search(x.name,l);
	while(cur!=NULL)
	{
		printf("Account is existed\n");
		printf("Enter again : \nUser name : ");
		scanf("%s",&x.name);
		cur = Search(x.name,l);
	}
	printf("Password : \n");
	scanf("%s",&x.pass);
	x.status=1;
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur=CreateNode(x);
	AddTail(cur,l);
	printf("Successful registration\n");


}

void LoadFile(List *l) 
	{
	FILE *file = fopen("account.txt", "r");
	if (ferror(file))
		return;

	while (!feof(file)) {
		Node *p = new Node;

		fscanf(file, "%s", p->data.name);
		fscanf(file, "%s", p->data.pass);
		fscanf(file, "%d", p->data.status);
		p->data.login=0;

		AddTail(p, l);
	}

	fclose(file);
}

void SaveFile(List *l)
{
	FILE *file = fopen("account.txt", "w");
	if (ferror(file))
		return;
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	for(cur=l->head;cur->next!=NULL;cur=cur->next)
	{
		fprintf(file, "%s\t",cur->data.name );
		fprintf(file, "%s\t",cur->data.pass );
		fprintf(file, "%s\t",cur->data.status );
	}
	fclose(file);

}


void Menu()
{
	int choice;
	printf("USER MANAGEMENT PROGRAM\n");
	printf("---------------------------------------------\n");
	printf("1. Register\n");
	printf("2. Sign in\n");
	printf("3. Search\n");
	printf("4. Sign out\n");
	printf("Your choice (1-4, other to quit) : \n");	

}


int main()
{
	List *l;
	CreateList(l);
	LoadFile(l);
	int i;
	do
	{
		Menu();
		scanf("%d",&i);
	
		switch(i)
		{
			case 1 :
			Register(l);
			break;
			case 2 :
			SignIn(l);
			break;
			case 3:
			break;
			default :
			printf("Enter again : \n");
		}
	}
	return 0;
}

