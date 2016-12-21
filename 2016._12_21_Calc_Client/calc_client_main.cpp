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

//통신에 사용할 헤더. (
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
	SOCKADDR_IN clientAddress; //접속할 서버의 주소 정보를 저장할 구조체.
	SOCKET		clientSocket;	//클라이언트 소켓
	WSADATA		wsadata;
	char		ch;
	char		recvBuffer[_BUFF_SIZE_];
	char		buffer[_BUFF_SIZE_];
	int			iBuffer[100];
	
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

	memset(&recvBuffer,0x00,sizeof(recvBuffer));
	//len = recv(clientSocket,recvBuffer,sizeof(buffer),0); //처음 접속후 서버의 메세지를 기다린다.
	//recvBuffer[len] = 0x00; 
	//cout << recvBuffer; 

	_Header header;
	int offset = 0;
	while(true)
	{
		memset(&header,0x00,sizeof(_Header));
		memset(&recvBuffer,0x00,sizeof(recvBuffer));
		memset(&buffer,0x00,sizeof(buffer));

		len = recv(clientSocket,recvBuffer,sizeof(recvBuffer),0); //처음 접속후 서버의 메세지를 기다린다.
		memcpy(&header,recvBuffer,sizeof(_Header));

		switch(header.calc)
		{
		case 'M': // 결과.
			offset = sizeof(_Header);
			memcpy(buffer,(recvBuffer + offset ),header.count);
			buffer[header.count] = 0x00;
			cout << buffer << endl;
			break;
		case 'A': //계산식 입력 .
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
					cout << "연산자를 입력하세요." << endl;
					cin.getline(buffer,sizeof(buffer));
					fflush(stdin);
					header.calc = buffer[0];
				}
				else
				{
					cout << "숫자를 입력 하세요. 입력종료(999999)" << endl ;
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
	cout << "프로그램을 종료합니다.." << endl;
	clientSocket = NULL;
	WSACleanup(); //소켓 초기화를 해제한다.
	system("pause");

}