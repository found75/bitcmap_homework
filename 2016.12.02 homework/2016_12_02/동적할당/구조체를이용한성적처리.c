#include <stdio.h>

#define MAX_NAME 20
#define SUBJECTS 3
#define STUDENTS 3

typedef struct grade
{
	char name[MAX_NAME];
	int score[SUBJECTS];
	int total;
	double average;
}Grade;

void main()
{
	char* subjects[SUBJECTS]={"����", "����", "����"};
	Grade grd[STUDENTS];
	int i=0, j=0;

	// 1) ���� �Է�
	for(i=0;i<STUDENTS;i++)
	{
		printf("*********************%d ��° �л�*********************\n", i+1);
		printf("�̸� : ");
		scanf("%s", grd[i].name);

		for(j=0;j<SUBJECTS;j++)
		{
			printf("%s: ", subjects[j]);
			scanf("%d", &(grd[i].score[j]));
		}
	}

	// 2) ���� ���
	for(i=0;i<STUDENTS;i++)
	{
		grd[i].total=0;
		for(j=0;j<SUBJECTS;j++)
		{
			grd[i].total += grd[i].score[j];
		}
		grd[i].average = (double)grd[i].total/SUBJECTS;
	}

	// 3) ���� ���
	printf("--------------------------------------------------\n");
	printf("�̸�\t| ����\t| ����\t| ����\t| ����\t| ���\n");
	for(i=0;i<STUDENTS;i++)
	{
		printf("%s\t| ", grd[i].name);
		for(j=0;j<SUBJECTS;j++)
		{
			printf("%d\t| ", grd[i].score[j]);
		}
		printf("%d\t| ", grd[i].total);
		printf("%0.2lf\n", grd[i].average);
	}
	printf("--------------------------------------------------\n");
}