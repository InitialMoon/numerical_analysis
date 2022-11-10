#include <iostream>
#include <cmath>
#define MAXSIZE 100
using namespace std;

double A[MAXSIZE][MAXSIZE]; // ��ʼ��ϵ������
double U[MAXSIZE][MAXSIZE]; // ��Ϊ�����Ǿ�������в�����Uϵ������
double L[MAXSIZE][MAXSIZE]; // ͬ��L����
double B[MAXSIZE]; // �ұߵĳ���������
double Z[MAXSIZE]; // ��Ϊ�����Ǿ�����ϵ������
double X[MAXSIZE]; // ��Ĵ�ŵ�Ԫ
int n = 0;
int methodType = 0;
double(*Lii)(int) = NULL;

void input();
void select();
void back();
void solve();
void Eliminate(); // ��Ԫ����
void output();
double GuessLii(int i);
double CroutLii(int i);

int main() {
	while (methodType <= 0 || methodType > 4) { // ѡ��Ϸ��Լ��
		select();
	}
	input();
	solve();
	output();
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

void output() {
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << X[i] << endl;
	}
}

void select() {
	cout << "��ѡ������ʹ�õķ���" << endl;
	cout << "1.��˹��Ԫ��" << endl;
	cout << "2.��������Ԫ��" << endl;
	cin >> methodType;
	switch (methodType) {
	case 1:
		Lii = GuessLii;
		break;
	case 2:
		Lii = CroutLii;
		break;
	default:
		break;
	}
}

void solve() {
	Eliminate();
	back();
}

// �ش������Ǿ������
void back() {
	for (int i = n - 1; i >= 0; i--) {
		X[i] = Z[i];
		for (int k = i + 1; k < n; k++) {
			X[i] -= U[i][k] * X[k];
		}
		X[i] /= U[i][i];
	}
}

// ����������Ԫ����
void Eliminate() {
	for (int i = 0; i < n; i++) {
		// Lij����
		Lii(i);
		for (int j = 0; j < i; j++) {
			L[i][j] = A[i][j];
			for (int k = 0; k < j; k++) {
				L[i][j] -= L[i][k] * U[k][j];
			}
			L[i][j] /= U[j][j];
		}

		// Uij����
		for (int j = i; j < n; j++) {
			U[i][j] = A[i][j];
			for (int k = 0; k < i; k++) {
				U[i][j] -= L[i][k] * U[k][j];
			}
		}

		// Zi����
		Z[i] = B[i];
		for (int k = 0; k < i; k++) {
			Z[i] -= L[i][k] * Z[k];
		}
	}
}

// ��˹��Ԫ����lii���㷽ʽ
double GuessLii(int i) {
	L[i][i] = 1;
	return 1;
}

double CroutLii(int i) {
	return 0.0;
}
