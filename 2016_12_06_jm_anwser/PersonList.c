#include "PersonList.h"

#include <stdio.h>
#include <string.h>

/*
1�ܰ�. �����Ҵ����� �����ϼ���
2�ܰ�. ���Ϻ����ϼ���
3�ܰ�. ���� ��ȭ��ȣ�Է� ������ �����ϰ�
�ٽ� ������ �� �ε��Ͽ� �Է� ���¸� �����ϼ���
4�ܰ�. ������ �� XOR��ȣȭ�� �����ϰ�
�ε��� �� XOR��ȣȭ�� �����ϼ���
key�� ������ Ű�� �ּ���
*/


char* _szFileName = "personList.txt";
char _cKey = 'A';
void main_person()
{
	int choice=0;
	Person* prgPresons = (Person*)malloc(sizeof(Person)*MAX_PERSON_NUM);	
	int createPerNum=0;
	int perNum=0;

	while(1)
	{
		ShowMenu();
		printf("Choose the item : ");
		scanf("%d", &choice);

		switch(choice)
		{
		case 1:
			InsertTelInfo(prgPresons, &perNum);
			break;
		case 2:
			DeleteTelInfo(prgPresons, &perNum);
			break;
		case 3:
			SearchTelInfo(prgPresons, perNum);
			break;
		case 4:
			PrintAll(prgPresons, perNum);
			break;
		case 5:
			//free(perArr);
			return;
			break;
		case 6: //����
			//memset(prgPresons,0x00,sizeof(Person)*MAX_PERSON_NUM);
			SaveFile(_szFileName,_cKey,&prgPresons,perNum);			
			break;
		case 7://�ҷ�����.
			perNum = 0;
			memset(prgPresons,0x00,sizeof(Person)*MAX_PERSON_NUM);
			LoadFile(_szFileName,_cKey,&prgPresons,&perNum);
			break;
		default:
			printf("illegal selection...\n");
			break;
		}
	}

	free(prgPresons);
	prgPresons = NULL;
}


void ShowMenu()
{
	printf("\n--------- Menu ---------\n");
	printf("	1. Insert \n");
	printf("	2. Delete \n");
	printf("	3. Search \n");
	printf("	4. Print All \n");
	printf("	5. Exit \n");
	printf("	6. Save \n");
	printf("	7. Load \n");
}

void InsertTelInfo(Person* parr, int* pnum)
{
	char name[NAME_LEN];
	char phone[TEL_LEN];

	printf("[ INSERT ]\n");
	printf("Input Name : ");		scanf("%s", name);
	printf("Input Tel Number : ");	scanf("%s", phone);

	strcpy(parr[*pnum].name, name);
	strcpy(parr[*pnum].phone, phone);
	(*pnum)++;

	printf("-----------> Data Inserted..........\n");
}

void DeleteTelInfo(Person* parr, int* pnum)
{
	int i=0, j=0;
	char name[NAME_LEN];
	printf("[ Delete ]\n");
	printf("Input Name for Removing : "); scanf("%s", name);
	for(i=0;i<*pnum;i++)
	{
		if(strcmp(parr[i].name, name)==0)
		{
			for(j=i+1;j<*pnum;j++)
			{
				strcpy(parr[j-1].name, parr[j].name);
				strcpy(parr[j-1].phone, parr[j].phone);
			}
			(*pnum)--;
			return;
		}
	}

	printf("-------------> Data Not Found............\n");
}

void SearchTelInfo(Person* parr, int num)
{
	int i=0;
	char name[NAME_LEN];

	printf("[ Search ]\n");
	printf("Input Name for Searching : "); scanf("%s", name);

	for(i=0;i<num;i++)
	{
		if(strcmp(parr[i].name, name)==0)
		{
			printf("-----> Name : %s / Tel : %s \n", 
				parr[i].name, parr[i].phone);
			return;
		}
	}

	printf("------------> Data Not Found.............\n");
}

void PrintAll(Person* parr, int num)
{
	int i;
	printf("[ Print All Data ]\n");
	for(i=0;i<num;i++)
		printf("Name : %s / Tel : %s \n", parr[i].name, parr[i].phone);
}

void SaveFile(char* szFile, char cKey,Person** parr,int iSize)
{
	int i = 0 , j = 0;
	FILE* fp = fopen(szFile,"w");
	//char* pbuf =(parr);
	int ch = 0x00;
	for(i = 0; i < iSize * sizeof(Person); i++ )
	{
		ch = (((char*)(*parr))[i])^cKey;
		fputc(ch,fp);
	}
	fclose(fp);
	fp = NULL;
}
void LoadFile(char* szFile, char cKey,Person** parr,int* iSize)
{
	int i = 0;
	FILE* fp = fopen(szFile,"r");
	int ch = 0x00;
	while(feof(fp) == 0)
	{
		ch = fgetc(fp);
		((char*)(*parr))[i] = ch ^ cKey;
		i++;
	}
	(*iSize) = (i+1)/sizeof(Person);
	fclose(fp);
	fp = NULL;
}
