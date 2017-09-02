#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count=0;
struct wordlist
{
	char word[25];
	int wlen;
	int wcount;
	struct wordlist *prev;
	struct wordlist *next;
};

void init(struct wordlist *node)
{
    node->wlen=0;
    node->wcount=0;
}

struct wordlist *head=NULL;
struct wordlist *temp=NULL;
struct wordlist *trace=NULL;
void printlist(struct wordlist *head)
{
    FILE *f2;
    f2=fopen("wcoutput.txt","w");
    		fprintf(f2,"words frequency length\n");

	printf("LIST OF WORDS : \n\n");
	temp=head;
	while(temp->next!=NULL)
	{
		printf("%s %d %d\n",temp->word,temp->wcount,temp->wlen);
		fprintf(f2,"%s %d %d\n",temp->word,temp->wcount,temp->wlen);

		temp=temp->next;
	}
	printf("%s %d %d\n",temp->word,temp->wcount,temp->wlen);
   		fprintf(f2,"%s %d %d\n",temp->word,temp->wcount,temp->wlen);

    fclose(f2);
}

int main()
{
	int a,b,c=0,d,len;
	char arr[115];
	char *token;
	FILE *f1;
	f1=fopen("testdoc.txt","r");
	while(1)
	{
		fscanf(f1,"%s",arr);
		if(feof(f1))
		break;
		//token=strtok(arr," ");
		//while)
		{
			if(c==0)
			{
			struct wordlist *new1;
			new1=(struct wordlist*)malloc(sizeof(struct wordlist));
			init(new1);
			head=new1;
			temp=new1;
			strcpy(temp->word,arr);
			temp->wcount++;
			//count++;
			temp->wlen=strlen(arr);
			temp->next=NULL;
			temp->prev=NULL;
			c++;
			}
			else
			{
				struct wordlist *new1;
				new1=(struct wordlist*)malloc(sizeof(struct wordlist));
				init(new1);
				new1->next=NULL;
				new1->prev=temp;
				temp->next=new1;
				temp=temp->next;
				strcpy(temp->word,arr);
				temp->wcount++;
				//count++;
				temp->wlen=strlen(arr);
				temp->next=NULL;
				trace=head;
				while(trace->next!=NULL)
				{
					if(strcmp(trace->word,temp->word)==0)
					{
						trace->wcount++;
						//count--;
						temp=temp->prev;
						temp->next=NULL;
					}
   					trace=trace->next;
				}
			}
			//token=strtok(NULL," ");
			}
	}
	printlist(head);
	return 0;
}

