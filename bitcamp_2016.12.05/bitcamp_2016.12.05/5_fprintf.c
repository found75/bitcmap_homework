#include <stdio.h>
#include <Windows.h>
#include <string.h>
#define STR_LEN 1024

void main()
{
	char str[STR_LEN];
	FILE* fp = fopen("������ �츮��.txt","wt");
	fputs("�︪�� ������ ������ 200��\n",fp);
	fputs("�ܷο� ���ϳ� ���鿡 ����\n",fp);
	fputs("�״��� �ƹ��� �ڱ�� ���̶�� ��ܵ�\n",fp);

	fclose(fp);
	fp = NULL;

	fp = fopen("������ �츮��.txt","rt");
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fclose(fp);
	fp = NULL;

	getchar();
}


