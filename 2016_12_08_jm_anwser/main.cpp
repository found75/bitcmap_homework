#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
/*
1. cout << �����ڸ� �̿��ؼ� �������� ����ϼ���
2 x 1 = 2  3 x 1 = 3 ..... 9 x 1 = 9
......
2 x 9 = 18

2. Ű����κ��� 2���� ������ �о ū ���� ����ϼ���

3. �Ҽ����� ������ 5���� �Ǽ��� �Է¹޾� ���� ū ���� ����ϼ���

4. <Enter>Ű�� �Էµ� ������ ���ڵ��� �а�, �Էµ� ���� 'x'�� ������ ȭ�鿡 ����ϼ���.


5. "yes"�� �Էµ� ������ �������� �ʴ� ���α׷��� �ۼ��ؼ���. �Է��� cin.getline() �Լ��� ����ϼ���

6. ';'���� 5���� �̸��� �����ؼ� �Է¹޾�, �� �̸��� ����� ȭ�鿡 ����ϼ���. �׸��� ���� �� �̸��� �Ǻ��ؼ� ��Ÿ������.
cin.getline(str, 100, ';');
ȫ�浿;�Ӳ���;����;������;��¥��Ʈ;
1:ȫ�浿
2:�Ӳ���
3:����
4:������
5:��¥��Ʈ

7. �̸�, �ּ�, ���̸� �Է¹޾� ����ϼ���.

8. ���ڿ��� �ϳ� �Է¹ް� ���ڿ��� �κ� ���ڿ��� ����ϼ���
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
	cout <<"�� 1�� �Է��ϼ��� ==> ";
	cin >> nInput01;
	cout << endl;
	cout <<"�� 2�� �Է��ϼ��� ==> ";
	cin >> nInput02;

	fflush(stdin);

	if(nInput01 != nInput02)
	{
		cout << "ū ���� ==> " << ((nInput01 > nInput02)?nInput01:nInput02) << endl;
	}
	else 
	{
		cout << "�ΰ��� ��ġ �մϴ�."<< endl;
	}
}

//3. �Ҽ����� ������ 5���� �Ǽ��� �Է¹޾� ���� ū ���� ����ϼ���
void InputFloat()
{
	float rgBuffer[5];
	float nMax = 0;;
	cout << "�Ǽ��� 5�� �Է��Ͻÿ�" << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << (i + 1) << " ��° �Ǽ��� �Է��ϼ���." << endl;
		cin >> rgBuffer[i];
		cout << endl;
	}
	fflush(stdin);
	for(int i = 0; i < 5; i++)
	{
		nMax = (nMax < rgBuffer[i] )?rgBuffer[i]:nMax;
	}
	cout <<"�ִ밪�� " << nMax <<" �Դϴ�."<< endl;
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