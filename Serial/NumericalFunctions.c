#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 100000

double findMaximum(char []); 
int linearSearch(char []);
int getLength(char []);
int bubbleSort(char [],int, FILE *);
void merge(double [],int,int,int);
int mergeSort(char [],int,FILE *);

void matrixMult(char [],int,FILE *);
void dfs(char [],int,FILE *);

////////////////////////////////////////////////////
FILE *fup;

typedef struct node
{
 struct node*left;
 struct node*right;
 double data;
}node;

node* insert(double c[],int n)
{ 
  node*tree=NULL;
 
  if(c[n]!='\0')
   {
  	 tree=(node*)malloc(sizeof(node));
  	 tree->left=insert(c,2*n+1);
  	 tree->data=c[n];
  	 tree->right=insert(c,2*n+2);
 }
 return tree;
}

//Traverse the tree in inorder
void inorder(node *tree)
{
  double treeData;
 if(tree!=NULL)
 {
  inorder(tree->left);
   fprintf(fup,"%.2f ",tree->data);
   //treeData = tree->data;
  inorder(tree->right);
 }
}


void dfs(char line[MAXCHAR],int cid,FILE *fp){      // DFS traversal using Inorder technique

  node *tree=NULL;
  fup = fp;

  int i,j=0,length;
  double array[MAXCHAR];
  
 // Get the length of the line
   length = getLength(line);

  char *rest = strchr(line, ' ');
  char *res;
     
   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &array[j]);	
        }
     fprintf(fup,"\n%d dfs ",cid);
    
    tree=insert(array,0);
    inorder(tree);
}

////////////////////////////////////////////////////

double findMaximum(char line[MAXCHAR]){

int i,length,j=0;
// Get the length of the line
   length = getLength(line);

  char *rest = strchr(line, ' ');
  char *res;
  double array[MAXCHAR];
  double max;

	// printf("\n Length %d",length);      
   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &array[j]);
	//printf("%lf ",array[j]);	
        }

    max = array[0];
    for (i=1;i<length;++i) {
        if (max < array[i])
            max = array[i];
    }
    return max;
}

//////////////////////////////////////////
int getLength(char line[MAXCHAR]){

int count=-1;    
char *cur= line;

    for (;;){
        while (*cur == ' ')
        {
            cur++;
        }

        if (*cur == 0)
        {
            break;
        }

        count++;

        while (*cur != 0 && *cur != ' ')
        {
            cur++;
        }
    }
 return count; 
}

//////////////////////////////////////////
int linearSearch(char line[MAXCHAR]){

   int i,length,j=0, c, n;
   char *rest = strchr(line, ' ');
   char *res;
   double array[MAXCHAR],search;

// Get the length of the line
   length = getLength(line);

	// printf("\n Length %d",length);      
   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &array[j]);
	//printf("%lf ",array[j]);	
        }
 
   search = array[0];
 
   for (c = 1; c < length; c++)
   {
      if (array[c] == search)     /* if required element found */
      {
        // printf("\n %lf is present at location %d.\n", search, c);
         break;
      }
   }
   if (c == length){
      //printf("\n %lf is not present in array.\n", search);
	return -1;
   }
   return c;
}
//////////////////Bubble Sort//////////////////////////////// 
void swap(double *xp, double *yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void bubleSort(double arr[], int n)
{
   int i, j;
   int swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = 0;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swapped = 1;
        }
     }
     if (swapped == 0)
        break;
   }
}
 
/* Function to print an array */
void printArray(double arr[], int size,FILE *fp)
{
    int i;
    for (i=0; i < size; i++)
        fprintf(fp,"%.2f ", arr[i]);
    //printf("\n");
}
 
