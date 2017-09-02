#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void separate()
{
    FILE *fp,*f1,*f2,*f3,*fi;
    fp=fopen("clus1.txt","r");
    f1=fopen("cluster1.txt","w");
    f2=fopen("cluster2.txt","w");
    f3=fopen("cluster3.txt","w");
    fi=fopen("wcoutput.txt","r");

    char *token;
    char arr[50];
    char word[25],w[25];
    int f,l;
    while(1)
    {
        fscanf(fp,"%s",arr);
        if(feof(fp))
            break;
        token=strtok(arr," \"\n");

        while(token!=NULL)
        {
                if(atoi(token)==1)
                {
                    fseek(fi,0,SEEK_SET);
                    printf("%d\n",1);
                    while(1)
                    {
                        if(feof(fi))
                            break;
                        fscanf(fi,"%s %d %d",&w,&f,&l);
                        if(strcmp(word,w)==0)
                            fprintf(f1,"%s %d \n",w,f);
                    }
                }
                else if(atoi(token)==2)
                {
                     fseek(fi,0,SEEK_SET);
                    printf("%d\n",2);
                    while(1)
                    {
                        if(feof(fi))
                            break;
                        fscanf(fi,"%s %d %d",&w,&f,&l);
                        if(strcmp(word,w)==0)
                        {
                        fprintf(f2,"%s %d \n",w,f);
                        }
                    }
                }
                else if(atoi(token)==3)
                {
                    fseek(fi,0,SEEK_SET);
                    printf("%d\n",3);
                    while(1)
                    {
                        if(feof(fi))
                            break;
                        fscanf(fi,"%s %d %d",&w,&f,&l);
                        if(strcmp(word,w)==0)
                        {
                        fprintf(f3,"%s %d \n",w,f);
                        }
                        if(feof(fi))
                            break;
                    }
                }
                else
                {
                    strcpy(word,token);
                    printf("\n%s\t",token);
                }
            token=strtok(NULL," \"\n");
        }
    }

    fclose(fp);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(fi);

    FILE *fp1,*fp2,*fp3;
    fp1=fopen("cluster2.txt","r+");
    sort(fp1);
    fclose(fp1);
    fp2=fopen("cluster3.txt","r+");
    sort(fp2);
    fclose(fp2);
    fp3=fopen("cluster1.txt","r+");
    sort(fp3);
    fclose(fp3);

}

struct sort_array
{
    char wordd[20];
    int freq;
}a[100];

void sort(FILE *f)
{
    printf("\n--Sorting--\n");
    int i,j,count=0;
    fseek(f,0,SEEK_SET);
    while(!feof(f))
    {
        for(i=0;!feof(f);i++)
        {
            count++;
            fscanf(f,"%s %d",&a[i].wordd,&a[i].freq);
        }
    }
    for(i=1;i<count;i++)
    {
        for(j=1;j<count;j++)
        {
            if(a[j].freq>a[j-1].freq)
            {
                struct sort_array t;
                strcpy(t.wordd,a[j-1].wordd);
                strcpy(a[j-1].wordd,a[j].wordd);
                strcpy(a[j].wordd,t.wordd);
                t.freq=a[j-1].freq;
                a[j-1].freq=a[j].freq;
                a[j].freq=t.freq;
            }
            else if(a[j].freq==a[j-1].freq)
            {
                if(strcmp(a[j-1].wordd,a[j].wordd)>0)
                {
                    struct sort_array t;
                    strcpy(t.wordd,a[j-1].wordd);
                    strcpy(a[j-1].wordd,a[j].wordd);
                    strcpy(a[j].wordd,t.wordd);
                    t.freq=a[j-1].freq;
                    a[j-1].freq=a[j].freq;
                    a[j].freq=t.freq;
                }
            }
        }
    }
    fseek(f,0,SEEK_SET);
    for(i=0;i<(count);i++)
    {
        printf("\nWord : %s Freq : %d ",a[i].wordd,a[i].freq);
        fprintf(f,"%s\t%d\n",a[i].wordd,a[i].freq);
    }
    printf("\nSorting done.\n");
}
int main()
{
    separate();
}
