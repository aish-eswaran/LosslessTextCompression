#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int count=0;
int univ_count=0;
int total=0;
//STRUCTURE TO STORE THE LIST OF UNIQUE WORDS
struct wordlist
{
	char word[100];     //WORD
	int wlen;           //LENGTH
	int wcount;         //FREQUENCY
	struct wordlist *prev;
	struct wordlist *next;
};
struct wordlist *head=NULL;
struct wordlist *temp=NULL;
struct wordlist *trace=NULL;

//INITIALIZE INTERGER VALUES IN STRUCTURE FOR EACH NODE
void init(struct wordlist *node)
{
    node->wlen=0;
    node->wcount=0;
}

//MODULE TO INCREMENT THE COUNT OF ANY WORD IF ALREADY APPENDED IN THE LINKED LIST
int check(char ar[])
{
	trace=head;
	while(trace!=NULL)
	{
		if(strcmp(trace->word,ar)==0)
		{
			//printf("returned %s \n",ar);
            total++;
			trace->wcount++;
			return 0;
		}
 		trace=trace->next;
	}
    //univ_count++;
    total++;
	return 1;
}

//REDIRECTING OUTPUT TO WCOUTPUT.TXT
void printlist(struct wordlist *head)
{
     	FILE *f2,*f3;
    	f2=fopen("wcoutput.txt","w");
        f3=fopen("wcc.txt","w");
    	fprintf(f2,"words frequency length\n");
        fprintf(f3,"words frequency length\n");
        temp=head;
        univ_count=0;
        while(temp->next!=NULL)
        {
            //printf("%s: %d %d\n",temp->word,temp->wcount,temp->wlen);
            univ_count++;
            fprintf(f2,"%s %d %d\n",temp->word,temp->wcount,temp->wlen);
            fprintf(f3,"%d %d %d\n",univ_count,temp->wcount,temp->wlen);
            temp=temp->next;
        }
        //printf("%s: %d %d\n",temp->word,temp->wcount,temp->wlen);
        univ_count++;
        fprintf(f2,"%s %d %d\n",temp->word,temp->wcount,temp->wlen);
        fprintf(f3,"%d %d %d\n",univ_count,temp->wcount,temp->wlen);
    	fclose(f2);
        fclose(f3);
}

int main(int argc,char *argv[])
{
	FILE *f;
    float percent;
	char ch[100];
	clock_t begin,end;
	double time_spent;
	f=fopen(argv[1],"r");
	begin=clock();          //CALCULATE TIME TAKEN FOR THIS ROUTINE
    univ_count=0;
    total=0;
	//CREATING THE LINKED LIST CONTAINING THE COLLECTION OF WORDS IN THE DOCUMENT
	while(1)
	{
		fscanf(f,"%s",ch);
		if(feof(f))
		break;
		//printf("%s ",ch);
		if(head==NULL)
		{
			struct wordlist *new1;
			new1=(struct wordlist*)malloc(sizeof(struct wordlist));
			init(new1);
			head=new1;
			temp=new1;
			strcpy(temp->word,ch);
			temp->wcount++;
			temp->wlen=strlen(ch);
			temp->next=NULL;
			temp->prev=NULL;
			count++;
            total++;
		}
		else if(check(ch) == 1)
		{
			struct wordlist *new1;
			new1=(struct wordlist*)malloc(sizeof(struct wordlist));
			init(new1);
			new1->next=NULL;
			new1->prev=temp;
			temp->next=new1;
			temp=temp->next;
			strcpy(temp->word,ch);
			temp->wcount++;
			temp->wlen=strlen(ch);
			temp->next=NULL;
			count++;
		}
	}
	end=clock();
	printlist(head);
	printf("\nunique words count : %d ",count);
    printf("\nTotal number of words: %d ",total);
    percent=((float)count/(float)total)*100;
    printf("\nPercentage of unique words: %f ",percent);
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\nWORD COUNT TIME : %lf \n",time_spent);
	return 0;
}
