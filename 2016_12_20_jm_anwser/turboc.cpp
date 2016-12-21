
#include "turboc.h"

// ȭ���� ��� �����.
void clrscr()
{
	system("cls");
}

// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X=x+1;
	Cur.Y=y+1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

// Ŀ���� x ��ǥ�� �����Ѵ�.
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}


void NextEvnet(int cls)
{

	int ch = 0;
	while(1)
	{
		if(cls)
		{
			clrscr();
		}
		
		printf("\t���� �۾����� ���� �Ͻðڽ��ϰ� ? (Y) \n");
		ch = getchar();
		if(toupper(ch) == 'Y')
		{
			break;
		}
	}
}