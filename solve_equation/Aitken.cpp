#include "constFeild.h"
#include <cmath>
#include <iostream>

using namespace std;

double epsa = 5e-6;// Ĭ����Χ
double ansa = 0;
int interNuma = 0; // ��������
// ��������
double AitkenF(double x) {
	return pow(e, -x);
}

double AitkenInterator(double xn) {
	interNuma++;
	double yn = AitkenF(xn);
	double zn = AitkenF(yn);
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
	cout << "��������Ҫ�ľ��ȣ�����Ҫ��0.5x10�ĸ�n�η�����ʽ���룩��n = ";
	cin >> n;
	epsa = 0.5 * pow(10, -n);
	while (abs(xn - x0) > epsa) {
		xn = AitkenInterator(x0);
		x0 = AitkenInterator(xn);
	}
	cout.precision(n);
	cout << "�÷��̵Ľ��ǣ�" << xn << endl;
	cout << "���������ǣ�" << interNuma << endl;
	return 0;
}