#include <iostream>
#include <cmath>
#include "constFeild.h"

using namespace std;


double eps = 5e-6;// Ĭ����Χ
double ans = 0;
int interNum = 0; // ��������
// ��������
double NewtonF(double x) {
	double res = 0;
	res = x - (x - pow(e, -x)) / (1 + x);
	return res;
}

double NewtonInterator(double xn) {
	interNum++;
	xn = NewtonF(xn);
	return xn;
}

int Newton() {
	double x0 = 0.5; //��ֵ
	double xn = 0.6; // ��Χ��ĩλ��
	int n = 0; // �洢�û����뾫��

	cout << "����Գ������벻ͬ�ĳ�ֵ���м���Ա�" << endl;
	cout << "�������ֵ����ʾ��������Ϊ0.5-0.6����" ;
	cin >> x0;

	cout << "��������Ҫ�ľ��ȣ�����Ҫ��0.5x10�ĸ�n�η�����ʽ���룩��n = ";
	cin >> n;

	eps = 0.5 * pow(10, -n);

	while (abs(xn - x0) > eps) {
		xn = NewtonInterator(x0);
		x0 = NewtonInterator(xn);
	}
	cout.precision(n);
	cout << "�÷��̵Ľ��ǣ�" << xn << endl;
	cout << "���������ǣ�" << interNum << endl;
	return 0;
}
