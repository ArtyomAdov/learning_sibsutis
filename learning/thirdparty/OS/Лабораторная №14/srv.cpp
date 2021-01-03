#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#define MY_PORT 1952

int main(int argc, char* argv[])
{
	char buff[1024];
	SOCKET mysocket, client_socket;
	struct sockaddr_in local_addr, client_addr;
	int client_addr_size = sizeof(client_addr);
	
	if (WSAStartup(0x0202,(WSADATA *) &buff[0]))
	{
		printf("Error WSAStartup %d\n",
		WSAGetLastError());
		return -1;
 	}
	if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error socket %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	local_addr.sin_family = AF_INET;
 	local_addr.sin_port = htons(MY_PORT);
 	local_addr.sin_addr.s_addr = 0;
 	if (bind(mysocket,(struct sockaddr *) &local_addr, sizeof(local_addr))) 
	{
		printf("Error bind %d\n", WSAGetLastError());
 		closesocket(mysocket);
 		WSACleanup();
 		return -1;
 	}
 	if (listen(mysocket, 0x100))
 	{
 		printf("Error listen %d\n", WSAGetLastError());
 		closesocket(mysocket);
 		WSACleanup();
 		return -1;
 	}
 	printf("Waiting for calls\n");

 	while ((client_socket == accept(mysocket, (struct sockaddr *)&client_addr, &client_addr_size)))
	{
 		struct hostent *hst;
 		int bytes_recv;
 		hst = gethostbyaddr((char *)&client_addr.sin_addr.s_addr, 4, AF_INET);
 		printf("%s [%s] new connect!\n", (hst)?hst->h_name:"", inet_ntoa(client_addr.sin_addr));
 		send(client_socket, "Hello a new client!\n", sizeof("Hello a new client!\n"), 0);
 		//while ((bytes_recv == recv(client_socket, &buff[0], sizeof(buff), 0)) && bytes_recv != SOCKET_ERROR)
		//	send(client_socket, &buff[0], bytes_recv, 0);
		//printf("Client was disconnected\n");
 		closesocket(client_socket);
	}
	return 0;
}
