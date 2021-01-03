#include <windows.h>  
#include <stdio.h>
#include <conio.h>

char *buff;

void DumpExports(PBYTE pbyFile, IMAGE_SECTION_HEADER *pSectionHeader, IMAGE_NT_HEADERS32 *pNtHeader)
{
	PDWORD pdwNameRVA;
	IMAGE_EXPORT_DIRECTORY *pExportDirectory;
 
	pExportDirectory = (IMAGE_EXPORT_DIRECTORY *)((PBYTE)pbyFile + pSectionHeader->PointerToRawData + 
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress - pSectionHeader->VirtualAddress);
	
	printf("Name of PEF: %s\n", pbyFile + pSectionHeader->PointerToRawData + pExportDirectory->Name - pSectionHeader->VirtualAddress);
	printf("Exported data:\n");

	pdwNameRVA = (PDWORD)(pbyFile + pSectionHeader->PointerToRawData + pExportDirectory->AddressOfNames - pSectionHeader->VirtualAddress);
	for (int i = 0; i < pExportDirectory->NumberOfNames; i++) {
		printf("     %s\n", (pbyFile + pSectionHeader->PointerToRawData + pdwNameRVA[i] - pSectionHeader->VirtualAddress));
		buff = (char*)(pbyFile + pSectionHeader->PointerToRawData + pdwNameRVA[i] - pSectionHeader->VirtualAddress);
	}
}

int main(int argc, char *argv[])  
{     
    HANDLE hSrcFile, hMapSrcFile;
	PBYTE pSrcFile;
	IMAGE_DOS_HEADER *pDosHeader; 
	
	hSrcFile = CreateFile(/*"ostd2.dll"*/"C:\\Windows\\system32\\kernel32.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hSrcFile == INVALID_HANDLE_VALUE)
		return 1;

	hMapSrcFile = CreateFileMapping(hSrcFile, NULL, PAGE_READONLY, 0, 0, "Zad2");
	if (!hMapSrcFile || hMapSrcFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hSrcFile);
		return 1;
	}

	pSrcFile = (PBYTE)MapViewOfFile(hMapSrcFile, FILE_MAP_READ, 0, 0, 0);
	if (!pSrcFile) {
		CloseHandle(hMapSrcFile);  
        CloseHandle(hSrcFile);
		return 1;
	}

	pDosHeader = (IMAGE_DOS_HEADER *)pSrcFile;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		printf("it is not a EXE file.\n");
		return 1;
	}

	if (pDosHeader->e_lfanew) {
		IMAGE_NT_HEADERS32 *pNtHeader = (IMAGE_NT_HEADERS32 *)((PBYTE)pDosHeader + pDosHeader->e_lfanew);
		IMAGE_SECTION_HEADER *pFirstSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
		
		if (pNtHeader->Signature == IMAGE_NT_SIGNATURE) {
			for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++) {
				if (pFirstSectionHeader[i].VirtualAddress <= pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress &&
					pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress < pFirstSectionHeader[i].VirtualAddress + pFirstSectionHeader[i].Misc.VirtualSize) {
					printf("0x%lx -RVA\n", pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
					
					DumpExports((PBYTE)pDosHeader, &pFirstSectionHeader[i], pNtHeader);
				}
			}
		}
	}	
	CopyMemory(pSrcFile, buff, sizeof(buff));
	getch();
	UnmapViewOfFile(pSrcFile);  
    CloseHandle(hMapSrcFile);  
    CloseHandle(hSrcFile);
	system("pause");
	return 0;
}
