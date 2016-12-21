#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include <string>
#include "turboc.h"
#include <process.h>
//#include "Util.h"

using namespace std;

#define _GROUND_WITDH_ 80
#define _GROUND_HEIGTH_ 40

CRITICAL_SECTION crit;


bool bExit = false;
class base
{
public:
	clock_t preTime;//  = 0x00;;
	clock_t interval;//  = 1000;
	base(clock_t  per,clock_t interval)
	{
		this->preTime = per;
		this->interval = interval;
	}

};
class Gong : public base
{
	bool m_bStop;
public:
	bool bStart;
	string chName;// = 'A';
	
	bool	bXDirect;// // 진행 방향 
	bool	bYDirect;// // 진행 방향 

	int		x;
	int		y;
	
	bool	bMovehorizon; //vertical 

	Gong(string ch, clock_t pre,clock_t inter,bool dir,int x,int y)
		:base(pre,inter)
	{
		bXDirect = true;
		bYDirect = false;
		chName = ch;	
		this->y = y;
		this->x = x;
		this->bMovehorizon = bMovehorizon;

		m_bStop = false;
		bStart = true;
	}

public:
	void SetPosion(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void Display()
	{
		if(!m_bStop)
		{
			int oldX,oldY;
			oldX = x;
			oldY = y;

			if(x <= 0 || x >= _GROUND_WITDH_) //방향을 전환 시킨다.
			{
				bXDirect = ! bXDirect;
			}

			//if(y <= 0 || y >= _GROUND_HEIGTH_ ) //방향을 전환 시킨다.
			if(y <= 0 ) //방향을 전환 시킨다.
			{
				if(!bStart)
				{
					bYDirect = ! bYDirect;
					bStart = false; 
				}

			}
			bStart = false; //처음 실행 때는 방향을 전환 하지 않는다.


			if(bXDirect)
			{
				++x;
			}
			else
			{
				--x;

			}

			if(bYDirect)
			{
				++y;
			}
			else
			{
				--y;
			}
			EnterCriticalSection(&crit);
			gotoxy(oldX,oldY);
			cout << "  ";

			gotoxy(x,y);
			cout << chName;
			LeaveCriticalSection(&crit);
		}
	}

	void InitGame()
	{
		bXDirect = true;
		bYDirect = false;
		this->y = _GROUND_HEIGTH_;
		this->x = x;
		this->bMovehorizon = bMovehorizon;

		bStart = true;
	}

	void ChangeDirect()
	{
		bYDirect = false;
	}

	bool IsFloor()
	{
		return (y == _GROUND_HEIGTH_);
	}
	bool IsExit()
	{
		return (y > _GROUND_HEIGTH_);
	}

	bool IsStop()
	{
		return m_bStop;
	}
	void Stop()
	{
		m_bStop = true;
	}
};

class DidimDol : public base
{
	int m_nSize; //x 기분으로 갯수.
	int m_x; // X 위치
	int m_y; // y 위치.

public:
	DidimDol(int x, int y, int size,clock_t pre,clock_t inter)
		:base(pre,inter)
	{
		m_x = x; //고정
		m_y = y;
		m_nSize = size;
	}

	bool IsLeftWall()
	{
		if((m_x) <= 0 ) //벽임
		{
			return true;
		}
		return false;
	}
	bool IsRightWall()
	{
		if((m_x + (2* m_nSize)) >= _GROUND_WITDH_ ) //벽임
		{
			return true;
		}
		return false;
	}
	 
	bool IsDidimDol(int x, int y)
	{
		if(y == _GROUND_HEIGTH_)
		{
			if(((m_x) <= x) && x <= (m_x + (m_nSize * 2)))
			{
				return true;
			}
		}
		return false;
	}
	bool Display()
	{
		EnterCriticalSection(&crit);
		gotoxy(m_x,m_y);
		for(int i = 0; i <m_nSize; i++ )
		{
			cout <<"□";
		}
		LeaveCriticalSection(&crit);
		return true;
	}
	bool Remove()
	{
		EnterCriticalSection(&crit);
		gotoxy(m_x,m_y);
		for(int i = 0; i <m_nSize * 2; i++ )
		{
			cout <<"  ";
		}
		LeaveCriticalSection(&crit);
		return true;
	}

	bool MoveLeft()
	{
		if(!IsLeftWall())
		{
			Remove(); //이동 하기 전에 이전 위치값을 지운다.
			m_x--;
		}
		return true;
	}
	bool MoveRight()
	{
		if(!IsRightWall())
		{
			Remove(); //이동 하기 전에 이전 위치값을 지운다.
			m_x++;
		}
		return true;
	}

