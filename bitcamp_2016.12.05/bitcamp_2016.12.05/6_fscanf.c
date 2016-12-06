#include <stdio.h>
#include <Windows.h>
#define STR_LEN 1024

void main()
{
	char str[STR_LEN];
	FILE* fp = fopen("독도는 우리땅.txt","wt");
	fputs("울릉도 동남쪽 뱃길따라 200리\n",fp);
	fputs("외로운 섬하나 새들에 고향\n",fp);
	fputs("그누가 아무리 자기네 땅이라고 우겨도\n",fp);
	
	fclose(fp);
	fp = NULL;

	fp = fopen("독도는 우리땅.txt","rt");
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fgets(str,STR_LEN,fp); Sleep(500); puts(str);
	fclose(fp);
	fp = NULL;

	getchar();
}
