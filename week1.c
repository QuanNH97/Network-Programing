#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  Node
{
	char name[30];		//define Node data
	char pass[30];
	int status, login;	//login  is a variable that determines whether you are logged in or not
	struct Node *next;
} Node;

typedef struct  List
{
	Node* head;		//define List
	Node* tail;
}List;

void CreateList(List *l)			//create a list
{
	l->head=l->tail=NULL;		
}

void AddNode(Node *p, List *l)		// add a node to head of list
{	
	if(l->head == NULL)		
	{
		l->head=l->tail=p;
	}
	else
	{
		p->next = l->head; 
      		l->head = p;
		
	}

}
void LoadFile(List *l) 					//load data from account
	{
	FILE *file = fopen("account.txt", "r");
	if (ferror(file))
		return;

	while (1) {
		Node *p ;
		p = (Node *) malloc (sizeof (Node));

		fscanf(file, "%s", p->name);
		if(feof(file)) break;			//removed end of string
		fscanf(file, "%s", p->pass);
		fscanf(file, "%d", &p->status);
		p->login=0;

		AddNode(p,l);
	}
		
	fclose(file);

}


Node *CreateNode()		//input data to a node
{
	Node *p;
	p = (Node *) malloc (sizeof (Node));
	char name[30],pass[30];
	printf("Name : ");
	scanf("%s",name);
	printf("Pass : ");
	scanf("%s",pass);
	strcpy(p->name,name);
	strcpy(p->pass,pass);
	p->status=1;
	p->login=0;		//At the start login=1 -> account not sign in
	p->next=NULL;
	return p;
}

void PrintNode(Node *p)		// print data of node in screen
{
	printf("\nName : %s\n",p->name );
	if(p->status==1)	
		printf("Status : Active\n\n");
	else
		printf("Status : Blocked\n\n" );
}

void PrintAll(List *l)			// print all data
{
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur=l->head;
	while(cur)
	{
		PrintNode(cur);
		cur=cur->next;
	}
}

Node *Search(List *l)		// search by user name, return NULL when can not find data
{
	char name[30];
	printf("User name : ");
	scanf("%s",name);
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	if(l->head==NULL) return NULL;
	cur = l->head;
   	while (cur !=NULL)
   		{
   			if(!strcmp(cur->name,name)) return cur;
      			cur = cur->next;
      		}
   	return NULL;
}

void SignIn(List *l)		// sign in mode
{
	int i=2;
	printf("-------Sign In--------\n");
	char pass[30]; 
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur = Search(l);
	if(cur==NULL) 
		printf("Account is not exist\n");			// can not find data
	else if(cur->status==0)
		printf("Your account has been blocked\n");	// the account is blocked
	else if(cur!=NULL&&cur->status==1)
		{
			printf("Password : ");
			scanf("%s",pass);
			while(strcmp(cur->pass,pass)!=0&&i>0)		// 3 time passwork check
			{
				printf("Wrong password. Enter again : ");
				scanf("%s",pass);
				i--;
			}
			if(i==0)	
			{
				printf("Your account has been blocked\n");	// over 3 time -> block acc
				cur->status=0;
			}
			if(i>0)
			{
				printf("Hello %s\n",cur->name);			// if sign in sucessfull reset i
				cur->login=1;
			}
		}

}

void SignOut(List *l)		//sign out mode
{
	char name[30];
	printf("-------Sign Out--------\n");
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	cur = Search(l);
	if(cur==NULL) 
		printf("Cannot find account\n");
	else if(cur!=NULL&&cur->login==0)
		printf("Account is not sign in\n");
	else
	{
		cur->login=0;
		printf("Good bye %s\n",cur->name );
	}


}

int CheckAcc(char name[30],List *l)		//check account, return 0 or 1
{
	Node *cur;				
	cur = (Node *) malloc (sizeof (Node));
	if(l->head==NULL) return 0;
	cur = l->head;
   	while (cur !=NULL)
   		{
   			if(!strcmp(cur->name,name)) return 1;		//must be used in Register
      			cur = cur->next;
      		}
   	return 0;
}


void Register(List *l)
{
	
	printf("-------Register--------\n");
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	char name[30]; int i;
	printf("User name : ");
	scanf("%s",name);
	i=CheckAcc(name,l);
	if(i==1)
	{
		printf("Account  existed.\n");  //account existed, return menu
		return;
	}
	Node *p;
	p = (Node *) malloc (sizeof (Node));
	strcpy(p->name,name);
	printf("Password : ");
	scanf("%s",p->pass);
	p->status=1;
	p->login=0;
	p->next=NULL;
	printf("Register  sucessfully\n");
	AddNode(p,l);

}

void SaveFile(List *l)		//save list to account.txt
{
	FILE *file = fopen("account.txt", "w");
	if (ferror(file))
		return;
	Node *cur;
	cur = (Node *) malloc (sizeof (Node));
	for(cur=l->head;cur;cur=cur->next)
	{
		fprintf(file, "%s\t",cur->name );
		fprintf(file, "%s\t",cur->pass );
		fprintf(file, "%d\n",cur->status );
	}
	fclose(file);

}

int Menu()		//display menu
{
	int choice;
	printf("\n\nUSER MANAGEMENT PROGRAM\n");
	printf("---------------------------------------------\n");
	printf("1. Register\n");
	printf("2. Sign in\n");
	printf("3. Search\n");
	printf("4. Sign out\n");
	printf("Your choice (1-4, other to quit) : ");
	scanf("%d",&choice);
	return choice;
	
}

int main()
{	
	List *l;	
	CreateList(l); 
	Node *x;
	x = (Node *) malloc (sizeof (Node));
	LoadFile(l);
	int i;
	do
	{
		i=Menu();
		switch(i)
		{
			case 1:
			Register(l);
			break;
			case 2:
			SignIn(l);
			break;
			case 3:
			x=Search(l);
			if(x) PrintNode(x);
			else printf("Cannot find account\n");
			break;
			case 4:
			SignOut(l);
			break;
		}
	}while(i>0&&i<5);
	SaveFile(l);
	return 0;
}