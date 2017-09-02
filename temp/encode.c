#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

//CONTAINS THE LIST OF ALL THE WORDS WITH THEIR CODES
struct codelist
{
  char word[50];
  char code[50];
  struct codelist *next;
}*head1,*temp1;

//CREATING LINKED LIST OF THE UNIQUE WORDS IN THE ORIGINAL DOCUMENT
void createlist(FILE *f1)
{
    char a[50],b[50];
    while(1)
    {
        fscanf(f1,"%s %s",a,b);
        if(feof(f1))
        break;
        if(head1==NULL)
        {
            struct codelist *new1;
            new1=(struct codelist*)malloc(sizeof(struct codelist));
            head1=new1;
            temp1=new1;
            strcpy(temp1->word,a);
            strcpy(temp1->code,b);
            temp1->next=NULL;
        }
        else
        {
            struct codelist *new1;
            new1=(struct codelist*)malloc(sizeof(struct codelist));
            new1->next=NULL;
            temp1->next=new1;
            temp1=temp1->next;
            strcpy(temp1->word,a);
            strcpy(temp1->code,b);
            temp1->next=NULL;
        }
    }
}

//MODULE TO SCAN THE LIST TO FIND OUT THE CODE FOR EACH WORD
void scanlist(struct codelist *h,char arr[],FILE *f)
{

	temp1=h;
	while(temp1->next!=NULL)
	{
		if(strcmp(arr,temp1->word)==0)
		{
			fprintf(f,"%s",temp1->code);
		}
        	temp1=temp1->next;
	}
	if(strcmp(arr,temp1->word)==0)
	fprintf(f,"%s",temp1->code);
}

//MODULE TO FIND OUT THE SIZE OF THE ORIGINAL AND ENCODED FILES
void find_size(char *a)
{
	FILE *f;
	char ch;
	long long int count=0;
	long long int t;
	f=fopen(a,"r");
	while(1)
	{
		ch=fgetc(f);
		if(feof(f))
		break;
		count++;
	}
	fclose(f);
	printf("\nOriginal file size : %lld bytes\n",count);
	count=0;
	f=fopen("encoded_output.txt","r");
	while(1)
	{
		ch=fgetc(f);
		if(feof(f))
		break;
		count++;
	}
	fclose(f);
	t=count/8;
	printf("\nEncoded file size : %lld bytes\n",count/8);
	count=0;
	f=fopen("appended.txt","r");
	while(1)
	{
		ch=fgetc(f);
		if(feof(f))
		break;
		count++;
	}
	fclose(f);
	printf("\nCode Table size : %lld bytes\n",count);
	printf("\nTotal Encoded file size : %lld\n\n",t+count);

}

//DRIVER PROGRAM TO TEST THE ABOVE ROUTINES
int main(int argc,char *argv[])
{
	//USAGE :: ./a.out input_filename
	clock_t begin,end;
	double time_spent;
    FILE *f1,*f2,*fi,*fo;
    int k=1;
	char inp[50];
	f1=fopen("appended.txt","r");
	fi=fopen(argv[1],"r");
	fo=fopen("encoded_output.txt","w");
	head1=NULL;
	temp1=NULL;
	char er[20],er1[20];
	int i;
	createlist(f1);
	printf("\n\n Encoding the input text ..\n");
	//ENCODING THE ORIGINAL INPUT FILE
	begin=clock();
	while(1)
	{
		fscanf(fi,"%s",inp);
		if(feof(fi))
		break;
		scanlist(head1,inp,fo);
	}
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\nENCODING TIME : %lf \n\n",time_spent);
	fclose(f1);
	fclose(fi);
	fclose(fo);
	find_size(argv[1]);
	return 0;
}
