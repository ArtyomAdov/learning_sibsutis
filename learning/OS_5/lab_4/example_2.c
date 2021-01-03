#include <stdio.h>
#include <process.h>

void main()
{
	char* argv[] = {"cmd", "/C", "dir", NULL};
	_execvp(argv[0],argv);
	printf( "\nProcess was not created." );
	exit(0);
}
