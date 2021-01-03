#include <windows.h>
#pragma data_seg(".M_SH")

struct _shareTest 
{
	double g;
	int n;
}shareTest = {0.0, 1};

#pragma data_seg()
#pragma comment(linker, "/SECTION:.M_SH,RWS" )

