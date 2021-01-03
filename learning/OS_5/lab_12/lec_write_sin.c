#include <windows.h>
#include <stdio.h>
#include <math.h>
#define pi 3.141592
#define DATA_SIZE 1024
struct _data {
int index;
double x;
double y;
};
int main() {
struct _data Data[DATA_SIZE];
HANDLE hFile;
DWORD N;
for (int i = 0; i < DATA_SIZE; i++) {
Data[i].index = i;
Data[i].x = i*(2.0*pi / DATA_SIZE);
Data[i].y = sin(Data[i].x);
}
hFile = CreateFile("test.dat",
GENERIC_READ | GENERIC_WRITE,
0, NULL,OPEN_ALWAYS,
FILE_ATTRIBUTE_NORMAL, NULL);
WriteFile(hFile, Data, sizeof(struct _data)
*DATA_SIZE, &N, NULL);
CloseHandle(hFile);
return 0;
}

