#include "main.h"

#include <iostream>


using namespace std;
/*
1.  1 ~ 100까지 더한 결과를 출력하세요. 
	cout을 사용하세요.

2. 1 ~ 100까지 한줄에 10개씩 출력하세요.
	정수는 탭으로 간격을 줄 것

3. C를 C++의 cout, cin을 사용하여 바꾸세요
	#include <stdio.h>
	int main() { // 문제에 주어진 코드
		int k, n=0;
		int sum=0;
		printf("끝 수를 입력하세요>>");
		scanf("%d", &n);
		for(k=1; k<=n; k++) {
			sum += k;
		}
		printf("1에서 %d까지의 합은 %d 입니다.\n", n, sum);
		return 0;
}


4. 문자열 2개 입력받고 문자열 검사하는 프로그램 작성하세요.

	cin, cout 사용할 것

5. 사용자로부터 계속 정수를 입력받는다.
	-1이 되면 출력한다.
	default로 5개를 동적할당하고
	5개를 넘어가면 +5씩 동적할당을 증가시킨다.
	5 -> 10 -> 15
	반드시 new 연산자를 사용할 것


	6. 92페이지까지 예습할 것
*/

//1부터 100 까지의 합.
void RangeSum()
{
	int iSum = 0;
	for(int i = 0 ; i < 100; i++)
	{
		iSum += i;
	}
	std::cout<<"1부터 100 까지의 합입니다."<<iSum <<std::endl;
}

//1부터 100 까지의 합.
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
{ // 문제에 주어진 코드
	int k, n=0;
	int sum=0;
	cout<< "끝 수를 입력하세요>>" << endl;
	cin >> n;	
	for(k=1; k<=n; k++) 
	{
		sum += k;
	}
	cout<<"1에서" << n <<"까지의 합은 "<<sum<<"입니다.";
	return 0;
}

void strInOut()
{
	char szStr1[256];
	char szStr2[256];

	cout << "문자열을 입력하세요 " << endl;
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
	
	cout <<"숫자을 입력 하세요." << endl;
	while(iInput != -1)
	{
		cin >> iInput;
		prgData[inputCnt] = iInput;
		inputCnt++;
		
		if(inputCnt%5 == 0)
		{
			buffSize = buffSize + 5;
			int oldSize = sizeof(prgData);
			int* pNewData = new int[buffSize];
			cout<<" 메모리를 추가 할당 합니다." << buffSize <<endl;
			memcpy(pNewData,prgData,inputCnt*sizeof(prgData[0]));
			delete [] prgData;
			prgData = pNewData;
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

	dynamicAllocate();
	fflush(stdin);
	getchar();
}