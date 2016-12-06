#include <stdio.h>


void main()
{
	FILE* fp = fopen("애국가.txt","wb");

	fputs("동해물과백두산이\n",fp);
	fputs("마르고닳도록\n",fp);
	fputs("하느님이 보우하사\n",fp);
	fputs("우리나라 만세\n",fp);

	fclose(fp);
	fp = NULL;
}
