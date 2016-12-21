#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;


typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
class CUtil
{
private:
	static string format_arg_list(const char *fmt, va_list args);
public:
	static string GetCurTime(const string& str);
	static string GetCurTime();
	static void  GetCurTime(int& y,int& m,int& d);
	static string ToDateFormat(string day);
	static void clrscr();
	static void Gotoxy(int x, int y);
	static int wherex();
	static int wherey();
	static void setcursortype(CURSOR_TYPE c);
	static void delay(int n);
	//string 를 구분자를 통해서 불리 한다.
	static void Tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ");
	static string GetWeek();
	static void textcolor(int color_number = 7);
	
	
	
	//static string GetCurrentTime(int a);
	
	//static string format(const char *fmt, ...)	
	//{
	//	va_list args;
	//	va_start(args, fmt);
	//	std::string s = format_arg_list(fmt, args);
	//	va_end(args);
	//	return s;
	//}

	CUtil(void);
	~CUtil(void);
};
