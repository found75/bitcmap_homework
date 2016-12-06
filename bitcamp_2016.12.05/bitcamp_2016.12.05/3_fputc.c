#include <stdio.h>


void main()
{
	char str[1024];
	FILE* fp = fopen("¾Ö±¹°¡.txt","rt");

	while(feof(fp) == 0)
	{
		memset(str,0,sizeof(str));
		fgets(str,sizeof(str),fp);
		printf("%s",str);
	}
	fclose(fp);
	fp = NULL;

	getchar();
}
