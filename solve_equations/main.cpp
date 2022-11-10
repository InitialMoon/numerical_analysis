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
void(*Eliminate)() = NULL; // �������õ���Ԫ����

void input();
void select();
void back();
void solve();
void CEliminate(); // �����ع�����Ԫ����
void GEliminate(); // ��˹��Ԫ����
void SqEliminate(); // ƽ��������Ԫ����
void mainEliminate(); // ��Ԫ�ط�
void output();

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
	cout.precision(4);

	cout << "������Ľ����£�" << endl;
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << X[i] << endl;
	}
	cout << endl;

	cout << "L" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cout << L[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "U" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			cout << U[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << 'Z' << endl;
	for (int i = 0; i < n; i++) {
		cout << Z[i] << " ";
	}
	cout << endl;
}

void select() {
	cout << "��ѡ������ʹ�õķ���" << endl;
	cout << "1.��˹��Ԫ��" << endl;
	cout << "2.��������Ԫ��" << endl;
	cout << "3.ƽ������" << endl;
	cout << "4.����Ԫ�ط�" << endl;

	cin >> methodType;

	switch (methodType) {
	case 1:
		Eliminate = GEliminate;
		break;
	case 2:
		Eliminate = CEliminate;
		break;
	case 3:
		Eliminate = SqEliminate;
		break;
	case 4:
		Eliminate = mainEliminate;
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
void GEliminate() {
	for (int i = 0; i < n; i++) {
		// Lij����
		L[i][i] = 1;

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

void CEliminate() {
	for (int i = 0; i < n; i++) {
		// Lij����,ֱ�ӽ��и�ֵ�������У������ٳ���
		for (int j = 0; j < i; j++) {
			L[i][j] = A[i][j];
			for (int k = 0; k < j; k++) {
				L[i][j] -= U[k][j] * L[i][k];
			}
		}

		L[i][i] = A[i][i];
		for (int j = 0; j < i; j++) {
			L[i][i] -= L[i][j] * U[j][i];
		}

		// Uij����
		U[i][i] = 1;
		for (int j = i + 1; j < n; j++) {
			U[i][j] = A[i][j];
			for (int k = 0; k < i; k++) {
				U[i][j] -= L[i][k] * U[k][j];
			}
			U[i][j] /= L[i][i];
		}

		// Zi����
		Z[i] = B[i];
		for (int k = 0; k < i; k++) {
			Z[i] -= L[i][k] * Z[k];
		}
		Z[i] /= L[i][i];
	}
}

void SqEliminate() {

}

void mainEliminate() {

}
