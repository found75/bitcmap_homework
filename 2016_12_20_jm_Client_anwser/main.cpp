// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>

int PORT = 8000;
//char IP[20] = "192.168.0.117"; //Loop Address
char IP[20] = "127.0.0.1"; //Loop Address

void main(int argc, char* argv[])
{
	SOCKADDR_IN clientAddress; //������ ������ �ּ� ������ ������ ����ü.
	SOCKET		clientSocket;	//Ŭ���̾�Ʈ ����
	WSADATA		wsadata;
	char		ch;
	char		buffer[4096];
	int			len = 0;

	if(argc == 3)
	{
		strcpy(IP,argv[1]);		// �ܺο��� IP , PORT ����.
		PORT = atoi(argv[2]);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
	{
		printf("WSAStartUp Error\n");
		return;
	}

	clientSocket = socket(AF_INET,SOCK_STREAM,0); //AF_INET(IPV4), SOCK_STREAM(TCP)
	ZeroMemory(&clientAddress,sizeof(clientAddress));
	clientAddress.sin_port = htons(PORT);
	//clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddress.sin_addr.s_addr = inet_addr(IP);
	clientAddress.sin_family = AF_INET;

	//������ ���� �ּҷ� ���� ��û.
	len = connect(clientSocket,(SOCKADDR*)(&clientAddress),sizeof(clientAddress));

	if(len != 0)
	{
		printf("Connect Error\n");
		return;
	}

	while(true)
	{
		len = recv(clientSocket,buffer,sizeof(buffer),0);
		buffer[len] = 0;
		printf("%s\n",buffer);

		if(strcmp(buffer,"OUT") == 0)
		{
			break;
		}

		fgets(buffer,sizeof(buffer),stdin);
		send(clientSocket,buffer,strlen(buffer),0);
	}
	//len = recv(clientSocket,buffer,sizeof(buffer),0);
	//buffer[len] = 0;
	printf("data ===> %s\n",buffer);
	closesocket(clientSocket);
	WSACleanup(); //���� �ʱ�ȭ�� �����Ѵ�.
	system("pause");

}