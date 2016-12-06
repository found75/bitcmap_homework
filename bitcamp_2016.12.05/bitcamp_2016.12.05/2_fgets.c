#include <stdio.h>
#include <windows.h>

void main()
{
	char str[1024];
	char ch = 0x00;
	FILE* fp = fopen("애국가.txt","wt");
	fputc('A',fp);
	fputc('B',fp);
	fputc('C',fp);
	//fputc('\r',fp);
	//fputc('\n',fp);
	fputc('D',fp);
	fputc('E',fp);
	fputc('F',fp);
	fclose(fp);
	fp = NULL;

	fp = fopen("애국가.txt","rt");
	
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);
	ch = fgetc(fp); Sleep(1000) ;putchar(ch);

	fclose(fp);
	fp = NULL;


	getchar();
}
