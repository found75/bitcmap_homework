#include <stdio.h>
#include <Windows.h>
#include <string.h>
#define STR_LEN 1024
void main()
{
	char buffer[STR_LEN];
	int korean[] = {23,23,12,23,43,12,43,23};
	int sum = 0 , i = 0;
	double ave = 0.0;
	FILE* fp = NULL;

	for(i = 0; i < sizeof(korean)/sizeof(int); i++)
	{
		sum += korean[i];
	}
	ave = sum/(sizeof(korean)/sizeof(int));


	fp = fopen("국어점수.bin","wb");
	if(fp == NULL)
	{
		printf("에러\n");
	}
	sprintf(buffer,"국어점수");
	fwrite(buffer,sizeof(char),strlen(buffer)+1,fp);

	sprintf(buffer,"총점: ");
	fwrite(buffer,sizeof(char),strlen(buffer)+1,fp);
	fwrite(&sum,sizeof(int),1,fp);
	sprintf(buffer,"평균: ");
	fwrite(buffer,sizeof(char),strlen(buffer)+1,fp);
	fwrite(&ave,sizeof(int),1,fp);



	fclose(fp);
	fp = NULL;
	getchar();
}