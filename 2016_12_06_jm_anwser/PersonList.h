#pragma once

/*
1단계. 동적할당으로 수정하세요
2단계. 파일분할하세요
3단계. 현재 전화번호입력 내역을 저장하고
다시 시작할 때 로딩하여 입력 상태를 유지하세요
4단계. 저장할 때 XOR암호화를 적용하고
로딩할 때 XOR암호화를 해제하세요
key는 임의의 키를 주세요
*/

#define NAME_LEN		20
#define TEL_LEN			20
#define MAX_PERSON_NUM	100


#pragma pack(push,1)
typedef struct _Person
{
	char name[NAME_LEN];
	char phone[TEL_LEN];

} Person;


void ShowMenu();
void InsertTelInfo(Person* parr, int* pnum);
void PrintAll(Person* parr, int num);
void DeleteTelInfo(Person* parr, int* pnum);
void SearchTelInfo(Person* parr, int num);

void SaveFile(char* szFileName, char cKey,Person** parr,int iSize);
void LoadFile(char* szFileName, char cKey,Person** parr,int* iSize);

void main_person();