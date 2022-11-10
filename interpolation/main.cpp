// ţ�ٻ������̹�ʽ
#include <iostream>
const int MAXSIZE = 100;
int N = 0;
double xn = 0;
double X[MAXSIZE] = { 0 };
double Y[MAXSIZE] = { 0 };
double P[MAXSIZE][MAXSIZE] = { 0 };
double res = 0;
using namespace std;

void input() {
	cout << "�������ֵ�ڵ�ĸ���:";
	cin >> N;
	cout << "�밴��x,yһ��һ���˳������x,yֵ" << endl;
	for (int i = 0; i < N; i++) {
		cout << "��" << i << "��" << ":";
		cin >> X[i] >> Y[i];
		cout << "x" << i << "=" << X[i] << endl;
		cout << "y" << i << "=" << Y[i] << endl;
	}
	cout << "��ֵ�㣺" << endl;
	cin >> xn;
}

void output() {
	cout << "��ֵ���:" << res << endl;
}

// count�����ֵ����
void interpolate(int count) {
	int value = 1;
	for (int i = 0; i < count; i++) {
		for (int j = i; j < count; j++) {
			double Quotient = (P[j + 1][i] - P[j][i]) / (X[j + 1] - X[j + 1 - value]);
			P[j + 1][i + 1] = Quotient;
		}
		value += 1;
	}
}

void front_solve() {
	double calcValue = 0, temp = 1;
	int j = 0;
	for (int i = 0; i < N; i++) {
		temp = 1;
		for (int j = 0; j < i; j++) {
			temp *= (xn - X[j]);
		}
		temp *= P[i][i];
		calcValue += temp;
	}
	res = calcValue;
}

int main() {
	input();
	for (int i = 0; i < N; i++) {
		P[i][0] = Y[i];
	}
	interpolate(N);
	front_solve();
	output();
}
