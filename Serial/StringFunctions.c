#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAXCHAR 100000

int palindrome(char*);
int stringLength(char*);
int compare_string(char*, char*);
int multiply(int,int [],int);
int factorial(char*,int,FILE *);
int getlength(char[]);
void reverse(char[],int,FILE *);
int armstrong(char*);
long int power(char*,char*);

 
int palindrome(char *string)
{
   int i,len,flag=0;
	
	strtok(string, "\n");
	len=strlen(string);

	for (i=0;i<len;i++) {
		if(string[i]==string[len-i-1])
		     flag=flag+1;
	}
	if(flag==len)
	   return 1;
	else
	   return 0;
}
 
////////////////
int stringLength(char *string)
{
   int length = 0;  
 
   while(*string)
   {
      length++;
      string++;
   }
 
   return length;
}
 
//////////////////////////////////////////
int getlength(char line[MAXCHAR]){

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

void reverse(char line[MAXCHAR],int cid, FILE *fptr)
{
  char str[MAXCHAR];
  char rev[MAXCHAR];
  int i=-1,j=0;

  char *rest = strchr(line, ' ');
  char *res;
  
  strcpy(str,rest);
 
   while(str[++i]!='\0');

    while(i>=0)
     rev[j++] = str[--i];

    rev[0] = ' ';
    fprintf(fptr,"\n%d reverseString%s",cid,rev);

 }

/////////////////////////////
 
int compare_string(char *first, char *second)
{
   strtok(second, "\n");

   while(*first==*second)
   {
      if ( *first == '\0' || *second == '\0' )
         break;
 
      first++;
      second++;
   }
   if( *first == '\0' && *second == '\0' )
      return 1;
   else
      return 0;
}

/*******************Factorial of large numbers and prints them **************************************/
int factorial(char *data,int cid,FILE *fptr)
{
    int n = atoi(data);
    int res[MAXCHAR];
 
    // Initialize result
    res[0]=1;
    int res_size = 1,i,x;
 
    // Factorial formula n! = 1 * 2 * 3 * 4...*n
    for (x=2; x<=n; x++)
        res_size = multiply(x, res, res_size);
 
    fprintf(fptr,"\n%d factorial ",cid);
    for (i=res_size-1; i>=0; i--)
        fprintf(fptr,"%d",res[i]);
	//printf("\n");
	
return 0;
}
 
int multiply(int x,int res[], int res_size)
{
    int carry = 0,i;  // Initialize carry
 
    // One by one multiply n with individual digits of res[]
    for (i=0; i<res_size; i++)
    {
        int prod = res[i] * x + carry;
        res[i] = prod % 10;  // Store last digit of 'prod' in res[]
        carry  = prod/10;    // Put rest in carry
    }
 
    // Put carry in res and increase result size
    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_size++;
    }
    return res_size;
}

/*******************Factorial of large numbers and prints them **************************************/

////////////////////////Armstrong////////////////
int armstrong(char *data){
	
  int n,n1, rem, num=0;
 
  n = atoi(data); 	
  n1=n;
  while(n1!=0)
  {
      rem=n1%10;
      num+=rem*rem*rem;
      n1/=10;
  }
  if(num==n){
   // printf("\n%d is an Armstrong number.",n);
    return 1;
  }
  else
    //printf("\n%d is not an Armstrong number.",n);
    return 0;
}
////////////////////////////////////////////////
long int power(char *data,char *data2){

  int pow,num,i=1;
  long int sum=1;

    num = atoi(data);
    pow = atoi(data2);

   while(i<=pow){
            sum=sum*num;
            i++;
  }
  //printf("\n%d to the power %d is: %ld",num,pow,sum);
  return sum;
}

/////////////////////////////////////////////////

