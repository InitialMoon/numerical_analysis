#include <iostream>
#include <algorithm>
using namespace std;
const int MAXSIZE = 100;
int n = 0;
int InteratorNum = 0;// ��¼��������
double eps = 1e-5;// �����
double e = 1e2; // ��������в��ϱ仯�����ڲ���������
int methodType = 0;
double A[MAXSIZE][MAXSIZE];
double B[MAXSIZE];
// �ſ˱ȷ�����Ҫʹ����������˹���¶���ֻ��һ��
double X0[MAXSIZE];// �������д�ŵ�Ԫ�����ᱣ�����᲻���滻
double X1[MAXSIZE];// �������д�ŵ�Ԫ�����ᱣ�����᲻���滻
double F[MAXSIZE][MAXSIZE]; // ������ʽϵ����ţ���һ��ϵ���ǳ�������������µ�ϵ����˳�򣬻������Լ���һ��,��һ�£��������
double* a = X0;
double* b = X1;
void Jacobi();
void Guess_Seidel();
void solve();
void output();

void init() {
	for (int i = 0; i < n; i++) {
		X0[i] = 0;
		X1[i] = 0;
	}
}

void input() {
	cout << "�����뷽�������:";
	cin >> n;
	cout << "�����뷽������������:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
		}
		cin >> B[i];
	}
}

void select() {
	cout << "��ѡ������ʹ�õķ���" << endl;
	cout << "1.�ſ˱ȵ�����" << endl;
	cout << "2.��˹���¶�������" << endl;

	cin >> methodType;

	switch (methodType) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}
int main() {
	init();
	while (methodType <= 0 || methodType > 2) { // ѡ��Ϸ��Լ��
		select();
	}
	input();
	solve();
	output();
}

// Jacobi������
void Jacobi() {
	InteratorNum++;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				a[i] += F[i][j] * b[j];
			}
		}
		a[i] += F[i][n - 1];
		e = abs(a[i] - b[i]);
	}
}

void Guess_Seidel() {
	InteratorNum++;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				a[i] += F[i][j] * b[i];
			}
		}
		a[i] += F[i][n];
		e = abs(a[i] - b[i]);
		swap(a, b);
	}
}

void solve() {
	// ���������ʽ��ϵ��
	for (int i = 0; i < n; i++) {
		double aa =  - A[i][i];
		for (int j = 0; j < n; j++) {
			if (i != j) {
				F[i][j] = A[i][j] / aa;
			}
		}
		F[i][n] = B[i] / aa;
	}
	// ��ʼ��������
	// e�Ǽ�������е���������ϴε���ֵ֮��ģ�����ֻ��дһ���ܴ������ֹһ��ʼ�ͻ���
	while (InteratorNum < 10) {
		if (methodType == 1) {
			Jacobi();
		}
		else {
			Guess_Seidel();
		}
		swap(a, b);
	}
}

void output() {
	cout << "���̵Ľ��ǣ�" << endl;
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << X0[i] << endl;
	}
	cout << "����������" << InteratorNum << endl;
}
