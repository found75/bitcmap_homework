// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	SOCKADDR_IN clientAddress; //접속할 서버의 주소 정보를 저장할 구조체.
	SOCKET		clientSocket;	//클라이언트 소켓
	WSADATA		wsadata;
	char		ch;
	char		buffer[_BUFF_SIZE_];
	int			len = 0;

	if(argc == 3)
	{
		strcpy(IP,argv[1]);		// 외부에서 IP , PORT 설정.
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

	//설정된 서버 주소로 접속 요청.
	len = connect(clientSocket,(SOCKADDR*)(&clientAddress),sizeof(clientAddress));

	if(len != 0)
	{
		printf("Connect Error\n");
		return;
	}

	while(true)
	{
		len = recv(clientSocket,buffer,sizeof(buffer),0); //처음 접속후 서버의 메세지를 기다린다.
		buffer[len] = 0;
		RecvMsg(buffer);
		cin.getline(buffer,_BUFF_SIZE_ - 1);		
		send(clientSocket,buffer,strlen(buffer),0);
		SendMsg(buffer);
		if(strcmp(buffer,":quit") == 0)
		{
			cout << "채팅을 종료 합니다." << endl;
			break;
		}
	}
	
	closesocket(clientSocket);
	cout << "프로그램을 종료합니다.." << endl;
	clientSocket = NULL;
	WSACleanup(); //소켓 초기화를 해제한다.
	system("pause");

}