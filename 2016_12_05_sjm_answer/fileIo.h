#ifndef _FILEIO_H_
#define _FILEIO_H_

#define _NODE_MAX_CNT_ 100
#define _BUFF_SIZE_ 1024

#define _NAME_ 20
#define _AGE_ 4
#define _HOBBY_ 20
#define _ADDR_ 200

struct _user
{
	char szName[_NAME_];
	char szAge[_AGE_];
	char szHobby[_HOBBY_];
	char szAddr[_ADDR_]; 
	int  bDel; //삭제 여부
};


typedef struct _user User;


/*
1. mystory.txt파일을 생성해서  이름, 나이, 전화번호를 저장하세요 저장의 형태는
# 이름 : 홍길동
# 나이 : 24
# 전화번호 : 010-1111-2222
*/
int HomeWork01();

/*
2. 1번파일에 데이터를 추가하세요.
# 즐겨먹는 음식 : 짬뽕, 탕수육
# 취미 : 축구
*/
int HomeWork02();

//3. 2번을 완료한 후 파일을 읽고 출력하세요.
int HomeWork03(char* szFileName);

//4. 주소록 포맷을 설계하고 사용자 입력을 받아서
//  추가, 수정, 삭제 해보세요
//	이름,나이,취미,주소
//	ex)
//	홍길동,024,활빈,금강산
//	임꺽정,033,파워,구월산
//	장길산,036,광대,장산곶
//	일지매,021,코스프레,서울종로
int HomeWork04();
int _readUsers();
int _writeUsers();

User bufferTOUser(char* buffer);

int fileIo_Main();

extern User rgTUsers[_NODE_MAX_CNT_];
extern char buffer[_BUFF_SIZE_];
//데이터가 입력 되었있는 위치 까지의 노드숫자. 삭제된 노드 포함.
extern int iUserCnt; 

#endif


