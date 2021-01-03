#include <windows.h>  
#include <stdio.h>

void DumpImports(PBYTE pbyFile, IMAGE_SECTION_HEADER *pSectionHeader, IMAGE_NT_HEADERS32 *pNtHeader) 
{
	IMAGE_IMPORT_DESCRIPTOR *pImportDescriptor; 
	IMAGE_THUNK_DATA *thunk;
	IMAGE_IMPORT_BY_NAME *pImportByName;
	
   	pImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*) ((PBYTE)pbyFile + pSectionHeader->PointerToRawData + 
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - pSectionHeader->VirtualAddress); 

	printf("Imported data:\n");
	while (pImportDescriptor->TimeDateStamp || pImportDescriptor->Name) { //перебираем список dll	   
    	printf("Name of PEF: %s\n", (PBYTE)(pbyFile + pSectionHeader->PointerToRawData + pImportDescriptor->Name - pSectionHeader->VirtualAddress)); //название dll  
    	
       	//RVA-смещение на массив указателей на функции  
       	thunk = (IMAGE_THUNK_DATA*)pImportDescriptor->Characteristics;  
       	if (!thunk) thunk = (PIMAGE_THUNK_DATA)pImportDescriptor->FirstThunk;  
       	thunk = (PIMAGE_THUNK_DATA)((PBYTE)thunk + (DWORD)pbyFile + pSectionHeader->PointerToRawData - pSectionHeader->VirtualAddress);  	  
       	
		while (thunk->u1.AddressOfData) { //перебираем функции  
            if (!(thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)) {  
            	pImportByName = (IMAGE_IMPORT_BY_NAME*)thunk->u1.AddressOfData;  
               	pImportByName = (IMAGE_IMPORT_BY_NAME*)((PBYTE)pImportByName + (DWORD)pbyFile + pSectionHeader->PointerToRawData - pSectionHeader->VirtualAddress);  
	       		printf("     %s\n", pImportByName->Name); //выводим имя функции 
            }  
            thunk++;  
        }  
        pImportDescriptor++;  
    }  
}

int main(int argc, char *argv[])  
{     
    HANDLE hSrcFile, hMapSrcFile;
	PBYTE pSrcFile;
	IMAGE_DOS_HEADER *pDosHeader; 
	
	hSrcFile = CreateFile("C:\\Program Files\\Internet Explorer\\iexplore.exe"/*"ostd2.dll"/*"C:\\Windows\\system32\\kernel32.dll*//*"C:\\Notepad++Portable\\Notepad++Portable.exe"*/, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hSrcFile == INVALID_HANDLE_VALUE)
		return 1;

	hMapSrcFile = CreateFileMapping(hSrcFile, NULL, PAGE_READONLY, 0, 0, NULL);
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
				if(pFirstSectionHeader[i].VirtualAddress <= pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress &&
					pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress < pFirstSectionHeader[i].VirtualAddress + pFirstSectionHeader[i].Misc.VirtualSize) {
					printf("0x%lx -RVA\n", pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
					
					DumpImports((PBYTE)pDosHeader, &pFirstSectionHeader[i], pNtHeader);
				}
			}
		}
	}	
	UnmapViewOfFile(pSrcFile);  
    CloseHandle(hMapSrcFile);  
    CloseHandle(hSrcFile); 
	return 0;
}
