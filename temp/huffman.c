// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

int count=1,k=1,x=1;
int max;
int ptr;
int *arr;
int *freq;
int size = sizeof(arr)/sizeof(arr[0]);

//List for mapping words to integer values
struct wordlist
{
	char word[100];
	int n;
	int fr;
	struct wordlist *prev;
	struct wordlist *next;
};

struct wordlist *head=NULL;
struct wordlist *temp=NULL;
struct wordlist *trace=NULL;

//INITIALIZE INTEGER VALUES IN EACH NODE
void init(struct wordlist *node)
{
    node->n=0;
}

//FUNCTION DELETING UNNECESSARY FILES USED IN THE ENCODING PROCESS

void remove_file(char file_name[])
{
    int status;
    status = remove(file_name);
    if( status != 0 )
    {
        printf("Unable to delete the file\n");
        perror("Error");
    }
}

void change()
{
    FILE *f1,*f2,*f3;
    char ch[50],cid[50],word[50],freq[50],len[50];
    f1=fopen("rout.txt","r");
    f2=fopen("wcoutput.txt","r");
    f3=fopen("routput.txt","w");
    fscanf(f1,"%s",ch);
    
    fscanf(f2,"%s%s%s",word,freq,len);
    while(1)
    {
        fscanf(f1,"%s%s",ch,cid);
        if(feof(f1))
            break;
        fscanf(f2,"%s%s%s",word,freq,len);
        fprintf(f3,"%s %s\n",word,cid);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    //remove_file("rout.txt");
}

void printlist(struct wordlist *head)
{
	temp=head;
	while(temp->next!=NULL)
	{
		printf("%s %d %d\n",temp->word,temp->n,temp->fr);
        temp=temp->next;
	}
	printf("%s %d %d\n",temp->word,temp->n,temp->fr);
}

//ASSINGING INTEGER ID FOR EACH WORD FROM THE WORDLIST STRUCTURE TO AN ARRAY FOR HUFFMAN ENCODING
void initialize_array(struct wordlist *head)
{
    int i=0;
	temp=head;
	while(temp->next!=NULL)
	{
	    arr[i]=temp->n;
	    freq[i]=temp->fr;
		temp=temp->next;
		i++;
	}
	arr[i]=temp->n;
    freq[i]=temp->fr;
}

//STRUCTURE TO SORT WORDS IN A SPECIFIC CLUSTER
struct sort_array
{
    char wordd[50];
    int freq;
}a[10000];

//SORT FUNCTION TO SORT THE ARRAY A[]
void sort(FILE *f)
{
    char w[50];
    int ff;
    int i=0,j,count=0;
    fseek(f,0,SEEK_SET);
    while(1)
    {
        fscanf(f,"%s %d",w,&ff);
        if(feof(f))
        break;
        strcpy(a[i].wordd,w);
        a[i].freq=ff;
        count++;
        i++;
    }
    for(i=0;i<count;i++)
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
    FILE *g;
    char er[15];
    sprintf(er,"%d",x);
    char er1[20]="res";
    strcat(er1,er);
    strcat(er1,".txt");
    //printf("%s",er1);
    g=fopen(er1,"w");
    for(i=0;i<(count);i++)
    {
        //printf("\n%s\t%d \n",a[i].wordd,a[i].freq);
        fprintf(g,"%s\t%d\n",a[i].wordd,a[i].freq);
    }
    fclose(g);
    x++;
}

//FUNCTION TO SEPARATE THE WORDS INTO FILES BASED ON THEIR CLUSTER IDS
//i.e. WORDS BELONGING TO CLUSTER 1 GO TO CLUSTER1.TXT AND SO ON
void separate(int c)
{
    char *token;
    char arr[100];
    char word[100],w[100],er[20],er1[20];
    int f,l,i,j=0;
    int c1=0,c2=0,c3=0;//initialise for each cluster

    FILE *fp,*f1,*f2,*f3,*fi,*f4;
    fp=fopen("routput.txt","r");
    fi=fopen("wcoutput.txt","r");
    f1=fopen("clusid.txt","w");
    for(i=1;i<=c;i++)
    {
	c1=0;
	j++;
    	sprintf(er,"%d",i);
       	strcpy(er1,"cluster");
        strcat(er1,er);
        strcat(er1,".txt");
        f2=fopen(er1,"w");
		//printf("%s\n\n",er1);
    	fseek(fp,0,SEEK_SET);
		//fscanf(fp,"%s",arr);
    	while(1)
	    {
        	fscanf(fp,"%s",arr);
	        if(feof(fp))
	        break;
	        //token=strtok(arr," \"\n");
	        //while(token!=NULL)
	        {
                //printf("%s ",token);
                if(atoi(arr)==i)
                {
                    fseek(fi,0,SEEK_SET);
                    while(1)
                    {
                        fscanf(fi,"%s %d %d",w,&f,&l);
                        if(feof(fi))
                        break;
                        if(strcmp(word,w)==0)
                        {
                                c1++;
                                fprintf(f2,"%s %d \n",w,f);
                        }
                    }
                }
                else
                {
                    strcpy(word,arr);
                    //printf(" word:%s \n",token);
                }
            //token=strtok(NULL," \"\n");
		}//end of inner while
	}//end of outer while
	fprintf(f1,"%d\t%d\n",i,c1);//change this also
	fclose(f2);
    }//end of for
    fclose(fp);
    fclose(f1);
    fclose(fi);

    //remove_file("clus1.txt");
    for(i=1;i<=c;i++)
    {
        sprintf(er,"%d",i);
       	strcpy(er1,"cluster");
        strcat(er1,er);
        strcat(er1,".txt");
        f1=fopen(er1,"r");
        sort(f1);
        fclose(f1);
        remove_file(er1);
    }
}



// A Huffman tree node
struct MinHeapNode
{
    int data;  // One of the input characters
    unsigned freq;  // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap
{
    unsigned size;    // Current size of min heap
    unsigned capacity;   // capacity of min heap
    struct MinHeapNode **array;  // Attay of minheap node pointers
};

// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(int data, unsigned freq)
{
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n,FILE *f)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        //printf("%d", arr[i]);
        fprintf(f,"%d",arr[i]);

    }
    //printf(" ");
    fprintf(f," ");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}

