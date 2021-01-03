#include <windows.h>
#include <stdio.h>
#define DATA_SIZE 1024
struct _data {
	int index;
	double x;
	double y;
};

int main() {
	struct _data Data[64];
	HANDLE hFile;
	DWORD N;
	long n;
	hFile = CreateFile("test2.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for(int j = 0; j < DATA_SIZE / 64; j++) {
		SetFilePointer(hFile, 64 * j * sizeof(struct _data), NULL, FILE_BEGIN);
		ReadFile(hFile, Data, sizeof(struct _data) * 64, &N, NULL);
		for(int i = 0; i < 64; i++)
			printf("%d\t%g\t%g\n", Data[i].index, Data[i].x, Data[i].y);
		getchar();
	}
	CloseHandle(hFile);
	return 0;
}
