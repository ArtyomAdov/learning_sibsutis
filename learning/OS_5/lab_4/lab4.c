#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

char* Convert_Command(char* buf)//перевод команды терминала в команду консоли
{
	if(!strncmp(buf,"clear",5))//если введенная команда соответсвует clear возвращаем cls
	{
		return "cls";
	}
	if(!strncmp(buf,"ifconfig",8))
	{
		return "ipconfig";
	}
	if(!strncmp(buf,"users",5))
	{
		return "net user";
	}
	if(!strncmp(buf,"bash",4))
	{
		return "cmd";
	}
	if(!strncmp(buf,"exit",4)) // если был введен exit 
	{
		return NULL;//возвращаем NULL (для выхода из бесконечного цикла в main)
	}
	printf("command not found in bash synonym\n");//выводим сообщение о том что команда не
												// была найдена среди синонимов bash команд
	return buf; // возвращаем неизмененную команду
}

int main()
{
	while(1)//бесконечный цикл
	{
		char* buf = NULL; //переменная для ввода комнады пользователем
		char* conv = NULL; // переменная для получения синонима из bash команды для cmd
		char path[MAX_PATH]; // переменная для хранения текущей директории
		char symbol = '0'; // переменная использующаяся для ввода пользователем команды посимвольно
		int buf_size = 10; // начальное количество символов в команде пользователя
		if(GetCurrentDirectory(MAX_PATH,path) == 0) //встроенная функция получения текущей директории
		{
			printf("couldn't get the current directory\n");// сообщение о том тчо директория не найдена
			return 1; //завершение работы с ошибкой
		}
		printf("%s ",path); //печать текущей директории
		buf = (char*) calloc (buf_size, sizeof(char)); //выделение памяти под команду пользователя
		for(short int i = 0; (symbol != '\n'); i++) //пока пользователь не нажмет enter продолжаем принимать ввод
		{
			symbol = getc(stdin); // ввод одного символа
			if(buf_size <= i) // проверка что количество символов не превышает размер массива команды
			{//если превышает то
				buf_size += buf_size; // увеличиваем размер массива команды вдвое
				buf = (char*)realloc(buf,buf_size); // перевыделяем память для массива команды
				if(buf == NULL)// если произошла ошибка во время выделения памяти
				{
					printf("Error: fail realloc\n");// сообщение об ошибке функции realloc
					return 1;//завершение работы с ошибкой
				}
			}
			buf[i] = symbol;//запись в массив команд символа введенного пользователем
		}
		conv = Convert_Command(buf); // вызываем функция для конвертирования
		if(conv==NULL) // если был возвращен NULL 
		{
			return 0;//завершаем работу без ошибки
		}
		char* com[] = {"cmd","/C",conv,NULL};  // создаем двумерный массив для функции spawnvp и заполняем его
		_spawnvp(_P_WAIT,com[0],com);//выполняем функцию spawnvp приостанавливая родительский процесс
	}
	return 0;
}
