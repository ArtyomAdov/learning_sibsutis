#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#define PORT 1952
#define SERVERADDR "127.0.0.1"

int main(int argc, char* argv[])
{
	char buff[1024];
	struct sockaddr_in dest_addr;
	SOCKET my_sock;
	struct hostent *hst;
	int nsize;

	if (WSAStartup(0x202,(WSADATA *)&buff[0]))
	{
		printf("WSAStart error %d\n", WSAGetLastError());
		return -1;
 	}

 	my_sock = socket(AF_INET, SOCK_STREAM, 0);
 	if (my_sock < 0)
	{
 		printf("Socket() error %d\n", WSAGetLastError());
 		return -1;
 	}

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);

	if (inet_addr(SERVERADDR) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else

	if (hst == gethostbyname(SERVERADDR))
		((unsigned long *)&dest_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
 	else
 	{
 		printf("Invalid address %s\n", SERVERADDR);
 		closesocket(my_sock);
 		WSACleanup();
 		return -1;
 	}

	if (connect(my_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		printf("Connect error %d\n", WSAGetLastError());
		return -1;
	}
	
	printf("Connection with %s was established\n\
	Type quit for quit\n\n", SERVERADDR);

	while ((nsize == recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) != SOCKET_ERROR)
	{
		buff[nsize] = 0;
		printf("ServerToClient:%s", buff);
		printf("ClientToServer:");
		fgets(&buff[0], sizeof(buff)-1, stdin);
 		if (!strcmp(&buff[0], "quit\n"))
		{
			printf("Exit...");
			closesocket(my_sock);
			WSACleanup();
			return 0;
 		}
 		send(my_sock,&buff[0],nsize,0);
	}
	
	printf("Recv error %d\n", WSAGetLastError());
	closesocket(my_sock);
	WSACleanup();
 	return -1;
}
