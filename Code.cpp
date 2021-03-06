/*Design a system for find and replace available with word processors by reading contents from file*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

struct node
{
	char WORD[30];
	node *left;
	node *right;
	node *next_node;
}*root,*head;

void add(char *arr,int length) //create bst
{
	
	if(root==NULL)
	{
		int i;
		root=(struct node*)malloc(sizeof(struct node));
		for( i=0;i<length;i++)
		{
			root->WORD[i]=*(arr+i);
		}
		root->WORD[i]='\0';
		root->left=NULL;
		root->right=NULL;

	}
	else
	{
		int i;
		struct node *temp,*temp1;
		temp=root;
		temp1=(struct node*)malloc(sizeof(struct node));

		for(i=0;i<length;i++)
		{
				temp1->WORD[i]=*(arr+i);
		}
		temp1->WORD[i]='\0';
		temp1->left=NULL;
		temp1->right=NULL;
		while(temp!=NULL)
		{
		
			if(strcmp(temp1->WORD,temp->WORD)<=0 && temp->left!=NULL)
			{
				temp=temp->left;
			}
			else if(strcmp(temp1->WORD,temp->WORD)<=0 && temp->left==NULL)
			{
				temp->left=temp1;
				break;
			}
			else if(strcmp(temp1->WORD,temp->WORD)>0 && temp->right!=NULL)
			{
				temp=temp->right;
			}
			else
			{
				temp->right=temp1;
				break;
			}
		}
	}
}

int find(struct node *t,char *word,int length,int count) //find word in BST
{
	char temp[20];
	int i;
	for(i=0;i<=length;i++)
	{
		temp[i]=*(word+i);
	}
	
	if(t==NULL)
	{
		return count;
	}
		count=find(t->left,temp,length,count);
		if(strcmp(t->WORD,temp)==0)
		{
			count++;
		}
		count=find(t->right,temp,length,count);
}

void add_headnode(char *word,int length) //add head node in linked list
{
	head=(struct node*)malloc(sizeof(struct node));
	int i;
	for(i=0;i<length;i++)
	{
		head->WORD[i]=*(word+i);
	}
	head->WORD[i]='\0';
	head->next_node=NULL;
}

void add_node(char *word,int length) //add node in linked list
{
	int i;
	node *temp,*newnode;
	newnode=(struct node*)malloc(sizeof(struct node));
	temp=head;
	for (i=0;i<length;i++)
	{
		newnode->WORD[i]=*(word+i);
	}
	newnode->WORD[i]='\0';
	newnode->next_node=NULL;
	while(temp->next_node!=NULL)
	{
		temp=temp->next_node;
	}
	temp->next_node=newnode;
}

void display() //display text
{
	node *temp;
	temp=head;
	while(temp!=NULL)
	{
		printf("%s",temp->WORD);
		temp=temp->next_node;
	}
}

void replace(char *new_word,  char *old_word,int length_new,int length_old) //replace word in linked list
{
	char temp_new[20];
	char temp_old[20];
	node *temp;
	int i;
	FILE *file_read=fopen("text.txt","w");
	for(i=0;i<length_new;i++)
	{
		temp_new[i]=*(new_word+i);
	}
	temp_new[i]='\0';
	for(i=0;i<length_old;i++)
	{
		temp_old[i]=*(old_word+i);
	}
	temp_old[i]='\0';
	temp=head;
	while(temp!=NULL)
	{
		if(strcmp(temp->WORD,temp_old)==0)
		{
			strcpy(temp->WORD,temp_new);
		}
		for(int i=0;i<strlen(temp->WORD);i++)
		{
			fputc(temp->WORD[i],file_read);
		}
		temp=temp->next_node;
	}
	fclose(file_read); //update in original file
}

void inorder(struct node *t,char *new_word,  char *old_word,int length_new,int length_old) //update BST
{
	
	char temp_new[20];
	char temp_old[20];
	node *temp;
	int i;
	for(i=0;i<length_new;i++)
	{
		temp_new[i]=*(new_word+i);
	}
	temp_new[i]='\0';
	for(i=0;i<length_old;i++)
	{
		temp_old[i]=*(old_word+i);
	}
	temp_old[i]='\0';
	if(t==NULL)
	{
		return;
	}
		inorder(t->left,temp_new,temp_old,strlen(temp_new),strlen(temp_old));
		if(strcmp(t->WORD,temp_old)==0)
		{
			strcpy(t->WORD,temp_new);
		}
		inorder(t->right,temp_new,temp_old,strlen(temp_new),strlen(temp_old));
}

int main()
{
	char c;
	char word[20];
	char str[20];
	int count=0;
	int length=0;
	int total;
	int headexist=0;
	char old_word[20];
	char new_word[20];
	int length_new=0;
	int length_old=0;
	int j;
	int option=1;
	//struct node *x;
	FILE *file_read=fopen("text.txt","r");
	c=fgetc(file_read);
	if(file_read==NULL)
	{
		printf("Can't read file'\n");
	}
	//adding word in BST and linked list 
	while(c!=EOF)
	{
		int flag=0;
		while(isalpha(c)!=0)
		{
			word[count]=c;
			count++;
			c=fgetc(file_read);
			flag++;
		}
		if(flag!=0)
		{
			
			
			add(word,count);
			if(headexist==0)
			{
				add_headnode(word,count);
				headexist++;	
			}
			else
			{
				add_node(word,count);
			}
			
		}
		count=0;	
		word[count]=c;
		count++; 
		add(word,count);
		if(headexist==0)
		{
			add_headnode(word,count);
			headexist++;
		}
		else
			add_node(word,count);
		count=0;
		c=fgetc(file_read);
	}
	fclose(file_read);
	while(option!=0)
	{
		
		printf("\nPress:\n0 for EOP\n1 for display\n2 for find\n3 for replace\n");
		scanf("%d",&option);
		if (option==1)
		{
			display(); //display text
		}
		else if(option==2)
		{
			printf("Enter word:");
			scanf("%s",str);
			for(j=0;str[j]!='\0';j++)
			{
				length++;
			}
			total=find(root,str,length,0); //find word
			printf("Total %d %c%s%c were found\n",total,'"',str,'"');
		}
		else if(option==3)
		{
			printf("Enter word that has to be replaced:");
			scanf("%s",old_word);
			for(int k=0;old_word[k]!='\0';k++)
			{
				length_old++;
			}
			printf("Enter new word:");
			scanf("%s",new_word);
			for(int k=0;new_word[k]!='\0';k++)
			{
				length_new++;
			}
			replace(new_word,old_word,length_new,length_old); //replace the word in linked list
			inorder(root,new_word,old_word,length_new,length_old); //update BST
		}
		else if(option==0)
		{
			printf("\nEND OF PROGRAM\n");
		}
		else
		{
			printf("\nInvalid option\n");
		}
	}
}
