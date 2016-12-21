

// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 ���� Header
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <iostream>
using namespace std;

int PORT = 9000;

#define _BUFF_SIZE_ 4096

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
	SOCKADDR_IN serverAddress; // �ּҸ� ��� ����ü.
	SOCKET		serverSocket;	//������
	SOCKET		clientSocket;	//Accept  ���� ����.
	WSADATA		wsadata;
	char		buffer[_BUFF_SIZE_];
	char		ch;
	int			len = 0;

	if(argc == 2)
	{
		PORT = atoi(argv[1]);
	}

	//������ ���� �Լ��� ��� �ϱ� ���Ͽ� �ʱ�ȭ �Ѵ�.
	//MAKEWORD(2,2) Socket ����. wsadata ???
	if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0) 
	{
		printf("WSAStartUp Error\n");
		return;
	}
	puts("���� �ʱ�ȭ");

	//AF_INET IPV4 �� �ּҸ� �����ڴ�. 
	//SOCK_STREAM TCP ������ ����ϰڴ�.
	serverSocket = socket(AF_INET,SOCK_STREAM,0);	
	puts("���� ����");

	//�ּҼ���. Network �� bigendan �� �����.
	ZeroMemory(&serverAddress,sizeof(serverAddress));	
	serverAddress.sin_addr.s_addr	= htonl(INADDR_ANY);//�ڱ� �ڽ��� �����Ǹ� �Ҵ��Ѵ�.
	serverAddress.sin_family		= AF_INET;			//(internetwork: UDP, TCP, etc.) �������� ����� ������ �����Ѵ�.
	serverAddress.sin_port			= htons(PORT);		//htons �Լ��� u_short�� ȣ��Ʈ���� 
	//TCP/IP ��Ʈ��ũ ����Ʈ ���� (big-endian)�� ��ȯ�մϴ�.

	//���ϰ� �ּ� ������ bind �Ѵ�. 
	if(bind(serverSocket,(SOCKADDR*)&serverAddress,sizeof(serverAddress)) == SOCKET_ERROR) 
	{
		printf("%d Bind error\n",WSAGetLastError());
		return;
	}
	puts("���� �ּ� ���ε�");

	listen(serverSocket,5);  //serverSocket �� ��� �������� ���� �Ѵ�.
	

	int nUser = 0;
	while(true)
	{
		cout << "���� �����...(" << ++nUser <<")��°"  << endl;
		if((clientSocket = accept(serverSocket,NULL,NULL)) == INVALID_SOCKET) //Ŭ���̾�Ʈ ������ ����Ѵ�.
		{
			printf("Accept Error\n");
		}
		sprintf(buffer,"%d ��° ������ ȯ���մϴ�.",nUser);
		SendMsg(buffer);
		send(clientSocket,buffer,strlen(buffer),0);
		while(true)
		{
			memset(buffer,0x00,sizeof(buffer));

			//���� �޼����� ��ٸ���.
			len = recv(clientSocket,buffer,sizeof(buffer),0);

			if(strcmp(buffer,":quit") == 0)
			{
				//���� ä���� ���� �ϰ� ���ο� ä���� ��ٸ���.
				closesocket(clientSocket);
				clientSocket = 0x00;
				break; 
			}
			if(len == 0)
			{
				printf("Ŭ���̾�Ʈ�� ���� �Ǿ� ���� �մϴ�.");
				break;
			}
			buffer[len] = 0;
			RecvMsg(buffer);

			cin.getline(buffer,_BUFF_SIZE_-1);
			send(clientSocket,buffer,strlen(buffer),0);
			SendMsg(buffer);
			//���� ����� ����.
		}

	}
	
	
	system("pause");
	return;
}




