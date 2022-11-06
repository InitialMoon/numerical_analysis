#include <iostream>
#include "Aitken.h"
#include "Newton.h"
#include "stringm.h"

int type = 0;
double eps = 5e-6;// Ĭ����Χ
double ans = 0;
int interNum = 0; // ��������

using namespace std;

int main() {
	double(*interator)(double, int&) = NULL;
	bool isString = false;
	cout << "==��������ⷽ��==" << endl;
	cout << "����������б�ѡ����ⷽ��ʹ�õķ���" << endl;
	cout << "1---���ؿϷ�" << endl;
	cout << "2---ţ�ٵ�����" << endl;
	cout << "3---1��2��Ͻ�׳��" << endl;
	cout << "4---�����ҽط�" << endl;
	cout << "5---˫���ҽط�" << endl;

	re: // �Ƿ����������������ȡ
	cin >> type;
	switch (type)
	{
	case 1:
		interator = AitkenInterator;
		break;
	case 2:
		interator = NewtonInterator;
		break;
	case 3:
		break;
	case 4:
	case 5:
		isString = true;
		break;
	default:
		cout << "�������Ƿ����������б��е�����" << endl;
		goto re;
		break;
	}

	double x0 = 0.5; //��ֵ
	double xn = 0.6; // ��Χ��ĩλ��
	int n = 0; // �洢�û����뾫��

	cout << "����Գ������벻ͬ�ĳ�ֵ���м���Ա�" << endl;
	cout << "�������ֵ����ʾ��������Ϊ0.5-0.6����" ;
	cin >> x0;
	
	// ѡ��3ʱ�Żᴥ�����Զ�ѡ����
	if (type == 3) {
		if (abs(x0 - xn) < 0.1) {
			interator = NewtonInterator;
		}
		else {
			interator = AitkenInterator;
		}
	}
	cout << "��������Ҫ�ľ��ȣ�����Ҫ��0.5x10�ĸ�n�η�����ʽ���룩��n = ";
	cin >> n;
	eps = 0.5 * pow(10, -n);
	if (!isString) {
		while (abs(xn - x0) > eps) {
			xn = interator(x0, interNum);
			x0 = interator(xn, interNum);
			if (abs(xn - 0.5) < 0.1 && type == 3) {
				// ѡ��3ʱ�Żᴥ�����Զ�ѡ����
				interator = NewtonInterator;
			}
		}
	}
	else {
		double x1 = x0;
		while (abs(xn - x1) > eps) {
			if (type == 4) {
				x1 = sStringInterator(xn, x0, interNum);
				xn = sStringInterator(x1, x0, interNum);
			}
			if (type == 5) {
				x1 = dStringInterator(xn, x1, interNum);
				xn = dStringInterator(x1, xn, interNum);
			}
		}
	}
	cout.precision(n);
	cout << "�÷��̵Ľ��ǣ�" << xn << endl;
	cout << "���������ǣ�" << interNum << endl;
	return 0;
}