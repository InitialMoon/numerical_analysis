#include <iostream>
#include <cmath>
#define MAXSIZE 100
using namespace std;

double A[MAXSIZE][MAXSIZE]; // 初始的系数矩阵
double U[MAXSIZE][MAXSIZE]; // 化为上三角矩阵过程中产生的U系数矩阵
double L[MAXSIZE][MAXSIZE]; // 同上L矩阵
double B[MAXSIZE]; // 右边的常数项向量
double Z[MAXSIZE]; // 化为上三角矩阵后的系数向量
double X[MAXSIZE]; // 解的存放单元
int n = 0;
int methodType = 0;
double(*Lii)(int) = NULL;

void input();
void select();
void back();
void solve();
void Eliminate(); // 消元过程
void output();
double GuessLii(int i);
double CroutLii(int i);

int main() {
	while (methodType <= 0 || methodType > 4) { // 选项合法性检测
		select();
	}
	input();
	solve();
	output();
}

void input() {
	cout << "其输入方程组的秩:";
	cin >> n;
	cout << "请输入方程组的增广矩阵:" << endl;
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
	cout << "请选择你想使用的方法" << endl;
	cout << "1.高斯消元法" << endl;
	cout << "2.克劳特消元法" << endl;
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

// 回带上三角矩阵过程
void back() {
	for (int i = n - 1; i >= 0; i--) {
		X[i] = Z[i];
		for (int k = i + 1; k < n; k++) {
			X[i] -= U[i][k] * X[k];
		}
		X[i] /= U[i][i];
	}
}

// 从上至下消元过程
void Eliminate() {
	for (int i = 0; i < n; i++) {
		// Lij计算
		Lii(i);
		for (int j = 0; j < i; j++) {
			L[i][j] = A[i][j];
			for (int k = 0; k < j; k++) {
				L[i][j] -= L[i][k] * U[k][j];
			}
			L[i][j] /= U[j][j];
		}

		// Uij计算
		for (int j = i; j < n; j++) {
			U[i][j] = A[i][j];
			for (int k = 0; k < i; k++) {
				U[i][j] -= L[i][k] * U[k][j];
			}
		}

		// Zi计算
		Z[i] = B[i];
		for (int k = 0; k < i; k++) {
			Z[i] -= L[i][k] * Z[k];
		}
	}
}

// 高斯消元法的lii计算方式
double GuessLii(int i) {
	L[i][i] = 1;
	return 1;
}

double CroutLii(int i) {
	return 0.0;
}
