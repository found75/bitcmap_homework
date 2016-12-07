#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(char* szName, char* szPhone)
{
	SetName(szName);
	SetPhone(szPhone);
}

Person::Person(void)
{
}

Person::~Person(void)
{
}

char* Person::GetName()
{
	return m_szName;
}
void Person::SetName(const char* szName)
{
	strcpy(m_szName,szName);
}
char* Person::GetPhone()
{
	return m_szPhone;
}
void Person::SetPhone(const char* szPhone)
{
	strcpy(m_szPhone,szPhone);
}

bool Person::operator== (char* szName)
{
	return (strcmp(this->m_szName,szName) == 0);
}
void Person::Print()
{
	cout << "-----> Name : " << m_szName << "	/	Tel : " << m_szPhone << endl;
}

void main_person()
{
	int choice=0;						// 메뉴선택
	int nPersonNum=0;
	//Person perArr[MAX_PERSON_NUM];		// 전화정보저장배열

	Person* perArr = new Person[100];
	int perNum=0;						// 저장된 인원수

	while(1)
	{
		ShowMenu();

		cout <<"Choose the item : ";
		cin >> choice;

		switch(choice)
		{
		case 1 :
			InsertTelInfo(&perArr, &perNum);
			break;
		case 2 :
			DeleteTelInfo(perArr, &perNum);
			break;
		case 3 :
			SearchTelInfo(perArr, perNum);
			break;
		case 4 :
			PrintAll(perArr, perNum);
			break;
		case 5 :
			return;
			break;
		default :
			printf("illegal selection.. \n");
			break;
		}
	}
}

void ShowMenu()
{
	printf("\n------------- Menu -------------\n");
	printf("	1. Insert \n");
	printf("	2. Delete \n");
	printf("	3. Search \n");
	printf("	4. Print All \n");
	printf("	5. Exit \n");
}

void InsertTelInfo(Person** par, int* pnum)
{
	char name[NAME_LEN];
	char phone[TEL_LEN];
	cout << "[ INSERT ] \n"; 
	cout << "Input Name : ";
	cin >> name;
	cout << "Input Tel Number : ";
	cin >> phone;

	(*par)[*pnum].SetName(name);
	(*par)[*pnum].SetPhone(phone);
	(*pnum)++;

	cout << "-----------> Data Inserted......\n" ;
}

void DeleteTelInfo(Person* par, int* pnum)
{
	int i=0, j=0;
	char name[NAME_LEN];

	cout << "[ Delete ] \n"; 
	cout << "Input Name for Removing : "; 
	cin >> name;
	
	for(i=0;i<*pnum;i++)
	{
		if(par[i] == name)
		{
			for(j=i+1;j<*pnum;j++)
			{
				par[j-1].SetName(par[j].GetName());
				par[j-1].SetPhone(par[j].GetPhone());
			}
			(*pnum)--;
			return;
		}
	}
	cout << "-------------> Data Not Found..........\n"; 
}

void SearchTelInfo(Person* par, int num)
{
	int i=0;
	char name[NAME_LEN];

	cout << "[ Search ] \n";
	cout << "Input Name for Searching : ";
	cin >> name;
	
	for(i=0;i<num;i++)
	{
		if(par[i] == name)
		{
			par[i].Print();
			return;
		}
	}
	cout << "-------------> Data Not Found..........\n"; 
}

void PrintAll(Person* par, int num)
{
	int i=0;
	cout << "[ Print All Data ] \n"; 
	for(i=0;i<num;i++)
	{
		par[i].Print();
	}
}
