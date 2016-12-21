// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define _BUFF_SIZE_ 4096
int PORT = 9000;
char IP[20] = "127.0.0.1"; //Loop Address


void SendMsg(char* msg)
{
	cout << "My    => " << msg << endl;
}
void RecvMsg(char* msg)
{
	cout << "othar => " << msg << endl;
}

void main(int argc, char* argv[])
{
	SOCKADDR_IN clientAddress; //������ ������ �ּ� ������ ������ ����ü.
	SOCKET		clientSocket;	//Ŭ���̾�Ʈ ����
	WSADATA		wsadata;
	char		ch;
	char		buffer[_BUFF_SIZE_];
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
		len = recv(clientSocket,buffer,sizeof(buffer),0); //ó�� ������ ������ �޼����� ��ٸ���.
		buffer[len] = 0;
		RecvMsg(buffer);
		cin.getline(buffer,_BUFF_SIZE_ - 1);		
		send(clientSocket,buffer,strlen(buffer),0);
		SendMsg(buffer);
		if(strcmp(buffer,":quit") == 0)
		{
			cout << "ä���� ���� �մϴ�." << endl;
			break;
		}
	}
	
	closesocket(clientSocket);
	cout << "���α׷��� �����մϴ�.." << endl;
	clientSocket = NULL;
	WSACleanup(); //���� �ʱ�ȭ�� �����Ѵ�.
	system("pause");

}