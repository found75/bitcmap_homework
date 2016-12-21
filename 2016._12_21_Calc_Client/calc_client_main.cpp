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

//��ſ� ����� ���. (
struct _Header
{
	char calc;
	int	 count;
};


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
	char		recvBuffer[_BUFF_SIZE_];
	char		buffer[_BUFF_SIZE_];
	int			iBuffer[100];
	
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

	memset(&recvBuffer,0x00,sizeof(recvBuffer));
	//len = recv(clientSocket,recvBuffer,sizeof(buffer),0); //ó�� ������ ������ �޼����� ��ٸ���.
	//recvBuffer[len] = 0x00; 
	//cout << recvBuffer; 

	_Header header;
	int offset = 0;
	while(true)
	{
		memset(&header,0x00,sizeof(_Header));
		memset(&recvBuffer,0x00,sizeof(recvBuffer));
		memset(&buffer,0x00,sizeof(buffer));

		len = recv(clientSocket,recvBuffer,sizeof(recvBuffer),0); //ó�� ������ ������ �޼����� ��ٸ���.
		memcpy(&header,recvBuffer,sizeof(_Header));

		switch(header.calc)
		{
		case 'M': // ���.
			offset = sizeof(_Header);
			memcpy(buffer,(recvBuffer + offset ),header.count);
			buffer[header.count] = 0x00;
			cout << buffer << endl;
			break;
		case 'A': //���� �Է� .
			offset += sizeof(_Header);
			memcpy(buffer,(recvBuffer + offset ),header.count);
			buffer[header.count] = 0x00;
			cout << buffer;
			int count = 0;
			memset(&header,0x00,sizeof(header));
			while(true)
			{
				if(count == 0)
				{
					cout << "�����ڸ� �Է��ϼ���." << endl;
					cin.getline(buffer,sizeof(buffer));
					fflush(stdin);
					header.calc = buffer[0];
				}
				else
				{
					cout << "���ڸ� �Է� �ϼ���. �Է�����(999999)" << endl ;
					cin >> iBuffer[count - 1];
					fflush(stdin);
					if(iBuffer[count - 1] == 999999)
					{
						break;
					}
				}
				count++;
			}

			offset = 0;
			header.count = (count - 1);

			memset(recvBuffer,0x00,sizeof(recvBuffer));
			memcpy(recvBuffer,&header,sizeof(header));
			offset += sizeof(header);
			memcpy(recvBuffer + offset,iBuffer,sizeof(int) * count);
			offset += (sizeof(int) * count);
			send(clientSocket,recvBuffer,offset,0);
			break;
		}
	}

	closesocket(clientSocket);
	cout << "���α׷��� �����մϴ�.." << endl;
	clientSocket = NULL;
	WSACleanup(); //���� �ʱ�ȭ�� �����Ѵ�.
	system("pause");

}