#include <stdio.h>
#include <process.h>

void main(int argc, char* argv[])
{
	if(argc<2) 
	{
		return;	
	}
	if(_execvp(argv[1], argv)== -1)
	{
		perror("execvp call : ");	
	}
/*
>lab4 calc
>lab4b «cmd» «/c» dir
*/
	printf("\nProcess was not created.");
	exit(0);
}
