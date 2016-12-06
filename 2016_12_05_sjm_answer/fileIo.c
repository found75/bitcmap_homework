#include "fileIo.h"
#include <stdio.h>
#include <string.h>



#define _FILE_NAME_ "mystory.txt"

#define _FILE_PHONE_NAME_ "phone.txt"

#define INPUT_FORMAT "%s %s %s %s"
#define OUTPUT_FORMAT "%s,%s,%s,%s\n"

User rgTUsers[_NODE_MAX_CNT_] = {0};
char buffer[_BUFF_SIZE_] = {0};
int iUserCnt = 0; 
/*
1. mystory.txt파일을 생성해서  이름, 나이, 전화번호를 저장하세요 저장의 형태는
# 이름 : 홍길동
# 나이 : 24
# 전화번호 : 010-1111-2222
*/
int HomeWork01()
{
	FILE* pFile = fopen(_FILE_NAME_,"w");
	if(pFile == NULL)
	{
		printf("파일열기에 실패하였습니다.");
		return -1;
	}
	fputs("# 이름 : 홍길동\n",pFile);
	fputs("# 나이 : 24\n",pFile);
	fputs("# 전화번호 : 010-1111-2222\n",pFile);
	
	fclose(pFile);
	pFile = NULL;

	return 1;
}

/*
2. 1번파일에 데이터를 추가하세요.
# 즐겨먹는 음식 : 짬뽕, 탕수육
# 취미 : 축구
*/
int HomeWork02()
{
	FILE* pFile = fopen(_FILE_NAME_,"a");
	if(pFile == NULL)
	{
		printf("파일열기에 실패하였습니다.");
		return -1;
	}
	fputs("# 즐겨먹는 음식 : 짬뽕, 탕수육\n",pFile);
	fputs("# 취미 : 축구\n",pFile);
	
	fclose(pFile);
	pFile = NULL;
	return 1;
}

//3. 2번을 완료한 후 파일을 읽고 출력하세요.
int HomeWork03(char* szFileName)
{
	FILE* pFile = fopen(szFileName,"r");
	char buffer[_BUFF_SIZE_];

	while(!feof(pFile))
	{
		//buffer[0] = 0x00;
		fgets(buffer,_BUFF_SIZE_,pFile);
		printf(buffer);
	}

	fclose(pFile);
	pFile = NULL;

}

//4. 주소록 포맷을 설계하고 사용자 입력을 받아서
//  추가, 수정, 삭제 해보세요
//	이름,나이,취미,주소
//	ex)
//	홍길동,024,활빈,금강산
//	임꺽정,033,파워,구월산
//	장길산,036,광대,장산곶
//	일지매,021,코스프레,서울종로
int HomeWork04()
{
	int i = 0;
	int ilen = 0;
	int iTolLen = 0;
	int bExit = 0;
	int iMatch = 0;
	char ch;
	User tUser;	
	FILE* pFile = NULL;	

	_readUsers(); // 현재 저장되어 있는 정보를 먼저읽어온다. 

	while(bExit == 0)
	{
		printf("메뉴를 선택 하세요.\n");
		printf("추가('1') , 수정('2') , 삭제('3') , 종료('0')\n");
		ch = getch();
		switch(ch)
		{
		case '0':
			bExit = 1;
			break;
		case '1': //신규			
			memset(&tUser,0x00,sizeof(User));
			memset(&buffer,0x00,sizeof(char)*_BUFF_SIZE_);
			
			printf("이름 나이 취미 주소를 입력하세요.\n");
			scanf(INPUT_FORMAT,tUser.szName,tUser.szAge,tUser.szHobby,tUser.szAddr);
			rgTUsers[iUserCnt] = tUser;
			iUserCnt++;

			_writeUsers(); //데이터를 바로 저장한다.
			pFile = NULL;
			break;
		case '2': //수정. 
			iMatch = 0;
			memset(&tUser,0x00,sizeof(User));
			memset(&buffer,0x00,sizeof(char)*_BUFF_SIZE_);
			printf("수정할 이름을 선택 하세요.\n");
			scanf("%s",buffer);
			
			for(i = 0 ; i < iUserCnt ;i++)
			{
				if(strcmp(rgTUsers[i].szName,buffer) == 0 )
				{
					printf("변경할 이름을 입력하세요\n");
					scanf("%s",buffer);
					strcpy(rgTUsers[i].szName,buffer);
				}	
			}
			_writeUsers();
			break;
		case '3':
			iMatch = 0;
			memset(&tUser,0x00,sizeof(User));
			memset(&buffer,0x00,sizeof(char)*_BUFF_SIZE_);
			printf("삭제할 이름을 선택 하세요.\n");
			scanf("%s",buffer);

			for(i = 0 ; i < iUserCnt ;i++)
			{
				if(strcmp(rgTUsers[i].szName,buffer) == 0)
				{
					rgTUsers[i].bDel = 1;
				}	
			}
			_writeUsers();
			break;
		default:

			break;
		}
	}
}


//파일에서 User 을 읽어온다.
int _readUsers()
{	
	FILE* pFile = NULL;
	iUserCnt = 0;
	pFile = fopen(_FILE_PHONE_NAME_,"r");			
	if(pFile != NULL)
	{
		while(feof(pFile) == 0)
		{
			fgets(buffer,_BUFF_SIZE_,pFile);
			rgTUsers[iUserCnt] = bufferTOUser(buffer);
			iUserCnt++;
		}

		fclose(pFile);
	}
	
}
int _writeUsers()
{
	FILE* pFile = NULL;
	int i = 0;
	pFile = fopen(_FILE_PHONE_NAME_,"w");			
	for(i = 0 ; i < iUserCnt ;i++)
	{
		if(rgTUsers[i].bDel == 0)
		{
			sprintf(buffer,OUTPUT_FORMAT,rgTUsers[i].szName,rgTUsers[i].szAge,rgTUsers[i].szHobby,rgTUsers[i].szAddr);
			fputs(buffer,pFile);
		}
	}
	fclose(pFile);
	//iUserCnt 는 종료시에 초기화 한다.
}


User bufferTOUser(char* buffer)
{
	int i;
	int ilen = 0,cntComma = 0 , idxComma = 0;	
	User tUser = {0};

	ilen = strlen(buffer);
	idxComma = 0;
	for(i = 0; i < ilen ; i++)
	{
		if(buffer[i] == ',')
		{
			cntComma++;
			idxComma = i + 1; //, 위치는 제외 시킨다. 
		}

		if(buffer[i] != ',')
		{
			if(cntComma == 0)
			{
				tUser.szName[i -idxComma] = buffer[i];	
			}
			else if(cntComma == 1)
			{
				tUser.szAge[i-idxComma ] = buffer[i];
			}
			else if(cntComma == 2)
			{
				tUser.szHobby[i -idxComma ] = buffer[i];
			}
			else
			{
				tUser.szAddr[i -idxComma ] = buffer[i];
			}	
		}
		
	}
	return tUser;
}
int fileIo_Main()
{
	//HomeWork01();
	//HomeWork02();
	//HomeWork03(_FILE_NAME_);

	HomeWork04();

	getchar();
	return 1;
};
