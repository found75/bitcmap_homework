#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
/*
1. cout << 연산자를 이용해서 구구단을 출력하세요
2 x 1 = 2  3 x 1 = 3 ..... 9 x 1 = 9
......
2 x 9 = 18

2. 키보드로부터 2개의 정수를 읽어서 큰 수를 출력하세요

3. 소수점을 가지는 5개의 실수를 입력받아 제일 큰 수를 출력하세요

4. <Enter>키가 입력될 때까지 문자들을 읽고, 입력된 문자 'x'의 개수를 화면에 출력하세요.


5. "yes"가 입력될 때까지 종료하지 않는 프로그램을 작성해세요. 입력은 cin.getline() 함수를 사용하세요

6. ';'으로 5개의 이름을 구분해서 입력받아, 각 이름을 끊어내여 화면에 출력하세요. 그리고 가장 긴 이름을 판별해서 나타내세요.
cin.getline(str, 100, ';');
홍길동;임꺽정;장길산;일지매;모짜르트;
1:홍길동
2:임꺽정
3:장길산
4:일지매
5:모짜르트

7. 이름, 주소, 나이를 입력받아 출력하세요.

8. 문자열을 하나 입력받고 문자열의 부분 문자열을 출력하세요
hello
h
he
hel
hell
hello
*/

void Gugudan()
{
	for(int row = 1 ; row < 10 ; row++)
	{
		for(int col = 2; col < 10; col++)
		{
			cout << col << "*" << row << "=" << col*row << "\t";
		}
		cout << endl;
	}
}

void ShowMax()
{
	int nInput01, nInput02;
	cout <<"값 1을 입력하세요 ==> ";
	cin >> nInput01;
	cout << endl;
	cout <<"값 2을 입력하세요 ==> ";
	cin >> nInput02;

	fflush(stdin);

	if(nInput01 != nInput02)
	{
		cout << "큰 값은 ==> " << ((nInput01 > nInput02)?nInput01:nInput02) << endl;
	}
	else 
	{
		cout << "두값을 일치 합니다."<< endl;
	}
}

//3. 소수점을 가지는 5개의 실수를 입력받아 제일 큰 수를 출력하세요
void InputFloat()
{
	float rgBuffer[5];
	float nMax = 0;;
	cout << "실수를 5개 입력하시오" << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << (i + 1) << " 번째 실수를 입력하세요." << endl;
		cin >> rgBuffer[i];
		cout << endl;
	}
	fflush(stdin);
	for(int i = 0; i < 5; i++)
	{
		nMax = (nMax < rgBuffer[i] )?rgBuffer[i]:nMax;
	}
	cout <<"최대값은 " << nMax <<" 입니다."<< endl;
}
void xCount()
{
	//vector<char> vecCh;
	//int ch;
	//while()
	//{
	//	ch = getin();
	//}
}
int main()
{	
	//Gugudan();
	//ShowMax();
	//InputFloat();
	getchar();
}