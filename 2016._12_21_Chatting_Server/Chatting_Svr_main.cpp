

// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 버전 Header
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
	SOCKADDR_IN serverAddress; // 주소를 담는 구제체.
	SOCKET		serverSocket;	//대기소켓
	SOCKET		clientSocket;	//Accept  받은 소켓.
	WSADATA		wsadata;
	char		buffer[_BUFF_SIZE_];
	char		ch;
	int			len = 0;

	if(argc == 2)
	{
		PORT = atoi(argv[1]);
	}

	//윈도우 소켓 함수를 사용 하기 위하요 초기화 한다.
	//MAKEWORD(2,2) Socket 버전. wsadata ???
	if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0) 
	{
		printf("WSAStartUp Error\n");
		return;
	}
	puts("윈속 초기화");

	//AF_INET IPV4 의 주소를 가지겠다. 
	//SOCK_STREAM TCP 소켓을 사용하겠다.
	serverSocket = socket(AF_INET,SOCK_STREAM,0);	
	puts("소켓 생성");

	//주소설정. Network 는 bigendan 에 맞춘다.
	ZeroMemory(&serverAddress,sizeof(serverAddress));	
	serverAddress.sin_addr.s_addr	= htonl(INADDR_ANY);//자기 자신의 아이피를 할당한다.
	serverAddress.sin_family		= AF_INET;			//(internetwork: UDP, TCP, etc.) 영역에서 사용할 소켓을 생성한다.
	serverAddress.sin_port			= htons(PORT);		//htons 함수는 u_short를 호스트에서 
	//TCP/IP 네트워크 바이트 순서 (big-endian)로 변환합니다.

	//소켓과 주소 정보를 bind 한다. 
	if(bind(serverSocket,(SOCKADDR*)&serverAddress,sizeof(serverAddress)) == SOCKET_ERROR) 
	{
		printf("%d Bind error\n",WSAGetLastError());
		return;
	}
	puts("소켓 주소 바인딩");

	listen(serverSocket,5);  //serverSocket 을 대기 소켓으로 설정 한다.
	

	int nUser = 0;
	while(true)
	{
		cout << "접속 대기중...(" << ++nUser <<")번째"  << endl;
		if((clientSocket = accept(serverSocket,NULL,NULL)) == INVALID_SOCKET) //클라이언트 접속을 대기한다.
		{
			printf("Accept Error\n");
		}
		sprintf(buffer,"%d 번째 접속을 환영합니다.",nUser);
		SendMsg(buffer);
		send(clientSocket,buffer,strlen(buffer),0);
		while(true)
		{
			memset(buffer,0x00,sizeof(buffer));

			//다음 메세지를 기다린다.
			len = recv(clientSocket,buffer,sizeof(buffer),0);

			if(strcmp(buffer,":quit") == 0)
			{
				//현재 채팅을 종료 하고 새로운 채팅을 기다리다.
				closesocket(clientSocket);
				clientSocket = 0x00;
				break; 
			}
			if(len == 0)
			{
				printf("클라이언트가 종료 되어 종료 합니다.");
				break;
			}
			buffer[len] = 0;
			RecvMsg(buffer);

			cin.getline(buffer,_BUFF_SIZE_-1);
			send(clientSocket,buffer,strlen(buffer),0);
			SendMsg(buffer);
			//종료 기능은 없음.
		}

	}
	
	
	system("pause");
	return;
}




