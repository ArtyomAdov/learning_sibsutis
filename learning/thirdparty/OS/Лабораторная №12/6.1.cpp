#include <windows.h>
#include <conio.h>

int main()	
{
	HANDLE hFileMap;
	LPVOID lpMapView;
	char* buff = "Hello,students!";
	
	hFileMap = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 256, "MyCommonRegion");
	lpMapView = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 256);
	CopyMemory(lpMapView, buff, sizeof("Hello,students!"));
	getch();
	UnmapViewOfFile(lpMapView);
	CloseHandle(hFileMap);
	
	return 0;
}
