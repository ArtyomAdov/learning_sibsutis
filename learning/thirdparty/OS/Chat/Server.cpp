#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"advapi32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#define PORT 1334
#define SERVICENAME "Server_of_Chat"

using namespace std;

SERVICE_STATUS          wserv_testStatus; 
SERVICE_STATUS_HANDLE   wserv_testStatusHandle; 
 
SOCKET servSock, usersList[2];
int usersCount = 0;
 
DWORD WINAPI work(LPVOID clientSocket)
{
    int retVal;
    char szReq[256];
    int exit;
    SOCKET clientSock;
 
    clientSock = *((SOCKET *)clientSocket);
 
    while (true)
    {
        retVal = recv(clientSock, szReq, 256, 0);
 
        if (retVal == 0)
        {
            printf("Client disconnected\n");
            closesocket(clientSock);
            printf("Connection closed\n");
            return SOCKET_ERROR;
        }
        if (retVal == SOCKET_ERROR)
        {
            printf("Unable to recv\n");
            closesocket(clientSock);
            printf("Connection closed\n");
            return SOCKET_ERROR;
        }
        else
            szReq[retVal] = '\0';
 
        printf("Data received\n");
        int i;
 
        printf("Client>%s\n", szReq);
        char szResp[256];
        sprintf(szResp, "%s", szReq);
 
        printf("Sending response from server\n");
        for (i = 0; i < usersCount; i++)
        {
            SOCKET tempSock; 
            tempSock = usersList[i];

            if (tempSock != clientSock) 
				retVal = send(tempSock, szResp, 256, 0);
        }
 
        if (retVal == SOCKET_ERROR)
        {
            printf("Unable to send\n");
            closesocket(clientSock);
            printf("Connection closed\n");
            return SOCKET_ERROR;
        }
    }
}
 
int serv()
{
    char buff[1024];
    int retVal;
 
    if (WSAStartup(0x202, (WSADATA *)&buff[0]))
    {
    	printf("Unable to create winsock\n");
        return 1;
    }
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servSock == INVALID_SOCKET)
    {
        printf("Unable to create socket\n");
        WSACleanup();
        system("pause");
        return SOCKET_ERROR;
    }
 
    SOCKADDR_IN sin;
    char* localIP;
    //hostent* localHost;
 
   // localHost = gethostbyname("");
    //localIP = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = 0;
 
    retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
    if (retVal == SOCKET_ERROR)
    {
        printf("Unable to bind\n");
        return SOCKET_ERROR;
    }
    printf("Server started \n");
 
    while (true)
    {
        retVal = listen(servSock, 10);
        if (retVal == SOCKET_ERROR)
        {
            printf("Unable to listen\n");
            WSACleanup();
            return SOCKET_ERROR;
        }
 
        SOCKET clientSock;
        SOCKADDR_IN from;
        int fromlen = sizeof(from);
 
        clientSock = accept(servSock, (struct sockaddr*)&from, &fromlen);
        if (clientSock == INVALID_SOCKET)
        {
            printf("Unable to accept\n");
            WSACleanup();
            return SOCKET_ERROR;
        }
        printf("New connection accepted from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port));
 
        usersList[usersCount] = clientSock;
        usersCount++;
 
        DWORD threadID;
        CreateThread(NULL,NULL,work,&clientSock,NULL,&threadID);
    }
    closesocket(servSock);
    WSACleanup();
    return 0;
}

VOID __stdcall CtrlHandler (DWORD Opcode) 
{     
	DWORD status;  
    switch (Opcode)     
	{         
	case SERVICE_CONTROL_PAUSE: 
            wserv_testStatus.dwCurrentState = SERVICE_PAUSED;
			break; 
         case SERVICE_CONTROL_CONTINUE: 
            wserv_testStatus.dwCurrentState = SERVICE_RUNNING; 
            break;          
		 case SERVICE_CONTROL_STOP: 
            wserv_testStatus.dwWin32ExitCode = 0; 
            wserv_testStatus.dwCurrentState  = SERVICE_STOPPED; 
            wserv_testStatus.dwCheckPoint    = 0; 
            wserv_testStatus.dwWaitHint      = 0;  
            if (!SetServiceStatus (wserv_testStatusHandle, &wserv_testStatus))            
                status = GetLastError(); 
            return;          
		 default: 
         	 break;
	}      

    if (!SetServiceStatus (wserv_testStatusHandle,  &wserv_testStatus))     
        status = GetLastError(); 
	return; 
}  

void __stdcall wserv_testStart (DWORD argc, LPTSTR *argv) 
{     
	DWORD status; 

    wserv_testStatus.dwServiceType        = SERVICE_WIN32; 
    wserv_testStatus.dwCurrentState       = SERVICE_START_PENDING; 
    wserv_testStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    wserv_testStatus.dwWin32ExitCode      = 0; 
    wserv_testStatus.dwServiceSpecificExitCode = 0; 
    wserv_testStatus.dwCheckPoint         = 0; 
    wserv_testStatus.dwWaitHint           = 0;  
    wserv_testStatusHandle = RegisterServiceCtrlHandler(TEXT(SERVICENAME), CtrlHandler);  
   
	if (wserv_testStatusHandle == (SERVICE_STATUS_HANDLE)0)     
		return;     
	  
    wserv_testStatus.dwCurrentState       = SERVICE_RUNNING; 
    wserv_testStatus.dwCheckPoint         = 0; 
    wserv_testStatus.dwWaitHint           = 0;  
    if (!SetServiceStatus (wserv_testStatusHandle, &wserv_testStatus))     
        status = GetLastError(); 

	FILE* fp;
	SYSTEMTIME stSystemTime;

	while (wserv_testStatus.dwCurrentState!=SERVICE_STOPPED)
	{
		if (wserv_testStatus.dwCurrentState!=SERVICE_PAUSED)
		{
			serv();
		}
		Sleep(5000);
	}
	return; 
} 

void main(int argc, char *argv[])
{
	SERVICE_TABLE_ENTRY   DispatchTable[] =     
	{ 
        { TEXT(SERVICENAME), wserv_testStart      }
		,{ NULL,              NULL                }     
	};  
	if (argc > 1 && !stricmp(argv[1], "delete"))
	{
		SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if (!scm) 
		{
			cout << "Can't open SCM\n";
			exit(1);
		}
		SC_HANDLE svc = OpenService(scm, SERVICENAME, DELETE);
		if (!svc)
		{
			cout << "Can't open service\n";
			exit(2);
		}
		if (!DeleteService(svc))
		{
			cout << "Can't delete service\n";
			exit(3);
		}
		cout << "Service deleted\n";
		CloseServiceHandle(svc);
		CloseServiceHandle(scm);
		exit(0);
	}
	if (argc > 1 && !stricmp(argv[1], "setup"))
	{
		char pname[1024];
		pname[0] = '"';
		GetModuleFileName(NULL, pname + 1, 1023);
		strcat(pname, "\"");
		SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE),svc;
		if (!scm) 
		{
			cout << "Can't open SCM\n";
			exit(1);
		}
		if (!(svc = CreateService(scm, SERVICENAME, SERVICENAME, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, pname, NULL, NULL, NULL, NULL, NULL)))
		{
			cout << "Registration error!\n";
			exit(2);
		}
		cout << "Successfully registered " << pname << "\n";
		CloseServiceHandle(svc);
		CloseServiceHandle(scm);
		exit(0);
	}

	if (!StartServiceCtrlDispatcher( DispatchTable))     
	{ 

        
	} 
}
