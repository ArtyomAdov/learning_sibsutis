#include <windows.h>
#pragma data_seg(".M_SH")
int d[10] = {0};
double s = 0.0;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.M_SH,RWS")
