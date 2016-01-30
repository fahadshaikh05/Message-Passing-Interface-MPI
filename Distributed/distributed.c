#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mpi.h"
#include "timing.c"
#include "computation.c"
#include "StringFunctions.c"
#include "NumericalFunctions.c"


#define MAXCHAR 100000
int TAG=0;
char buff[MAXCHAR];
int totalines;
char filename[20];

void master( int, FILE *);
int worker(int,char [],int);
int slave(int,int ,int);
int getrand(int );
MPI_Status stat;



/////////////////// Distributed////////////////////////
int main (int argc, char *argv[])
{
   
   static const char filename[] = "commands_100.txt";
   FILE *file = fopen ( filename, "r" );

   int lines=0;
   int numprocs;
   int myid;
   char ch;
   int i,cid=0,res=0;

   start();

   if(file == NULL)
	perror(filename);

    while(!feof(file))
    {
    ch = fgetc(file);
    if(ch == '\n')
    totalines++;
    }
    rewind(file);

      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
      MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    while ( fgets ( buff, sizeof buff, file ) != NULL ) {
    lines = lines + 1;
	if(myid == 0){
		  master(numprocs,file);
	 if (lines == totalines){
         printf("\n\n File is completed program terminating\n\n");
	 stop();
         exit(1);
     }

    }else{
       // printf("I am slave %d",myid);
          res=slave(myid,numprocs,lines);
    }
    }  fclose (file);

   

   MPI_Finalize();
   return 0;
}

/////////////////// Distributed////////////////////////

void master( int numprocs, FILE *file){
int i,res;
int dest = getrand(numprocs);

 MPI_Send(buff,sizeof buff, MPI_CHAR, dest, TAG, MPI_COMM_WORLD);
 MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, 999, MPI_COMM_WORLD, &stat);

}

int slave(int sid, int numprocs,int lines){

int i,res=0;

	 MPI_Recv(&buff, sizeof buff, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &stat);
	 res = worker(lines,buff,sid);
     MPI_Send(&res,1, MPI_INT,0, 999, MPI_COMM_WORLD);

	 if (lines == totalines){
         printf("\n\n File is completed program terminating\n\n");
         exit(1);
     }
	return res;
}

/////////////////// Distributed////////////////////////

char *accepted_strings[] = {
	"palindrome","factorial","reverseString","stringLength","armstrong",
	"power","compareString","findMaximum","linearSearch","bubbleSort","mergeSort","comp\n","matrixMult","dfs"};

int getrand(int max){
     return(rand()%(max-1)+1);
}


int select_str(char *s)
{
	int i;
	for (i=0; i < sizeof accepted_strings/sizeof *accepted_strings;i++)
	if (!strcmp(s, accepted_strings[i]))

	return i;
	return -1;
}

int worker(int cid,char line[MAXCHAR],int sid){


char filename[20]= "outMaster.txt";
sprintf(filename, "outSlave_%d.txt",sid);
FILE *fp = fopen(filename,"a");

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

   	command = strtok (line," ");
	data = strtok (NULL," ");
    data2 = strtok (NULL," ");

	switch( id = select_str(command)) {

	case 0:
		result = palindrome(data);
		if(cid==1)
			fprintf(fp,"%d palindrome %d",cid,result);
		else
			fprintf(fp,"\n%d palindrome %d",cid,result);
			fclose(fp);
		return 1;

	case 1:
		factorial(data,cid,fp);
                fclose(fp);
		return 1;

	case 2:
		reverse(lineMax,cid,fp);
		fclose(fp);
		return 1;

	case 3:
		length = stringLength(data);
		fprintf(fp,"\n%d stringLength %d ",cid,length);
		fclose(fp);
		return 1;

	case 4:
		arm = armstrong(data);
		fprintf(fp,"\n%d armstrong %d ",cid,arm);
		fclose(fp);
		return 1;

	case 5:
		pow = power(data,data2);
		fprintf(fp,"\n%d power %ld ",cid,pow);
		fclose(fp);
		return 1;

	case 6:
		comp = compare_string(data,data2);
		fprintf(fp,"\n%d compareString %d ",cid,comp);
		fclose(fp);
		return 1;

	case 7:
		max = findMaximum(lineMax);
		fprintf(fp,"\n%d findMaximum %.2f",cid,max);
		fclose(fp);
		return 1;

	case 8:
		index = linearSearch(lineMax);
		fprintf(fp,"\n%d linearSearch %d",cid,index);
		fclose(fp);
		return 1;

	case 9:
		index = bubbleSort(lineMax,cid,fp);
		fclose(fp);
		return 1;

	case 10:
		index = mergeSort(lineMax,cid,fp);
		fclose(fp);
		return 1;

	case 11:
		compute = computation();
     		fprintf(fp,"\n%d comp %lf",cid,compute);
		fclose(fp);
		return 1;

	case 12:
		matrixMult(lineMax,cid,fp);
		fclose(fp);
		return 1;

	case 13:
		dfs(lineMax,cid,fp);
		fclose(fp);
		return 1;

	default:
	   	 fprintf(fp,"\n%d Command not found",cid);
	   	 fclose(fp);
	    return 1;
    }
    return 0;
}

