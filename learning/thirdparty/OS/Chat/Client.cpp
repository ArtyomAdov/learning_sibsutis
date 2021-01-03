#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"user32.lib")
#pragma comment (lib,"gdi32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>

#define PORT 1334 
#define SERVERADDR "192.168.1.4"

using namespace std;
 
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND HEdit, Hedit, hSent, hClean, hDel;
char str[50];
HWND hWnd;			
SOCKET clientSock; 
DWORD threadID;  
			
DWORD WINAPI get_message(LPVOID clientSocket);
DWORD WINAPI send_message(LPVOID clientSocket);
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	LPCSTR lpszAppName = "Chat";
	wc.lpszClassName = lpszAppName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = MyWndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);      
	wc.lpszMenuName = 0;  
	wc.hbrBackground = /*(HBRUSH)(COLOR_WINDOW + 1);*/CreateSolidBrush(RGB(20, 30, 40)); 
	wc.style = CS_HREDRAW | CS_VREDRAW;   
	
	if (!RegisterClass(&wc)) 
		return 0;
		
	hWnd = CreateWindow(lpszAppName, "Чат", WS_OVERLAPPEDWINDOW | WS_BORDER, 0, 0, 480, 400, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);      
		DispatchMessage(&msg);
		//CreateThread(NULL, NULL, send_message, &clientSock, NULL, &threadID); 
		CreateThread(NULL, NULL, get_message, &clientSock, NULL, &threadID); 
	}
	
	return msg.wParam;
}

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	char buff[1024];
    int retVal = 0;

	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			HEdit = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE, 5, 5, 450, 300, hWnd, (HMENU)1, NULL, NULL);
			hSent = CreateWindow("BUTTON", "Отправить", WS_VISIBLE | WS_CHILD | WS_BORDER, 360, 310, 75, 40, hWnd, (HMENU)2, NULL, NULL);
			Hedit = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 5, 310, 285, 40, hWnd, (HMENU)3, NULL, NULL);
			hClean = CreateWindow("BUTTON", "Очистить", WS_VISIBLE | WS_CHILD | WS_BORDER, 292, 310, 67, 40, hWnd, (HMENU)4, NULL, NULL); 
			hDel = CreateWindow("BUTTON", "x", WS_VISIBLE | WS_CHILD | WS_BORDER, 436, 310, 25, 40, hWnd, (HMENU)5, NULL, NULL); 
    		
    		if (WSAStartup(0x202, (WSADATA *)&buff[0]))
    		{
    				//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Не удалось инициализировать winsock\n"));
    				MessageBox(hWnd, "Не удалось инициализировать winsock", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
        			return 1;
    		}
 
			clientSock = socket(AF_INET, SOCK_STREAM, 0);
    		if (clientSock == SOCKET_ERROR)
    		{
    			//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Не удалось создать сокет\r\n"));	
    			MessageBox(hWnd, "Не удалось создать сокет", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
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
					//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Недействительный адрес: \r\n"));
					//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)(SERVERADDR));
					MessageBox(hWnd, "Недействительный адрес", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
					closesocket(clientSock);     
					WSACleanup();   
					return 1;   
				}
 
    		retVal = connect(clientSock, (LPSOCKADDR)&dest_addr, sizeof(dest_addr));
    		if (retVal == SOCKET_ERROR)
    		{
    			//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Не удалось установить связь с сервером\r\n"));
    			MessageBox(hWnd, "Не удалось установить связь с сервером", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
        		WSACleanup();
        		return 1;
    		}
    		//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Связь с сервером установлена\n"));
    		MessageBox(hWnd, "Связь с сервером установлена", "Сообщение о соединении", MB_OK | MB_ICONEXCLAMATION);
    		
        	//DWORD threadID;    		
    		//while (true)
    		//{
        	//	CreateThread(NULL, NULL, get_message, &clientSock, NULL, &threadID);
        	//	CreateThread(NULL, NULL, send_message, &clientSock, NULL, &threadID);       
    		//}
    		
			break;	
		case WM_COMMAND:
			if (LOWORD(wParam) == 2)
			{
        		CreateThread(NULL, NULL, send_message, &clientSock, NULL, &threadID); 
			}
			else if (LOWORD(wParam) == 4)
			{
				SetWindowText(Hedit, 0);	
			}
			else if (LOWORD(wParam) == 5)
			{
				SetWindowText(HEdit, 0);	
			}			
			
			break;
		default:  
			return DefWindowProc(hWnd, message, wParam, lParam);
			
	}
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
    	//SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Не удалось считать данные из сокета\r\n"));
    	MessageBox(hWnd, "Не удалось считать данные из сокета", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
        WSACleanup();
        return 1;
    }
    if (retVal > 0)
    {
        char *Resp;
        Resp = szResponse;
        SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("My friend: "));
        SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)Resp);
        SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("\r\n"));
    }
}
 
DWORD WINAPI send_message(LPVOID clientSocket)
{
    int retVal;
    char pBuf[256], exit[5];
    SOCKET clientSock;
 
    clientSock = *((SOCKET *)clientSocket);

	//gets_s(pBuf);	
	GetWindowText(Hedit, pBuf, 50);
	SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("I: "));
	SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)pBuf);
	SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("\r\n"));
	SetWindowText(Hedit, 0);

    retVal = send(clientSock, pBuf, strlen(pBuf), 0);
    if (retVal == SOCKET_ERROR)
    {
        //SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)("Не удалось отправить сообщение\r\n"));
        MessageBox(hWnd, "Не удалось отправить сообщение", "Сообщение об ошибке", MB_RETRYCANCEL | MB_ICONERROR);
        WSACleanup();
        return 1;
    }
}