int bubbleSort(char line[MAXCHAR],int cid,FILE *fp)
{

   int length,j;
   char *rest = strchr(line, ' ');
   char *res;
   double arr[MAXCHAR];

// Get the length of the line
   length = getLength(line);

	// printf("\n Length %d",length);      
   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &arr[j]);
	//printf("%lf ",arr[j]);	
        }

      bubleSort(arr,length);
      fprintf(fp,"\n%d bubbleSort ",cid);
      printArray(arr,length,fp);

    return 0;
}

/////////////////////MergeSort////////////////////////////////////// 


int min(double x, int y) 
{ return (x<y)? x :y; } 

void megeSort(double arr[], int n)
{
   int curr_size;  
   int left_start; 
 
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           int mid = left_start + curr_size - 1;
           int right_end = min(left_start + 2*curr_size - 1, n-1);
           merge(arr, left_start, mid, right_end);
       }
   }
}
 
void merge(double arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    double L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort Algorithm
int mergeSort(char line[MAXCHAR],int cid,FILE *fp)
{
   int length,j;
   char *rest = strchr(line, ' ');
   char *res;
   double arr[MAXCHAR];

// Get the length of the line
   length = getLength(line);

	// printf("\n Length %d",length);      
   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &arr[j]);
	//printf("%lf ",arr[j]);	
        }  
  
    megeSort(arr, length); 
    fprintf(fp,"\n%d mergeSort ",cid);
    printArray(arr,length,fp);

    return 0;
}

////////////////////////Matrix Multiplication/////////////
void matrixMult(char line[MAXCHAR],int cid,FILE *fp)
{
   int SIZE,i,j,k,a,b,c,d,length;
   char *rest = strchr(line, ' ');
   char *res;
   double arr[MAXCHAR];
   double temp[MAXCHAR];
   char *len,ch;
   char lineMax[MAXCHAR];

// storing the numbers of the line
size_t destination_size = sizeof (lineMax);
strncpy(lineMax, line, destination_size);
lineMax[destination_size - 1] = '\0';

        strtok (lineMax," ");
	len = strtok (NULL," ");        
	SIZE = atoi(len);

double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
// Get the SIZE of the line
   length = getLength(line);
	//printf("\n Length %d\n",SIZE); 
//printf("\n File size %d\n",length);      

   for(j=0;j<length;j++){
	for (res = rest ; *res && *res != ' ' ; res++);
	if (*res) res++;
	rest = res;	
	sscanf(rest, "%lf", &arr[j]);
	//printf("%.2f ",arr[j]);	
        } 

//////////////////////////////////
//printf("\nResultant 1D array is\n");
double arr1D[SIZE*SIZE];
for(j=0;j<length-1;j++){
	arr1D[j] = arr[j+1];
	//printf("%.2f ", arr1D[j]);
	//arr1D[j] = arr[j];
}


//printf("\nResultant Init A1D Array ");
for (i=0;i<length-1;i++) arr1D[i]=i+1; 
//Convert to A2D 
for (i=0;i<SIZE;i++) 
for (j=0;j<SIZE;j++) 
if (j+1<=arr1D[i]) A[i][j]=arr1D[i]; 
else A[i][j]=0;  

int cnt=0;

//printf("\nResultant 2D A array is\n");
 for (i = 0; i < SIZE; i++)
    {	
        for (j = 0; j < SIZE; j++)
        {   
		A[i][j] = arr1D[cnt];
		B[i][j] = arr1D[cnt++];
		//printf("%.2f ",A[i][j]);
        }
	//printf("\n");
    }

//multiplication
  for (i=0; i<SIZE; i++) 
    for (j=0; j<SIZE; j++) {
      C[i][j]=0.0;
      for (k=0; k<SIZE; k++)
      	C[i][j] += A[i][k]*B[k][j];
    }

 	/* print results */
        fprintf(fp,"\n%d matrixMult %d ",cid,SIZE);
        for (i=0; i<SIZE; i++)
              for (j=0; j<SIZE; j++)
		fprintf(fp,"%.2f ",C[i][j]);		
}
/////////////////////////////////////////////////////////////////////






