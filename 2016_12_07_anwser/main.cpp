#include "main.h"

#include <iostream>
#include "Person.h"



using namespace std;
/*
1.  1 ~ 100���� ���� ����� ����ϼ���. 
	cout�� ����ϼ���.

2. 1 ~ 100���� ���ٿ� 10���� ����ϼ���.
	������ ������ ������ �� ��

3. C�� C++�� cout, cin�� ����Ͽ� �ٲټ���
	#include <stdio.h>
	int main() { // ������ �־��� �ڵ�
		int k, n=0;
		int sum=0;
		printf("�� ���� �Է��ϼ���>>");
		scanf("%d", &n);
		for(k=1; k<=n; k++) {
			sum += k;
		}
		printf("1���� %d������ ���� %d �Դϴ�.\n", n, sum);
		return 0;
}


4. ���ڿ� 2�� �Է¹ް� ���ڿ� �˻��ϴ� ���α׷� �ۼ��ϼ���.

	cin, cout ����� ��

5. ����ڷκ��� ��� ������ �Է¹޴´�.
	-1�� �Ǹ� ����Ѵ�.
	default�� 5���� �����Ҵ��ϰ�
	5���� �Ѿ�� +5�� �����Ҵ��� ������Ų��.
	5 -> 10 -> 15
	�ݵ�� new �����ڸ� ����� ��


	6. 92���������� ������ ��
*/

//1���� 100 ������ ��.
void RangeSum()
{
	int iSum = 0;
	for(int i = 0 ; i < 100; i++)
	{
		iSum += i;
	}
	std::cout<<"1���� 100 ������ ���Դϴ�."<<iSum <<std::endl;
}

//1���� 100 ������ ��.
void RangePrint()
{
	int iSum = 0;
	for(int i = 0 ; i < 100; i++)
	{
		if(i != 0 && (i%10 == 0))
		{
			std::cout<<"\n";
		}
		cout<<i<<"\t";
	}
	
}

int mainCpp() 
{ // ������ �־��� �ڵ�
	int k, n=0;
	int sum=0;
	cout<< "�� ���� �Է��ϼ���>>" << endl;
	cin >> n;	
	for(k=1; k<=n; k++) 
	{
		sum += k;
	}
	cout<<"1����" << n <<"������ ���� "<<sum<<"�Դϴ�.";
	return 0;
}

void strInOut()
{
	char szStr1[256];
	char szStr2[256];

	cout << "���ڿ��� �Է��ϼ��� " << endl;
	cin >> szStr1 >> szStr2;

	cout << szStr1 <<","<< szStr2;
}

void dynamicAllocate()
{
	int buffSize = 5;
	int* prgData = new int[buffSize];
	//int *rgData = new int[5];
	int iInput = 0;
	int inputCnt = 0;
	
	cout <<"������ �Է� �ϼ���." << endl;
	while(iInput != -1)
	{
		cin >> iInput;
		if(iInput != -1)
		{
			prgData[inputCnt] = iInput;
			inputCnt++;

			if(inputCnt%5 == 0)
			{
				buffSize = buffSize + 5;
				int oldSize = sizeof(prgData);
				int* pNewData = new int[buffSize];
				cout<<" �޸𸮸� �߰� �Ҵ� �մϴ�." << buffSize <<endl;
				memcpy(pNewData,prgData,inputCnt*sizeof(prgData[0]));
				delete [] prgData;
				prgData = pNewData;
			}
		}
	}
	for(int i = 0; i < inputCnt; i++)
	{
		cout << prgData[i] <<endl;
	}
	delete [] prgData;
}




int main()
{
	//RangeSum();
	//RangePrint();
	//mainCpp();
	//strInOut();

	//dynamicAllocate();
	main_person();
	fflush(stdin);
	getchar();
}