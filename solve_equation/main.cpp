#include <iostream>
#include "Aitken.h"
#include "Newton.h"

using namespace std;
int main() {
	int type = 0;
	cout << "==��������ⷽ��==" << endl;
	cout << "����������б�ѡ����ⷽ��ʹ�õķ���" << endl;
	cout << "1---���ؿϷ�" << endl;
	cout << "2---ţ�ٵ�����" << endl;
	re: // �Ƿ����������������ȡ
	cin >> type;
	switch (type)
	{
	case 1:
		Aitken();
		break;
	case 2:
		Newton();
		break;
	default:
		cout << "�������Ƿ����������б��е�����" << endl;
		goto re;
		break;
	}
}