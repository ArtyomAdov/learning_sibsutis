#include <stdio.h>
#include <windows.h>

#define ERROR_GET_WINDOWS_DIRECTORY 0b00000001
#define ERROR_GET_TEMP_PATH 0b00000010
#define ERROR_GLOBAL_MEMORY_STATUS 0b00000011

#define SIZE_FOR_USIZE 11
#define SIZE_FOR_NBUFFER_LENGTH 36

int main()
{
	SYSTEM_INFO lpSystemInfo;
	/*LP*/MEMORYSTATUSEX lpMemoryStatus;
	char* lpBuffer = NULL;
	int uSize = SIZE_FOR_USIZE;
	int nBufferLength = SIZE_FOR_NBUFFER_LENGTH;
	lpBuffer = (char*) calloc (uSize, sizeof(char));
	if(GetWindowsDirectory((LPTSTR)lpBuffer, (UINT)uSize) == NULL) {
		return ERROR_GET_WINDOWS_DIRECTORY;
	} else {
		fprintf(stdout, "Windows directory: %s\n", lpBuffer);
	}
	free(lpBuffer);
	lpBuffer = (char*) calloc (nBufferLength, sizeof(char));
	if(GetTempPath((DWORD)nBufferLength, (LPTSTR)lpBuffer) == NULL) {
		return ERROR_GET_TEMP_PATH;
	} else {
		fprintf(stdout, "Temp path: %s\n", lpBuffer);
	}
	free(lpBuffer);
	GetSystemInfo(&lpSystemInfo);
	fprintf(stdout, "Quantity processor core: %u\n", lpSystemInfo.dwNumberOfProcessors);
	fprintf(stdout, "Arhitecture of processor: %u\n", lpSystemInfo.dwProcessorType);
	fprintf(stdout, "Minimum custom address: %lp\n", lpSystemInfo.lpMinimumApplicationAddress);
	fprintf(stdout, "Maximum custom address: %lp\n", lpSystemInfo.lpMaximumApplicationAddress);
	lpMemoryStatus.dwLength = sizeof(lpMemoryStatus);
	if(!GlobalMemoryStatusEx(&lpMemoryStatus)) {
		return ERROR_GLOBAL_MEMORY_STATUS;
	}
	fprintf(stdout, "All physical memory: %I64d\n",lpMemoryStatus.ullTotalPhys);
	fprintf(stdout, "Avail physical memory: %I64d\n", lpMemoryStatus.ullAvailPhys);
	fprintf(stdout, "Used physical memory: %I64d\n", (lpMemoryStatus.ullTotalPhys - lpMemoryStatus.ullAvailPhys));
	fprintf(stdout, "Avail virtual memory: %I64d\n", lpMemoryStatus.ullAvailVirtual);
	fprintf(stdout, "Used virtual memory: %I64d\n", (lpMemoryStatus.ullTotalVirtual - lpMemoryStatus.ullAvailVirtual));
	return 0;
}
