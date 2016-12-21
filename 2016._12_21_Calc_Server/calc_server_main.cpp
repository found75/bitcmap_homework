

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

//��ſ� ����� ���. (
struct _Header
{
	char calc; //A
	int	 count;
};

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
	char		tmpbuffer[_BUFF_SIZE_];
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

	_Header header;

	int offset = 0;
	int nUser = 0;
	while(true)
	{
		cout << "���� �����Դϴ�....(" << ++nUser <<")��°"  << endl;
		if((clientSocket = accept(serverSocket,NULL,NULL)) == INVALID_SOCKET) //Ŭ���̾�Ʈ ������ ����Ѵ�.
		{
			printf("Accept Error\n");
		}

		while(true)
		{
			offset = 0;
			memset(buffer,0x00,sizeof(buffer));
			memset(tmpbuffer,0x00,sizeof(tmpbuffer));

			sprintf(tmpbuffer,"������ �Է��ϼ���. (+,-,*,/ ",nUser);
			header.calc = 'A'; //���� �Է�
			header.count = strlen(tmpbuffer);
			
			memcpy(buffer,&header,sizeof(header));
			offset += sizeof(header); //Heade ������ ������´�.
			memcpy(buffer + offset,tmpbuffer,sizeof(header.count));
			offset += header.count;

			send(clientSocket,buffer,offset,0);
			//���� �޼����� ��ٸ���.
			len = recv(clientSocket,buffer,sizeof(buffer),0);
			if(len == -1)
			{
				cout << "Ŭ���̾�Ʈ�� ������ ���� �Ǿ����ϴ�." << endl;
				//���� ä���� ���� �ϰ� ���ο� ä���� ��ٸ���.
				closesocket(clientSocket);
				clientSocket = 0x00;	
				break;
			}
			
			offset = 0;
			memcpy(&header,buffer + offset,sizeof(header));
			offset += sizeof(header);
			int* pRgDigit = new int[header.count];

			memcpy(pRgDigit,buffer + offset,sizeof(int)* header.count);

			int val = 0;
			val = pRgDigit[0];
			for(int i = 1 ;i < header.count ; i++)
			{
				switch(header.calc)
				{
				case '+':
					val += pRgDigit[i];
					break;
				case '-':
					val -= pRgDigit[i];
					break;
				case '*':
					val *= pRgDigit[i];
					break;
				case '/':
					val /= pRgDigit[i];
					break;
				case 'Q':
				case '1':
					//���� ä���� ���� �ϰ� ���ο� ä���� ��ٸ���.
					closesocket(clientSocket);
					clientSocket = 0x00;					
					break;

				}
			}
			if(clientSocket == 0x00)
			{
				//���� ������ ��ٸ���.
				break;
			}

			for(int i = 0 ; i < header.count ;i++)
			{
				if(i != (header.count  - 1))
				{
					cout << pRgDigit[i] <<" "<< header.calc << " ";
				}
				else
				{
					cout << pRgDigit[i] << " = " ;
				}
			}
			cout << val << endl;
			offset = 0;
			sprintf(tmpbuffer,"����� %d �Դϴ�." , val);
			header.calc = 'M';
			header.count = strlen(tmpbuffer);
			memcpy(buffer + offset,&header,sizeof(header));
			offset += sizeof(header);
			memcpy(buffer + offset,tmpbuffer,header.count);
			offset += header.count;
			send(clientSocket,buffer,offset,0);
		}

	}


	system("pause");
	return;
}
