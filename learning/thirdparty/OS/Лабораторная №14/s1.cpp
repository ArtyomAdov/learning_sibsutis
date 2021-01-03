#include <Winsock2.h>
#include <string.h>
#include <stdio.h>
#define SERVERADD "195.149.206.243"//"94.100.191.203"

int main()
{
	SOCKET socket_fd; //int socket_fd;
	struct sockaddr_in name;
	char buff[1024];
	char buffer[10000];
	size_t num_char;
	struct hostent* host;

	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
 	{
 		printf("WSAStart error %d\n",WSAGetLastError());
 		return -1;
 	}
	host = gethostbyname( "www.mail.ru" );
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	name.sin_family = AF_INET;
	name.sin_port = htons(82);
	//inet_aton("217.69.139.199",&name.sin_addr);
	if (inet_addr("195.149.206.243") != INADDR_NONE)
		name.sin_addr.s_addr = inet_addr("195.149.206.243");
	else
	{
		printf("no such address\n");
		return -2;
	}
 
	if(connect(socket_fd, (struct sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
	{
 		printf("Couldn't connect to server\n");
 		return -1;
 	}
 	sprintf(buffer,"GET /\n");
 	send(socket_fd,	buffer,	strlen(buffer), 0);
 
	while(1)
	{
 		num_char = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
		if (num_char == 0)
		{
			closesocket(socket_fd);
			WSACleanup();
			return 1;
 		}
 		fwrite(buffer, sizeof(char), num_char, stdout);
	}
	closesocket(socket_fd);
 	WSACleanup();
	return 0;
}

