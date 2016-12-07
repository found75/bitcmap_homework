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
	printf("-----> Name : %s	/	Tel : %s \n", m_szName, m_szPhone);
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

		printf("Choose the item : ");
		scanf("%d", &choice);

		/*cout <<"Choose the item : ";
		cin >> choice;*/

		

		switch(choice)
		{
		case 1 :
			InsertTelInfo(perArr, &perNum);
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

void InsertTelInfo(Person* par, int* pnum)
{
	char name[NAME_LEN];
	char phone[TEL_LEN];
	printf("[ INSERT ] \n");
	printf("Input Name : ");
	scanf("%s", name);
	printf("Input Tel Number : ");
	scanf("%s", phone);
	par[*pnum].SetName(name);
	par[*pnum].SetPhone(phone);
	(*pnum)++;

	printf("-----------> Data Inserted......\n");
}

void DeleteTelInfo(Person* par, int* pnum)
{
	int i=0, j=0;
	char name[NAME_LEN];

	printf("[ Delete ] \n");
	printf("Input Name for Removing : ");
	scanf("%s", name);

	for(i=0;i<*pnum;i++)
	{
		if(strcmp(par[i].GetName(), name)==0)
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

	printf("-------------> Data Not Found..........\n");
}

void SearchTelInfo(Person* par, int num)
{
	int i=0;
	char name[NAME_LEN];

	printf("[ Search ] \n");
	printf("Input Name for Searching : ");
	scanf("%s", name);

	for(i=0;i<num;i++)
	{
		if(par[i] == name)
		{
			par[i].Print();
			return;
		}
	}

	printf("-------------> Data Not Found..........\n");
}

void PrintAll(Person* par, int num)
{
	int i=0;

	printf("[ Print All Data ] \n");

	for(i=0;i<num;i++)
	{
		par[i].Print();
	}
	//printf("Name : %s	/	Tel : %s \n", par[i].name, par[i].phone);
}
