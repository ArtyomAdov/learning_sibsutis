#include <stdio.h>
#include <process.h>

void main()
{
	char* argv[]={ "notepad", NULL };
	//_spawnvp(_P_OVERLAY, argv[0],argv);
	_spawnvp(_P_NOWAIT, argv[0],argv);
	printf( "\nParent process is yet running." );
	exit(0);
}
