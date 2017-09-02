#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int flag;

//LINKED LIST CONTAINING THE LIST OF WORDS FROM THE CODE TABLE
struct codelist
{
    char word[100];
    char code[100];
    struct codelist *next;
}*head1,*temp1;

void createlist(FILE *f1)
{
    char a[25],b[25];
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

void printlist(struct codelist *h)
{
    
    temp1=h;
    while(temp1!=NULL)
    {
        //printf("%s %s \n",temp1->word,temp1->code);
        temp1=temp1->next;
    }
}

//FUNCTION TO CHECK IF THE CODE WORD IS PRESENT IN THE CODE TABLE
void scanlist(struct codelist *h,char arr[],FILE *f)
{
    
    temp1=h;
    while(temp1 != NULL)
    {
        if(strcmp(arr,temp1->code)==0)
        {
            //printf("%s ",temp1->word);
            fprintf(f,"%s ",temp1->word);
            flag=1;
            break;
        }
        temp1=temp1->next;
    }
}

//FUNCTION TO DELETE THE BITS FROM THE MAIN INPUT STREAM IF THEY HAVE BEEN DECODED
void shift(char ch[100],int n)
{
    int i;
    for(i=0;i<strlen(ch);i++)
        ch[i]=ch[i+n];
}


int main()
{
    FILE *f1,*f2,*fi,*fo;
    int i;
    char inp[100],str[100],miss[100];
    f1=fopen("appended.txt","r");
    fi=fopen("encoded_output.txt","r");
    fo=fopen("decoded_output.txt","w");
    head1=NULL;
    temp1=NULL;
    char er[10],er1[10];
    createlist(f1);
    //printlist(head1);
    
    clock_t begin,end;
    double time_spent;
    begin=clock();
    printf("\n\n Decoding begins.. ");
    while(fgets(inp,50,fi)!=NULL)
    {
        strcat(miss,inp);
        strcpy(inp,miss);
    l1:
        for(i = 1; i<strlen(inp) ; i++)
        {
            strcpy(str,"\0");
            strncat(str,inp,i);
            //printf("str: %s\n",str);
            scanlist(head1,str,fo);
            if(flag==1)
            {
                shift(inp,i);
                flag=0;
                strcpy(miss,inp);
                goto l1;
            }
        }
    }
    if(miss!=NULL)
    {
        scanlist(head1,miss,fo);
    }
    end=clock();
    time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
    printf(" \n\n DECODING TIME SPENT : %lf\n\n",time_spent);
    fclose(f1);
    fclose(fi);
    fclose(fo);
    return 0;
}
