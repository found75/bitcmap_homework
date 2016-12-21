
#include <Windows.h>
#include <iostream>
#include <process.h>
#include "Util.h"
using namespace std;

//�����                           �ǹ�  
//	THREAD_PRIORITY_TIME_CRITICAL   ���� ���� �켱 �������� �� ���� �켱 ����  
//	THREAD_PRIORITY_HIGHEST         ���� ���� �켱 ����  
//	THREAD_PRIORITY_ABOVE_NORMAL    ���� ���� ���� ���� �켱 ����  
//	THREAD_PRIORITY_NORMAL          ����  
//	THREAD_PRIORITY_BELOW_NORMAL    ���� ���� ���� ���� �켱 ����  
//	THREAD_PRIORITY_LOWEST          ���� ���� �켱 ����  
//	THREAD_PRIORITY_IDLE            ���� ���� �켱 �������� �� ���� �켱 ����  
//BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority);  
//int WINAPI GetThreadPriority(HANDLE hThread);  


//L
#define _COUNT_ 12
//#define _COUNT_ 2

struct thData
{
	
	int  x;
	int  y;
	char ch;
	//LPTHREAD_START_ROUTINE fun;
	unsigned threadID;
	bool bWinner;
	HANDLE hStop;
	HANDLE hThread;
};

int cnt=0;
CRITICAL_SECTION crit;


#define _FINISH_LINE_ 100
thData data[_COUNT_];

HANDLE rghThreads[_COUNT_];
HANDLE rghExit[_COUNT_];

char chWinner = 0x00;
bool bThexit = false;
void DrawGround()
{
	for(int i = 0; i < _COUNT_ ; i++)
	{
		CUtil::Gotoxy(_FINISH_LINE_,i);
		cout << "��";
	}
}

int Rand()
{
	srand( (unsigned)time( NULL ) );
	return  rand()%10 * 100;
}

unsigned __stdcall MyThreadFunction( void* pArguments )
{
	thData* pData = (thData*)pArguments;
	if(pData != NULL)
	{
		while(!bThexit)
		{
			EnterCriticalSection(&crit);
			int sleep = Rand();
			LeaveCriticalSection(&crit);
			//Sleep(200);
			
			Sleep(sleep);
			EnterCriticalSection(&crit);
			CUtil::Gotoxy((pData->x - 1),pData->y);
			cout << " ";
			CUtil::Gotoxy(pData->x++,pData->y);
			cout << pData->ch;
			
			if(pData->x == _FINISH_LINE_)
			{
				if(chWinner == 0x00)
				{
					chWinner = pData->ch;
					bThexit = true;
				}
			}
			LeaveCriticalSection(&crit);
		}
	}
	EnterCriticalSection(&crit);
	cout << "thread �� ���� �Ǿ����ϴ�." << pData->ch << endl;
	LeaveCriticalSection(&crit);	
	
	if(pData != NULL)
	{
		SetEvent(pData->hStop);
	}
	_endthreadex(0);
	
	return 0;
}

void InitThreadData()
{
	for(int i = 0 ; i < _COUNT_ ; i++)
	{
		data[i].ch = (char)('A' + i);
		data[i].x = 0;
		data[i].y = i;
	}
}

int main() 
{
	
	InitializeCriticalSection(&crit); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
	DrawGround();
	InitThreadData();
	
	for(int i = 0 ;i <_COUNT_; i++ )
	{	
		data[i].hStop = rghExit[i] = CreateEvent(NULL,true,false,NULL);
		data[i].hThread = rghThreads[i] = (HANDLE)_beginthreadex(NULL, 0, &MyThreadFunction, &data[i], 0, &(data[i].threadID) );
		
		switch(i%3)
		{
		case 0:
			SetThreadPriority(data[i].hThread,THREAD_PRIORITY_IDLE);
			break;
		case 1:
			SetThreadPriority(data[i].hThread,THREAD_PRIORITY_HIGHEST);
			break;
		case 2:
			SetThreadPriority(data[i].hThread,THREAD_PRIORITY_NORMAL);
			break;
		}
		
	}

	WaitForMultipleObjectsEx(_COUNT_,rghExit,true,INFINITE,false);

	EnterCriticalSection(&crit);
	cout << "thread �� ��� ���� �Ǿ����ϴ�." << endl;
	LeaveCriticalSection(&crit);

	DeleteCriticalSection(&crit);

	for(int i = 0;  i <_COUNT_ ; i++)
	{
		CloseHandle(rghExit[i]);
	}
	system("cls");
	cout << endl << endl;
	cout << "Winner  " << chWinner << endl;

	getchar();
	return 0;
}
