#include <stdio.h>
#include <string.h>
#include "computation.c"
#include "timing.c"
#include "StringFunctions.c"
#include "NumericalFunctions.c"
#define MAXCHAR 100000

void worker(int,char [],FILE *);

char *accepted_strings[] = {
	"palindrome","factorial","reverseString","stringLength","armstrong",
	"power","compareString","findMaximum","linearSearch","bubbleSort","mergeSort","comp\n","matrixMult","dfs"};


int main ()
{
   static const char filename[] = "commands_100.txt";
   FILE *file = fopen ( filename, "r" );
   
   FILE *fptr = fopen("output_serial.txt","w");
   int cid=0;
  
start();
   if ( file != NULL )
   {
      char line [MAXCHAR];
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
	worker(++cid,line,fptr);
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); 
   }
stop();

   return 0;
}


int select_str(char *s)
{
	int i;
	for (i=0; i < sizeof accepted_strings/sizeof *accepted_strings;i++)
	if (!strcmp(s, accepted_strings[i]))

	return i;
	return -1;
}

void worker(int cid,char line[MAXCHAR],FILE *fptr){

 char * command;
 char * data;
 char * data2;
 int id,result,length,arm,comp,index;
 long int pow;
 double max,compute;
 char lineMax[MAXCHAR];

// storing the numbers of the line
size_t destination_size = sizeof (lineMax);
strncpy(lineMax, line, destination_size);
lineMax[destination_size - 1] = '\0';

	//printf("Complete line: %s",line);
   	command = strtok (line," ");
  	//printf ("Command %s123",command);
	data = strtok (NULL," ");
        data2 = strtok (NULL," ");

	//printf ("Data %s\n",data);


	switch( id = select_str(command)) {
	
	case 0: 
		result = palindrome(data);
		if(cid==1)
			fprintf(fptr,"%d palindrome %d",cid,result);
		else
			fprintf(fptr,"\n%d palindrome %d",cid,result);
		break;
	case 1: 
		factorial(data,cid,fptr);
		break;

	case 2:
		reverse(lineMax,cid,fptr);
		break;

	case 3:
		length = stringLength(data);
		fprintf(fptr,"\n%d stringLength %d ",cid,length);
		break;

	case 4:
		arm = armstrong(data);
		fprintf(fptr,"\n%d armstrong %d ",cid,arm);
		break;

	case 5:
		pow = power(data,data2);
		fprintf(fptr,"\n%d power %ld ",cid,pow);
		break;

	case 6:
		comp = compare_string(data,data2);
		fprintf(fptr,"\n%d compareString %d ",cid,comp);
		break;

	case 7:
		max = findMaximum(lineMax);
		fprintf(fptr,"\n%d findMaximum %.2f",cid,max);
		break;

	case 8:
		index = linearSearch(lineMax);
		fprintf(fptr,"\n%d linearSearch %d",cid,index);
		break;

	case 9:
		index = bubbleSort(lineMax,cid,fptr);
		break;

	case 10:
		index = mergeSort(lineMax,cid,fptr);
		break;
	
	case 11:
		compute = computation();
     		fprintf(fptr,"\n%d comp %lf",cid,compute);
		break;

	case 12:
		matrixMult(lineMax,cid,fptr);
		break;

	case 13:
		dfs(lineMax,cid,fptr);
		break;

       	
	default:
	fprintf(fptr,"\n%d Command not found",cid);
	break;
}
}
