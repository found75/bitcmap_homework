#include "phonebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//전화 번호부이름.
char* szFileName = "ploneList.bin";

void main_phone()
{
	char ch = 0x00;
	char szBuffer[1024] = {0};
	int  iBuffer = 0x00;
	size_t posFile = 0;
	User tBuffUser = CreateUser();

	while(ch != 'q')
	{
		printf("메뉴를 선택 하세요.\n");
		printf("추가('1'),수정('2'),삭제('3') ,파일내용표시.('4'),종료('q') \n");
		ch = getch();
		switch(ch)
		{
		case '1':
			tBuffUser = CreateUser();
			MakeUser(&tBuffUser);	
			AddUser(&tBuffUser);			
			break;
		case '2': //수정.. 
			tBuffUser = CreateUser();
			printf("검색할 이름을  입력 하세요.\n");
			scanf("%s",tBuffUser.szName);
			if(SearchUser(&tBuffUser,&posFile) == 1)
			{
				User newUser = CreateUser();
				printf("수정할 내용을 입력하세요. \n");
				MakeUser(&newUser);
				InsertUser(&newUser,posFile); //지정된 위치에 추가한다.
			}
			else
			{
				printf("일치하는 이름이 없습니다.\n");
			}
			break;
		case '3': //삭제.
			tBuffUser = CreateUser();
			printf("삭제할 이름을 입력하세요 .\n");
			scanf("%s",tBuffUser.szName);
			if(SearchUser(&tBuffUser,&posFile) == 1)
			{
				tBuffUser.iDelete = 1;
				InsertUser(&tBuffUser,posFile); //지정된 위치에 추가한다.
			}
			else
			{
				printf("일치하는 이름이 없습니다.\n");
			}
			break;
		case '4': //Display 파일에 있는 내용을 표시한다.
			DisplayFile(szFileName);
			break;
		case 'q': //종료.
			break;

		}
		
	}
}



//새로운 유저를 생성 한다.
int MakeUser(User* pUser)
{
	printf("이름: "); scanf("%s",pUser->szName);
	printf("나이: "); scanf("%d",&(pUser->iAge));
	printf("취미: "); scanf("%s",pUser->szHobby);
	printf("주소: "); scanf("%s",pUser->szAddr); 
	return 1;
}

User CreateUser()
{
	User user = {"",0,"","",0,'\r','\n'};
	return user;
}
//사용자 정보를 검색해서 . (파일 위치를 반환 한다.)
int SearchUser(User* pUser,size_t* pSize)
{
	int bSearch = 0;
	size_t pos = 0;
	User user = {0};
	//파일이 없으면 생성 해도 상관 없음.
	FILE* fp = fopen(szFileName,"r");
	while(feof(fp) == 0)
	{
		fread(&user,sizeof(User),1,fp);
		if(strcmp(user.szName,pUser->szName) == 0)
		{
			(*pUser) = user;	
			bSearch = 1;
			break;
		}
		(*pSize) = ftell(fp);
	}
	fclose(fp);
	fp = NULL;
	return bSearch;
}

int AddUser(User* pUser)
{
	size_t pos;
	FILE* fp = fopen(szFileName,"a+");
	pos = fseek(fp,0,SEEK_END);
	fwrite(pUser,sizeof(User),1,fp);
	fclose(fp);
	fp = NULL;
	return 1;
}
int InsertUser(User* pUser,size_t pos)
{
	User user = {0};
	//파일이 없으면 생성 해도 상관 없음.
	FILE* fp = fopen(szFileName,"r+");
	//파일 위치를 이동 시킨다.
	fseek(fp,pos,SEEK_CUR);
	fwrite(pUser,sizeof(User),1,fp);
	fclose(fp);
	fp = NULL;
	return pos;
}
//int ChgNode(User* pUser) //전화번호부를 추가 한다.
//{
//
//}
int DeletrUser(User* pUser,long pos)
{
	return 0;
}

int DisplayFile(char* szFileName)
{
	int bSearch = 0;
	size_t pos = 0;
	User user = {0};
	//파일이 없으면 생성 해도 상관 없음.
	FILE* fp = fopen(szFileName,"r");
	while(feof(fp) == 0)
	{
		memset(&user,0x00,sizeof(User));
		if(fread(&user,sizeof(User),1,fp) != 0)
		{
			printf("%-10s,%3d,%-10s ,삭제(%d) ,%s \n",user.szName,user.iAge,user.szHobby,user.iDelete,user.szAddr);	
		}
	}
	
	fclose(fp);
	fp = NULL;
	return bSearch;
}