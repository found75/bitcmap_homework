// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include "stdafx.h"
#include <WinSock2.h> //Winsock 2 버전 Header
#include <windows.h>
#include <stdio.h>
#include "Util.h"
#include <string>
#include <vector>

int PORT = 8000;

int baseBall[3] = {0,0,0};

//야구 값을 생성 한다.
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
	SOCKADDR_IN serverAddress; // 주소를 담는 구제체.
	SOCKET		serverSocket;	//대기소켓
	SOCKET		clientSocket;	//Accept  받은 소켓.
	WSADATA		wsadata;
	char		buffer[4096];
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
	puts("소켓 listen (대기상태)");

	
	if((clientSocket = accept(serverSocket,NULL,NULL)) == INVALID_SOCKET) //클라이언트 접속을 대기한다.
	{
		printf("Accept Error\n");
	}

	MakeBaseBall();
	printf("야구 게임을 생성하였습니다. (%d , %d ,%d)" ,baseBall[0],baseBall[1],baseBall[2]); 
	puts("소켓 연결");

	int n[3] = {0};
	strcpy(buffer,"Server => 야구게임 입니다. 입니다. 번호를 불러 주세요 - <ex> 4,5,3");
	send(clientSocket,buffer,strlen(buffer),0);
	while(true)
	{
		memset(buffer,0x00,sizeof(buffer));
		
		len = recv(clientSocket,buffer,sizeof(buffer),0);
		if(len == 0)
		{
			printf("클라이언트가 종료 되어 종료 합니다.");
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
			//판정...

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
		//	sprintf(buffer,"입력 형식이 맞지 않습니다.",1,2);
		//}
		
	}
	
	

	
	
	closesocket(clientSocket);

	system("pause");
	return;
}


//야구 값을 생성 한다.
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


