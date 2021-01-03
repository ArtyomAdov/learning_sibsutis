#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <imagehlp.h>

int main(int argc, char* argv[])
{
	LOADED_IMAGE LoadedImage;
	PUCHAR BaseAddress;
	DWORD RVAExpDir, VAExpAddress, ppp;
	IMAGE_EXPORT_DIRECTORY* ExpTable;
	char* sName;
	DWORD nNames;
	char* pName;
	char** pNames;	
	DWORD i;
	
	std::ofstream fout("export.txt", std::ofstream::out);
	//Загружаем PE-файл
	if (!MapAndLoad(argv[1], NULL, &LoadedImage, TRUE, TRUE))
	{
		printf("Something's wrong!\n");
		exit(1);
	}	
	//Считываем базовый адрес загрузочного модуля
	BaseAddress = LoadedImage.MappedAddress;
	printf("0x%lx - Base Address\n", BaseAddress);
	
	//Определяем относительный виртуальный адрес - RVA, таблицы экспорта
	RVAExpDir = LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	printf("0x%lx - RVA of export table\n", RVAExpDir);
	
	//Определяем виртуальный адрес массива строк по его RVA
	VAExpAddress = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, RVAExpDir, NULL);
	printf("0x%lx - VA of export table\n", VAExpAddress);
	ExpTable = (IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
	
	//Определяем виртуальный адрес строки - имени PE-файла, //по его RVA
	sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->Name, NULL);
	printf("Name of PE-file: %s\n", sName);
	
	//Определяем виртуальный адрес массива строк по его RVA
	ppp = (DWORD)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);
	printf("0x%lx - VA of PE-file\n", ppp);
	
	pNames = (char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);
	
	//Считываем количество экспортируемых имен из таблицы //экспорта
	nNames = ExpTable->NumberOfNames;
	printf("Exported data: %u\n", nNames);
	for (i = 0; i < nNames; i++)
	{
		//Определяем виртуальный адрес i-ого имени по его RVA
		pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames, NULL);
		//printf("%s\n",pName);
		fout << pName << std::endl;
		*pNames++; //переходим к следующей строке
	}
	fout.close();
	UnMapAndLoad(&LoadedImage);
	
	return 0;
}
