#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"user32.lib")
#pragma comment (lib,"gdi32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <locale.h>

#define PORT 1334 
#define SERVERADDR "192.168.1.4"

using namespace std; 

DWORD WINAPI send_message(LPVOID clientSocket);
DWORD WINAPI get_message(LPVOID clientSocket);
int Exit = 0;
			
int main()
{
	char buff[1024], client_name[50];
  	setlocale(LC_ALL, "Russian");
  	
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
   	{
   		printf("Не удалось инициализировать winsock, ошибка - \n", WSAGetLastError());
      	return 1;
   	}
 
    SOCKET clientSock;
	clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock == SOCKET_ERROR)
    {
        printf("Не удалось создать сокет\n");
        WSACleanup();
        return 1;
   	}
    		
	struct sockaddr_in dest_addr;  
    dest_addr.sin_family = AF_INET;    
	dest_addr.sin_port = htons(PORT);  
	HOSTENT *host;
	if (inet_addr(SERVERADDR) != INADDR_NONE)   
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);   
	else     
		if (host = gethostbyname(SERVERADDR)) 
			((unsigned long *)&dest_addr.sin_addr)[0] = ((unsigned long **)host->h_addr_list)[0][0];     
		else       
		{
			printf("Недействительный адрес: %s\n", SERVERADDR);   
			closesocket(clientSock);     
			WSACleanup();   
			return 1;   
		}
 
    if (connect(clientSock, (LPSOCKADDR)&dest_addr, sizeof(dest_addr)) == SOCKET_ERROR)
    {
        printf("Не удалось установить связь с сервером\n");
       	WSACleanup();
       	return 1;
    }
    printf("Связь с сервером установлена\n");
    printf("Общение производится только на английском языке!\n");
    
    while (Exit == 0)
    {
        DWORD threadID;
        CreateThread(NULL, NULL, get_message, &clientSock, NULL, &threadID);
        CreateThread(NULL, NULL, send_message, &clientSock, NULL, &threadID);       
    }
    closesocket(clientSock);
    WSACleanup();
    return 0;
}

DWORD WINAPI get_message(LPVOID clientSocket)
{
    int retVal;
    SOCKET clientSock;
    clientSock = *((SOCKET *)clientSocket);
    char szResponse[256];
    
    retVal = recv(clientSock, szResponse, 256, 0);
    if (retVal == SOCKET_ERROR)
    {
        //printf("Unable to recv\n");
        WSACleanup();
        //system("pause");
        return 1;
    }
    if (retVal > 0)
    {
        char *Resp;
        Resp = szResponse;
        printf("Собеседник: %s\n", Resp);
    }
}
 
DWORD WINAPI send_message(LPVOID clientSocket)
{
    int retVal, i;
    char pBuf[256], name[2], exit[5];
    SOCKET clientSock;
 
    clientSock = *((SOCKET *)clientSocket);

	gets_s(pBuf);	
    
    exit[0] = 'e';
    exit[1] = 'x';
    exit[2] = 'i';
    exit[3] = 't';
    exit[4] = '\0';
    
    if (strcmp(pBuf, exit) == 0) 
		Exit = 1;
    else
    {
        retVal = send(clientSock, pBuf, strlen(pBuf), 0);
        if (retVal == SOCKET_ERROR)
        {
            printf("Не удалось послать сообщение\n");
            WSACleanup();
            return 1;
        }
    }
}
