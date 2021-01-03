#include <windows.h>
#include <imagehlp.h>
#include <stdio.h>

// #define 

int main(int argc, char* argv[])
{
    //my check
    if(argv[0] == NULL)
    {
        printf("argv err\n");
        return 0;
    }
    if(argc == 1)
    {
        printf("1)argc err\n");
        return 0;
    }
    if(argc == 2)
    {
        printf("2)argc tru\n");
        printf("%s\n",argv[0]);
        printf("%s\n",argv[1]);
        // return 0;
    }
    //end check need delete in release version
    LOADED_IMAGE LoadedImage;
    PUCHAR BaseAddress;
    DWORD RVAExpDir, VAExpAddress;
    IMAGE_EXPORT_DIRECTORY* ExpTable;
    char* sName;
    DWORD nNames;
    char* pName;
    char** pNames;
    DWORD i;
    //Загружаем PE-файл
    if(!MapAndLoad("imagehlp", NULL, &LoadedImage, TRUE, TRUE))
    {
        printf("Something's wrong!\n");
        system("PAUSE");
        exit(1);
    }
    //Считываем базовый адрес загрузочного модуля
    BaseAddress=LoadedImage.MappedAddress;
    printf("0x%lx - Base Address\n",(unsigned long)BaseAddress);
    //Определяем относительный виртуальный адрес - RVA, таблицы экспорта
    RVAExpDir= LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    printf("0x%lx -RVA\n", RVAExpDir);
    //Определяем виртуальный адрес массива строк по его RVA
    VAExpAddress=(DWORD)ImageRvaToVa(LoadedImage.FileHeader,
    BaseAddress, RVAExpDir,NULL);
    printf("0x%lx -VA\n",VAExpAddress);
    ExpTable = (IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
    //Определяем виртуальный адрес строки - имени PE-файла,
    //по его RVA
    sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->Name,NULL);
    printf("Name of PEF: %s\n",sName);
    //Определяем виртуальный адрес массива строк по его RVA
    pNames=(char**)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames,NULL);
    //Считываем количество экспортируемых имен из таблицы
    //экспорта
    nNames=ExpTable->NumberOfNames;
    // printf("Exported data: %s\n",pName);
    for(i = 0; i < nNames; i++)
    {
        //Определяем виртуальный адрес i-ого имени по его RVA
        pName = (char*)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, (DWORD)*pNames,NULL);
        printf("%s\n",pName);
        *pNames++; //переходим к следующей строке
    }
    UnMapAndLoad(&LoadedImage);
    getch();
    return 0;
}