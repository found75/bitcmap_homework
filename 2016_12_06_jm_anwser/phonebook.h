#pragma once


typedef unsigned int   size_t;

//1. 주소록 포맷을 설계하고 사용자 입력을 받아서
//   추가, 수정, 삭제 해보세요
//   이름(20)나이(3)취미(20)주소(100)
//   홍길동        024활빈       	금강산
//   임꺽정        033파워        	구월산
//   장길산        036광대        	장산곶
//   일지매        021코스프레       서울종로
//   차돌바위      015도끼질        	충청도보령

struct _user
{
	char szName[30];
	int	 iAge;
	char szHobby[30];
	char szAddr[100];
	short iDelete; //삭제여부를 나타낸다.
	char   r;
	char   n;
};
typedef struct _user User;


User CreateUser();
//사용자를 지정된 위치에 추가 한다.
int MakeUser(User* pUser);
//사용자 정보를 검색해서 . (파일 위치를 반환 한다.)
int SearchUser(User* pUser,size_t* pSize);
int AddUser(User* pUser);
int InsertUser(User* pUser,size_t pos);
//int ChgNode(User* pUser); //전화번호부를 추가 한다.
int DeletrUser(User* pUser,size_t pos);
//파일에 있는 내용을 표시한다.
int DisplayFile(char* szFileName);
void main_phone();