	bool MoveCenter()
	{
		Remove(); //이동 하기 전에 이전 위치값을 지운다.
		m_x = _GROUND_WITDH_/2;
		return true;
	}
};

#define _SIZE_ 6
Gong gongs[_SIZE_] =
{
	Gong("◎",0x00,50,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_),
	Gong("◎",0x00,85,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_),
	Gong("◎",0x00,20,true,30,_GROUND_HEIGTH_),
	Gong("◎",0x00,50,true,15,_GROUND_HEIGTH_),
	Gong("◎",0x00,85,true,55,_GROUND_HEIGTH_),
	Gong("◎",0x00,90,true,25,_GROUND_HEIGTH_)
};
Gong gong("◎",0x00,100,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_);
DidimDol didimDol(0,_GROUND_HEIGTH_,20,0x00,5);


bool RunGong();
bool RunDidimdol();
bool RunGongEx(Gong* pGong);

unsigned threadID;
HANDLE hThread;


unsigned __stdcall InputKey( void* pArguments );


int nRunningGame;
int bFinishGame;

bool bAppExit = false;
int main()
{
	InitializeCriticalSection(&crit); //동기화 객체를 초기화 한다.

	hThread = (HANDLE)_beginthreadex(NULL, 0, &InputKey, &didimDol, 0, &threadID);

	bFinishGame  = 0;
	system("mode con:cols=100 lines=60");
	setcursortype(NOCURSOR);
	while(true)
	{
		//RunGong();
		//RunDidimdol();
		for(int i = 0 ; i < _SIZE_ ; i++)
		{
			if(!RunGongEx(&gongs[i]))
			{

			}

			if(gongs[i].IsFloor() && !gongs[i].bStart) //공이 바닥에 있으면.
			{
				if(didimDol.IsDidimDol(gongs[i].x,gongs[i].y) && !gongs[i].IsStop()) //바닥에 있으면.
				{
					gongs[i].ChangeDirect();
				}
				else
				{
					if(!gongs[i].IsStop())
					{
						gongs[i].Stop();// = true;
						bFinishGame++;
					}
					
				}
			}
			
		}
		RunDidimdol();

		if(bFinishGame == _SIZE_)
		{
			EnterCriticalSection(&crit);
			gotoxy(2,_GROUND_HEIGTH_ + 2);
			cout << "모든 게임이 종료 되었습니다." << endl;
			cout << "다시 시작하시겠 습니까.";
			LeaveCriticalSection(&crit);

			int ch;
			cin >> ch;
			if(toupper(ch) == 'Y')
			{
				for(int i = 0; i < _SIZE_ ; i++ )
				{
					gongs[i].InitGame();
				}
			}
			else
			{
				bAppExit = true;
			}
		}
		
		if(bExit )
		{
			break;
		}
	}
	DeleteCriticalSection(&crit);

	bExit = true;
	WaitForSingleObject(hThread,5000); //키입력 Thread 가 입력 될때가지 5초만 대기한다. 
	return 0;

}


bool RunGongEx(Gong* pGong)
{
	if(pGong->preTime == 0)
	{
		pGong->preTime = clock();
	}
	clock_t curClock = clock();
	if(curClock - pGong->preTime > pGong->interval)
	{
		pGong->Display();
		pGong->preTime = clock();
	}
	return !pGong->IsExit();
}
bool RunGong()
{
	if(gong.preTime == 0)
	{
		gong.preTime = clock();
	}
	clock_t curClock = clock();
	if(curClock - gong.preTime > gong.interval)
	{
		gong.Display();
		gong.preTime = clock();
	}
	return !gong.IsExit();
}
bool RunDidimdol()
{
	if(didimDol.preTime == 0)
	{
		didimDol.preTime = clock();
	}
	clock_t curClock = clock();
	if(curClock - didimDol.preTime > didimDol.interval)
	{
		didimDol.Display();
		didimDol.preTime = clock();
	}
	return true;
}

//키보드 입력을 받는다.
unsigned __stdcall InputKey( void* pArguments )
{
	DidimDol* pDi = (DidimDol* )pArguments;
	int ch;
	while(!bExit)
	{
		ch = getch();
		//ch = getc(stdin);
		switch(toupper(ch))
		{
		case 'A':
			pDi->MoveLeft();
			break;
		case 'S':
			pDi->MoveCenter();
			break;
		case 'D':
			pDi->MoveRight();
			break;
		}
		Sleep(20);
	}
	return 0;
}
//void RunB()
//{
//	static 
//}