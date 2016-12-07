#pragma once
#include <stdlib.h>
/*
1_new_delete연산자로 수정할 것
2_구조체를 클래스로 전환할 것
*/

#define NAME_LEN		20
#define TEL_LEN			20
#define MAX_PERSON_NUM	100


class Person
{
private:
	char m_szName[NAME_LEN];
	char m_szPhone[TEL_LEN];

public:
	Person(char* szName, char* szPhone);
	Person(void);
	~Person(void);
	char* GetName();
	void SetName(const char* szName);
	char* GetPhone();
	void SetPhone(const char* szPhone);
	void Print();
	bool SameName(char* szName);

	bool operator== (char* szName);
};

void main_person();
void ShowMenu();
void InsertTelInfo(Person** par, int* pnum);
void DeleteTelInfo(Person* par, int* pnum);
void SearchTelInfo(Person* par, int num);
void PrintAll(Person* par, int num);




