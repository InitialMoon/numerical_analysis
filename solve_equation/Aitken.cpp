#include "constFeild.h"
#include <cmath>
#include <iostream>

using namespace std;

double eps = 5e-6;// Ĭ����Χ
double ans = 0;
int interNum = 0; // ��������

// ��������
double F(double x) {
	return pow(e, -x);
}

double interator(double xn) {
	interNum++;
	double yn = F(xn);
	double zn = F(yn);
	double xn1 = (zn * xn - yn * yn) / (zn + xn - 2 * yn);
	return xn1;
}

int Aitken() {
	double x0 = 0.5; //��ֵ
	double xn = 0.6; // ��Χ��ĩλ��
	int n = 0; // �洢�û����뾫��
	cout << "����Գ������벻ͬ�ĳ�ֵ���м���Ա�" << endl;
	cout << "�������ֵ����ʾ��������Ϊ0.5-0.6����" ;
	cin >> x0;
	cout << endl;
	cout << "��������Ҫ�ľ��ȣ�����Ҫ��0.5x10�ĸ�n�η�����ʽ���룩��n = ";
	cin >> n;
	eps = 0.5 * pow(10, -n);
	while (abs(xn - x0) > eps) {
		xn = interator(x0);
		x0 = interator(xn);
	}
	cout.precision(n);
	cout << "�÷��̵Ľ��ǣ�" << xn << endl;
	cout << "���������ǣ�" << interNum << endl;
	return 0;
}