// Creates a min heap of capacity equal to size and inserts all character of
// data[] in min heap. Initially size of min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(int data[], int freq[], int size)
{
    int i;
    struct MinHeap* minHeap = createMinHeap(size);
    for (i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(int data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void printCodes(struct MinHeapNode* root, int arr[], int top,FILE *f,int opt)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1,f,opt);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1,f,opt);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if(opt==1)
    {
    if (isLeaf(root))
    {
        temp=head;
        while(temp->next!=NULL)
        {
            //printf("%s\n",temp->word);
            if(root->data==temp->n)
            {
                    //printf("%s: ",temp->word);
                    fprintf(f,"%s ",temp->word);
                    break;
            }
            temp=temp->next;
        }
        if(root->data==temp->n && temp->next==NULL)
        {
             //printf("%s: ",temp->word);
             fprintf(f,"%s ",temp->word);
        }
        printArr(arr, top, f);
    }
    }
    else if(opt==2)
    {
   	if (isLeaf(root))
    	{
        	//printf("%d: ",root->data);
        	fprintf(f,"%d ",root->data);
        	printArr(arr, top, f);
    	}
    }
}

// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(int data[], int freq[], int size,int opt)
{
   //  Construct Huffman Tree
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using the Huffman tree built above
    int top=0;
    FILE *f;
    if(opt==1)
    {
        char er[25];
        sprintf(er,"%d",k);
        char er1[50]="code";
        strcat(er1,er);
        strcat(er1,".txt");
        f=fopen(er1,"w");
    }
    else if(opt==2)
    {
   	f=fopen("ccode.txt","w");
    }
    printCodes(root, arr, top,f,opt);
    fclose(f);
}

