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
	
	bool	bXDirect;// // ���� ���� 
	bool	bYDirect;// // ���� ���� 

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

			if(x <= 0 || x >= _GROUND_WITDH_) //������ ��ȯ ��Ų��.
			{
				bXDirect = ! bXDirect;
			}

			//if(y <= 0 || y >= _GROUND_HEIGTH_ ) //������ ��ȯ ��Ų��.
			if(y <= 0 ) //������ ��ȯ ��Ų��.
			{
				if(!bStart)
				{
					bYDirect = ! bYDirect;
					bStart = false; 
				}

			}
			bStart = false; //ó�� ���� ���� ������ ��ȯ ���� �ʴ´�.


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
	int m_nSize; //x ������� ����.
	int m_x; // X ��ġ
	int m_y; // y ��ġ.

public:
	DidimDol(int x, int y, int size,clock_t pre,clock_t inter)
		:base(pre,inter)
	{
		m_x = x; //����
		m_y = y;
		m_nSize = size;
	}

	bool IsLeftWall()
	{
		if((m_x) <= 0 ) //����
		{
			return true;
		}
		return false;
	}
	bool IsRightWall()
	{
		if((m_x + (2* m_nSize)) >= _GROUND_WITDH_ ) //����
		{
			return true;
		}
		return false;
	}
	 
	bool IsDidimDol(int x, int y)
	{
		if(y == _GROUND_HEIGTH_)
		{
			if(((m_x) <= x) && x <= (m_x + (m_nSize * 2) + 1))
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
			cout <<"��";
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
			Remove(); //�̵� �ϱ� ���� ���� ��ġ���� �����.
			m_x--;
		}
		return true;
	}
	bool MoveRight()
	{
		if(!IsRightWall())
		{
			Remove(); //�̵� �ϱ� ���� ���� ��ġ���� �����.
			m_x++;
		}
		return true;
	}

	bool MoveCenter()
	{
		Remove(); //�̵� �ϱ� ���� ���� ��ġ���� �����.
		m_x = _GROUND_WITDH_/2;
		return true;
	}
};

#define _SIZE_ 6
Gong gongs[_SIZE_] =
{
	Gong("��",0x00,50,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_),
	Gong("��",0x00,85,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_),
	Gong("��",0x00,20,true,30,_GROUND_HEIGTH_),
	Gong("��",0x00,50,true,15,_GROUND_HEIGTH_),
	Gong("��",0x00,85,true,55,_GROUND_HEIGTH_),
	Gong("��",0x00,90,true,25,_GROUND_HEIGTH_)
};
Gong gong("��",0x00,100,true,_GROUND_WITDH_/2,_GROUND_HEIGTH_);
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
	InitializeCriticalSection(&crit); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.

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

			if(gongs[i].IsFloor() && !gongs[i].bStart) //���� �ٴڿ� ������.
			{
				if(didimDol.IsDidimDol(gongs[i].x,gongs[i].y) && !gongs[i].IsStop()) //�ٴڿ� ������.
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
			cout << "��� ������ ���� �Ǿ����ϴ�." << endl;
			cout << "�ٽ� �����Ͻð� ���ϱ�.";
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
	WaitForSingleObject(hThread,5000); //Ű�Է� Thread �� �Է� �ɶ����� 5�ʸ� ����Ѵ�. 
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

//Ű���� �Է��� �޴´�.
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