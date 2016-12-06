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
	int  bDel; //���� ����
};


typedef struct _user User;


/*
1. mystory.txt������ �����ؼ�  �̸�, ����, ��ȭ��ȣ�� �����ϼ��� ������ ���´�
# �̸� : ȫ�浿
# ���� : 24
# ��ȭ��ȣ : 010-1111-2222
*/
int HomeWork01();

/*
2. 1�����Ͽ� �����͸� �߰��ϼ���.
# ��ܸԴ� ���� : «��, ������
# ��� : �౸
*/
int HomeWork02();

//3. 2���� �Ϸ��� �� ������ �а� ����ϼ���.
int HomeWork03(char* szFileName);

//4. �ּҷ� ������ �����ϰ� ����� �Է��� �޾Ƽ�
//  �߰�, ����, ���� �غ�����
//	�̸�,����,���,�ּ�
//	ex)
//	ȫ�浿,024,Ȱ��,�ݰ���
//	�Ӳ���,033,�Ŀ�,������
//	����,036,����,����
//	������,021,�ڽ�����,��������
int HomeWork04();
int _readUsers();
int _writeUsers();

User bufferTOUser(char* buffer);

int fileIo_Main();

extern User rgTUsers[_NODE_MAX_CNT_];
extern char buffer[_BUFF_SIZE_];
//�����Ͱ� �Է� �Ǿ��ִ� ��ġ ������ ������. ������ ��� ����.
extern int iUserCnt; 

#endif


