#include <windows.h>
#include <stdio.h>
#include <imagehlp.h>

#define FILE_NAME "C:\\Windows\\system32\\notepad.exe"
#define FILE_NAME_PRINT "result.txt"
#define WRITE_ONLY "w"

PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(DWORD rva, PIMAGE_NT_HEADERS pNTHeader)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);
	for(unsigned int i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++)
	{
		if((rva >= section->VirtualAddress) && (rva < (section->VirtualAddress + section->Misc.VirtualSize)))
		{
			return section;
		}
	}
	return 0;
}

int main()
{
	HANDLE hFile = NULL;
	HANDLE hFileMapping = NULL;
	LPVOID lpFileBase = NULL;
	PIMAGE_THUNK_DATA thunk = NULL;
	PIMAGE_IMPORT_BY_NAME pOrdinalName = NULL;
	PIMAGE_DOS_HEADER pDOSHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_IMPORT_DESCRIPTOR importDesc = NULL;
	PIMAGE_SECTION_HEADER pSection = NULL;
    LPVOID buffer;
	FILE* file = NULL;
	int StartRVA = 0;
	int delta = 0;
	hFile = CreateFile(FILE_NAME, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //open file
	if(hFile == INVALID_HANDLE_VALUE)
    {
    	return 1;
	}
	file = fopen(FILE_NAME_PRINT,WRITE_ONLY);
	if(file == NULL)
	{
		return 2;
	}
	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL); //display file in memory
	if(hFileMapping == NULL)
	{
		return 3;
	}
	lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0); //convert in pointer
    if(lpFileBase == NULL)
	{
        return 4;
    }
    pDOSHeader = (PIMAGE_DOS_HEADER)lpFileBase; //pointer on DOS header
    if(pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
    	return 5;
	}
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + pDOSHeader->e_lfanew); //get adress NT header (PE)
    if(pNTHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return 6;
	}
	StartRVA = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress; //get adress rva import
    if(StartRVA == 0)
    {
    	return 7;	
	}
	pSection = GetEnclosingSectionHeader(StartRVA, pNTHeader); //get virtual adress section
    if(pSection == NULL)
    {
    	return 8;
	}
    delta = pSection->VirtualAddress - pSection->PointerToRawData; //calculate distance between sections
    importDesc = (PIMAGE_IMPORT_DESCRIPTOR)(StartRVA - delta + (DWORD)lpFileBase); //calculate descriptor for table import dll
	while(importDesc->Name)
	{
		buffer = ((PBYTE)(importDesc->Name) - delta + (DWORD)lpFileBase);
		fprintf(file,"%s\n",buffer);
		thunk = (PIMAGE_THUNK_DATA)((PBYTE)importDesc->FirstThunk - delta + (DWORD)lpFileBase); //calculate pointer for dll 
        while(thunk->u1.AddressOfData)
		{
        	if(!(thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)) //if function import and used first
			{
                pOrdinalName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)thunk->u1.AddressOfData - delta + (DWORD)lpFileBase);//function name
	            buffer = pOrdinalName->Name;
	            fprintf(file,"\t%s\n",buffer);
            }
            thunk++;
        }
        importDesc++;
    }
	UnmapViewOfFile(lpFileBase);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
    return 0;
}  