//APPLYING HUFFMAN CODING FOR EACH CLUSTER AND OBTAINING HUFFMAN CODES
//FOR EACH WORD. FOR EACH CLUSTER THE OUTPUT IS STORED IN CODE1.TXT, CODE2.TXT.. SO ON
void inner_cluster_huffman(int l)
{
    char word[100];
    int f,c,i=0;
    FILE *f1;
    char er[25],er1[50];

    head=NULL;
    for(i=1;i<=l;i++)
    {
        c=0;
        sprintf(er,"%d",i);
        strcpy(er1,"res");
        strcat(er1,er);
        strcat(er1,".txt");
        f1=fopen(er1,"r");
        //	printf("opened %s \n:", er1);
        while(1)
        {
            fscanf(f1,"%s%d",word,&f);
            if(feof(f1))
            break;
            if(head==NULL)
            {
                struct wordlist *new1;
                new1=(struct wordlist*)malloc(sizeof(struct wordlist));
                init(new1);
                head=new1;
                temp=new1;
                strcpy(temp->word,word);
                temp->n=count;
                temp->fr=f;
                temp->next=NULL;
                temp->prev=NULL;
                c++;
            }
            else
            {
                count++;
                struct wordlist *new1;
                new1=(struct wordlist*)malloc(sizeof(struct wordlist));
                init(new1);
                new1->next=NULL;
                new1->prev=temp;
                temp->next=new1;
                temp=temp->next;
                strcpy(temp->word,word);
                temp->n=count;
                temp->fr=f;
                max=count;
                temp->next=NULL;
                c++;
            }
        }
        arr=(int*)malloc(c*sizeof(int));  //memory allocated using malloc
        freq=(int*)malloc(c*sizeof(int));  //memory allocated using malloc
        size = c;
        if(arr==NULL)
        {
            printf("Error! memory not allocated.");
            exit(0);
        }
        if(freq==NULL)
        {
            printf("Error! memory not allocated.");
            exit(0);
        }
        initialize_array(head);
        HuffmanCodes(arr, freq, size,1);
        head=NULL;temp=NULL;
        k++;
        x++;
        free(arr);
        free(freq);
    }
	for(i=1;i<=l;i++)
	{
		sprintf(er,"%d",i);
        strcpy(er1,"res");
        strcat(er1,er);
        strcat(er1,".txt");
        remove_file(er1);
	}
}

//APPLYING HUFFMAN ENCODING FOR THE CLUSTERS TO OBTAIN THE CLUSTER CODES. THE OUTPUT OF THIS
//FUNCTION IS STORED IN CCODE.TXT
void outer_cluster_huffman(int l)
{
    FILE *f1;
    int f,c,i=0;
    f1=fopen("clusid.txt","r");
    arr=(int*)malloc(l*sizeof(int));  //memory allocated using malloc
    if(arr==NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    freq=(int*)malloc(l*sizeof(int));  //memory allocated using malloc
    if(freq==NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    size = l;
    while(1)
    {
        fscanf(f1,"%d%d",&c,&f);
        if(feof(f1))
        break;
        arr[i]=c;
        freq[i]=f;
        i++;
    }

   //if int is used it ll be applicable for a maximum of 32000 words
    HuffmanCodes(arr, freq, size,2);
    remove_file("clusid.txt");
    free(arr);
    free(freq);
}

//MODULE TO APPEND THE CLUSTER CODE TO THE WORD CODE AND CREATE THE FINAL CODE CODE TABLE
//THE FINAL CODE TABLE CONTAINING THE CODEWORD FOR EACH WORD IS STORED IN APPENDED.TXT
void rearrange(int c)
{
	FILE *fp,*fw,*f1;
	int i=1;
	char er[20],er1[20];
	char cid[20],ccode[150],word[150],wcode[150],temp[150];
	fw=fopen("appended.txt","w");
	for(i=1;i<=c;i++)
	{
		strcpy(er,"code");
		sprintf(er1,"%d",i);
		strcat(er,er1);
		strcat(er,".txt");
		f1=fopen(er,"r");
		fp=fopen("ccode.txt","r");
		while(1)
		{
			fscanf(fp,"%s%s",cid,ccode);
			if((strcmp(er1,cid)==0))
			break;
		}
		strcpy(temp,ccode);
		while(1)
		{
			fscanf(f1,"%s%s",word,wcode);
			if(feof(f1))
			break;
			strcat(temp,wcode);
			fprintf(fw,"%s %s ",word,temp);
			strcpy(temp,ccode);
		}
		fclose(fp);

		fclose(f1);
	}
	fclose(fw);
	for(i=1;i<=c;i++)
	{
		strcpy(er,"code");
		sprintf(er1,"%d",i);
		strcat(er,er1);
		strcat(er,".txt");
		remove_file(er);
	}
	remove_file("ccode.txt");
}

// Driver program to test above functions
int main(int argc,char *argv[])
{
    //USAGE ::  ./a.out no_of_clusters

	clock_t begin,end;
	double time_spent;
    int c=atoi(argv[1]);

	begin=clock();
	printf("\n\nGetting huffman codes.. \n");
    change();
    separate(c);
    //inner_cluster_huffman(c);
    //outer_cluster_huffman(c);
    //rearrange(c);
	end=clock();

	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTime Spent for huffman: %lf\n",time_spent);
    return 1;
}
