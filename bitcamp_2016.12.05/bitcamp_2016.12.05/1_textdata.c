#include <stdio.h>


void main()
{
	FILE* fp = fopen("�ֱ���.txt","wb");

	fputs("���ع�����λ���\n",fp);
	fputs("������⵵��\n",fp);
	fputs("�ϴ����� �����ϻ�\n",fp);
	fputs("�츮���� ����\n",fp);

	fclose(fp);
	fp = NULL;
}
