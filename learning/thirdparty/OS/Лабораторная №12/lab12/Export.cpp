#include <windows.h>  
#include <stdio.h>

int main(int argc, char *argv[])  
{     
    HANDLE hSrcFile; 
	HANDLE hMapSrcFile; 
	PVOID pSrcFile; 
  
	IMAGE_DOS_HEADER *pDosHeader;   
	IMAGE_NT_HEADERS32 *pNtHdr;
	IMAGE_SECTION_HEADER *pFirstSectionHeader;
	IMAGE_SECTION_HEADER *pSectionHeader;
	IMAGE_EXPORT_DIRECTORY *pExportDirectory;

	hSrcFile = CreateFile("C:\\Notepad++Portable\\Notepad++Portable.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL); //открываем файл
	
    if (hSrcFile == INVALID_HANDLE_VALUE) return 0;   
    hMapSrcFile = CreateFileMapping(hSrcFile, NULL, PAGE_READONLY, 0, 0, NULL); //отображаем файл в память  
    if (!hMapSrcFile) {  
        CloseHandle(hSrcFile);  
        return 0;  
    }
	     
    pSrcFile = (PBYTE)MapViewOfFile(hMapSrcFile, FILE_MAP_READ, 0, 0, 0); // преобразовать в указатель  
    if (!pSrcFile) {  
        CloseHandle(hMapSrcFile);  
        CloseHandle(hSrcFile);  
        return 0;  
	}      
	
   	pDosHeader = (IMAGE_DOS_HEADER *)pSrcFile;
   	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) return 0;    
   	pNtHdr = (IMAGE_NT_HEADERS32 *)((PBYTE)pDosHeader + pDosHeader->e_lfanew);
   	//pFirstSectionHeader = (IMAGE_SECTION_HEADER *)((PBYTE)&pNtHdr->OptionalHeader + pNtHdr->FileHeader.SizeOfOptionalHeader);
   	pFirstSectionHeader = IMAGE_FIRST_SECTION(pNtHdr);
   	for (int i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++) {  
        if ((pFirstSectionHeader[i].VirtualAddress <= pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress) 
			&& (pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress < (pFirstSectionHeader[i].VirtualAddress + pFirstSectionHeader[i].Misc.VirtualSize))) 
			{
			pSectionHeader = &pFirstSectionHeader[i];
			pExportDirectory = (IMAGE_EXPORT_DIRECTORY *)((PBYTE)pSrcFile + pSectionHeader->PointerToRawData 
			+ pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress - pSectionHeader->VirtualAddress);	
			printf("Export : %s\n", (PBYTE)pExportDirectory->Name);		
		}
    }  
   	
    UnmapViewOfFile(pSrcFile);  
    CloseHandle(hMapSrcFile);  
    CloseHandle(hSrcFile);   
    system("PAUSE");
} 
