#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void shift(char ch[100],int n)
{
	int i;
	for(i=0;i<strlen(ch);i++)
		ch[i]=ch[i+n];
	printf("\nShifted");	
	//printf("\n%s",ch);
}

void decode()
{
	FILE *input,*fc,*f1,*f2,*f3,*fo;

	input = fopen("output.bin","r");
	fc = fopen("ccode.txt","r");
	f1 = fopen("code1.txt","r");
	f2 = fopen("code2.txt","r");
	f3 = fopen("code3.txt","r");
	fo = fopen("decoded_output.txt","w");
	
	char ch[100];
	char cname[100],cid[100],wname[100],wid[100];
	int flag,flag2;

		
	while(fgets(ch,100,input) != NULL)
	{	
		printf("%s",ch);
	}

	
	char str[100] = "\0";
	char str2[100] = "\0";
	int length = strlen(ch);
	int i,j;

	for(i = 1; i<length ; i++)
	{
		l1:
		strcpy(str,"\0");
		strncat(str,ch,i);
		//printf("\nFor cluster id %s \n",str);
		flag=0;
		fseek(fc,0,SEEK_SET);
		fscanf(fc,"%s\t%s",cname,cid);
		
		while(1)
		{
			if(feof(fc))
				break;
			if(strcmp(str,cid)==0)
			{
				flag=1;
				printf("\nEqual\n");
				shift(ch,i);
				for(j=1;j<strlen(ch);j++)
				{
					strcpy(str2,"\0");
					strncat(str2,ch,j);
					//printf("\nFor codeword : %s \n",str2);
					flag2=0;
					if(strcmp(cname,"1")==0)
					{
						//printf("\nOpening file cluster 1");
						fseek(f1,0,SEEK_SET);
						fscanf(f1,"%s\t%s",wname,wid);
						while(1)
						{
							if(feof(f1))
								break;
							if(strcmp(str2,wid)==0)
							{
								flag2=1;
								printf("\nWord equal : %s",wname);
								fprintf(fo,"%s ",wname);
								shift(ch,j);
								goto l1;
							}
							fscanf(f1,"%s\t%s",wname,wid);
						}
						
					}
					if(strcmp(cname,"2")==0)
					{
						
						fseek(f2,0,SEEK_SET);
						fscanf(f2,"%s\t%s",wname,wid);
						while(1)
						{
							if(feof(f2))
								break;
							if(strcmp(str2,wid)==0)
							{
								flag2=1;
								printf("\nWord equal : %s",wname);
								fprintf(fo,"%s ",wname);
								shift(ch,j);
								goto l1;
							}
							fscanf(f2,"%s\t%s",wname,wid);
						}
						strcpy(str2,"\0");					
					}
					if(strcmp(cname,"3")==0)
					{
						fseek(f3,0,SEEK_SET);
						fscanf(f3,"%s\t%s",wname,wid);
						while(1)
						{
							if(feof(f3))
								break;
							if(strcmp(str2,wid)==0)
							{
								flag2=1;
								printf("\nWord equal : %s",wname);
								fprintf(fo,"%s ",wname);
								shift(ch,j);
								goto l1;
							}
							fscanf(f3,"%s\t%s",wname,wid);
						}
						strcpy(str2,"\0");
					}
					
				}			
			}
					
			fscanf(fc,"%s\t%s",cname,cid);
		}
		
	}
	printf("\n");
}

int main()
{
	decode();
} 
		
