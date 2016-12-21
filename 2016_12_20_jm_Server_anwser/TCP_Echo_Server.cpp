// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include "stdafx.h"
#include <WinSock2.h> //Winsock 2 ���� Header
#include <windows.h>
#include <stdio.h>
#include "Util.h"
#include <string>
#include <vector>

int PORT = 8000;

int baseBall[3] = {0,0,0};

//�߱� ���� ���� �Ѵ�.
bool MakeBaseBall();

int CountBall(int* source,int* input)
{
	int cnt = 0;
	for(int i = 0 ; i < 3; i++)
	{
		for(int k = 0 ; k < 3 ; k++)
		{
			if(*(source + i) == *(input + k) && i != k )
			{
				cnt++;
			}
		}
	}
	return cnt;
}

int CountStrike(int* source,int* input)
{
	int cnt = 0;
	for(int i = 0 ; i < 3; i++)
	{
		if(*(source + i) == *(input + i))
		{
			cnt++;
		}
	}
	return cnt;
}
void main(int argc, char* argv[])
{
	SOCKADDR_IN serverAddress; // �ּҸ� ��� ����ü.
	SOCKET		serverSocket;	//������
	SOCKET		clientSocket;	//Accept  ���� ����.
	WSADATA		wsadata;
	char		buffer[4096];
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
	puts("���� listen (������)");

	
	if((clientSocket = accept(serverSocket,NULL,NULL)) == INVALID_SOCKET) //Ŭ���̾�Ʈ ������ ����Ѵ�.
	{
		printf("Accept Error\n");
	}

	MakeBaseBall();
	printf("�߱� ������ �����Ͽ����ϴ�. (%d , %d ,%d)" ,baseBall[0],baseBall[1],baseBall[2]); 
	puts("���� ����");

	int n[3] = {0};
	strcpy(buffer,"Server => �߱����� �Դϴ�. �Դϴ�. ��ȣ�� �ҷ� �ּ��� - <ex> 4,5,3");
	send(clientSocket,buffer,strlen(buffer),0);
	while(true)
	{
		memset(buffer,0x00,sizeof(buffer));
		
		len = recv(clientSocket,buffer,sizeof(buffer),0);
		if(len == 0)
		{
			printf("Ŭ���̾�Ʈ�� ���� �Ǿ� ���� �մϴ�.");
			break;
		}
		buffer[len] = 0;

		printf("data ===> %s\n",buffer);
		string retstr(buffer);
		vector<string> vec;
		CUtil::Tokenize(retstr,vec,",");

		if(vec.size() == 3)
		{
			n[0] = atoi(vec[0].c_str());
			n[1]= atoi(vec[1].c_str());
			n[2] = atoi(vec[2].c_str());

			int s = CountStrike(baseBall,n);
			int b = CountBall(baseBall,n);
			//����...

			if(s == 3)
			{
				sprintf(buffer,"OUT");
			}
			else
			{
				sprintf(buffer," %d ball %d strike",b,s);
			}
			send(clientSocket,buffer,strlen(buffer),0);
		}
		//else
		//{
		//	sprintf(buffer,"�Է� ������ ���� �ʽ��ϴ�.",1,2);
		//}
		
	}
	
	

	
	
	closesocket(clientSocket);

	system("pause");
	return;
}


//�߱� ���� ���� �Ѵ�.
bool MakeBaseBall()
{
	int nDigit = 0;
	srand( (unsigned)time( NULL ) );
	while(nDigit < 3)
	{
		if(nDigit == 0)
		{
			baseBall[nDigit++] = rand()%10 ;
		}
		else if(nDigit == 1)
		{
			baseBall[nDigit] = rand()%10 ;
			if(baseBall[0] !=  baseBall[nDigit])
			{
				nDigit++;
			}
		}
		else if(nDigit == 2)
		{
			baseBall[nDigit] = rand()%10 ;

			if(baseBall[0] != baseBall[nDigit] 
			&& baseBall[1] != baseBall[nDigit])
			{
				nDigit++;
			}
		}
	}
	return true;

}


