#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

CUtil::CUtil(void)
{
}


CUtil::~CUtil(void)
{

}


//#include "turboc.h"

// ȭ���� ��� �����.
void CUtil::clrscr()
{
	system("cls");
}

void CUtil::Gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X= x;
	Cur.Y= y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

void CUtil::Tokenize(const string& str,vector<string>& tokens,const string& delimiters)
{
	// �� ù ���ڰ� �������� ��� ����
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// �����ڰ� �ƴ� ù ���ڸ� ã�´�
	string::size_type pos     = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{		
		tokens.push_back(str.substr(lastPos, pos - lastPos)); // token�� ã������ vector�� �߰��Ѵ�
		lastPos = str.find_first_not_of(delimiters, pos); // �����ڸ� �پ�Ѵ´�.  "not_of"�� �����϶�
		pos = str.find_first_of(delimiters, lastPos); // ���� �����ڰ� �ƴ� ���ڸ� ã�´�
	}
}

// Ŀ���� x ��ǥ�� �����Ѵ�.
int CUtil::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int CUtil::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
void CUtil::setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case CURSOR_TYPE(NOCURSOR):
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case CURSOR_TYPE(SOLIDCURSOR):
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case CURSOR_TYPE(NORMALCURSOR):
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

string CUtil::GetCurTime(const string& str)
{
	char s[255] = {0};
	struct tm *t;
	time_t timer;
	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	
	string test;
	if(str == string("YYYYMMDD"))
	{
		sprintf(s, "%04d-%02d-%02d",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	}
	else if(str == string("YYYYMMDDHHMM"))
	{
		sprintf(s, "%04d-%02d-%02d %02d:%02d"
				,t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,t->tm_hour, t->tm_min);
	}
	else if(str == string("YYYYMMDDHHMMSS"))
	{
		sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec
			);
	}	
	return string(s);
}
string CUtil::GetCurTime()
{
	char s[255] = {0};
	struct tm *t;
	time_t timer;
	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	string test;
	sprintf(s, "%04d%02d%02d%02d%02d%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
		);	
	return string(s);
}
void CUtil::GetCurTime(int& y,int& m,int& d)
{
	char s[255] = {0};
	struct tm *t;
	time_t timer;
	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	y = t->tm_year;
	m = t->tm_mon;
	d = t->tm_mday;
	m  += 1;
	y +=1900;

}

string CUtil::ToDateFormat(string day)
{
	string yyyy,mm,dd,hh,mi,ss;
	if(day.size() == 8)
	{
		yyyy = day.substr(0,4);
		mm = day.substr(4,2);
		dd = day.substr(6,2);
	}
	else if(day.size()  == 12)
	{
		yyyy = day.substr(0,4);
		mm = day.substr(4,2);
		dd = day.substr(6,2);
		hh = day.substr(8,2);
		mi = day.substr(10,2);
		ss = day.substr(12,2);
	}
	else
	{
		return day;
	}
	string str = yyyy+"-"+mm+"-"+dd+" "+hh+":"+mm+":"+ss;
	return str;
}

string CUtil::GetWeek()
{
	string week[] = { "��", "��", "ȭ", "��", "��", "��", "��" };
	struct tm *t;
	time_t timer;
	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	return week[t->tm_wday];
}


#pragma warning(disable:4996)
string CUtil::format_arg_list(const char *fmt, va_list args)
{
	if (!fmt) return "";
	int   result = -1, length = 256;
	char *buffer = 0;
	while (result == -1)
	{
		if (buffer) delete [] buffer;
		buffer = new char [length + 1];
		memset(buffer, 0, length + 1);
		result = _vsnprintf(buffer, length, fmt, args);
		length *= 2;
	}
	std::string s(buffer);
	delete [] buffer;
	return s;
}

void CUtil::textcolor(int color_number)
{
	/*
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
	*/
}