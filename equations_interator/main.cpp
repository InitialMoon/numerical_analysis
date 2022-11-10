#include <iostream>
#include <algorithm>
using namespace std;
const int MAXSIZE = 100;
int n = 0;
int InteratorNum = 0;// 记录迭代次数
double eps = 1e-5;// 误差限
double e = 1e2; // 计算过程中不断变化的用于测量误差的数
int methodType = 0;
double A[MAXSIZE][MAXSIZE];
double B[MAXSIZE];
// 雅克比方法需要使用两个，高斯赛德尔法只用一个
double X0[MAXSIZE];// 迭代序列存放单元，不会保留，会不断替换
double X1[MAXSIZE];// 迭代序列存放单元，不会保留，会不断替换
double F[MAXSIZE][MAXSIZE]; // 迭代公式系数存放，第一个系数是常数项，后面是余下的系数，顺序，会跳过自己这一项,反一下，最后处理常数
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

void select() {
	cout << "请选择你想使用的方法" << endl;
	cout << "1.雅克比迭代法" << endl;
	cout << "2.高斯赛德尔迭代法" << endl;

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
	while (methodType <= 0 || methodType > 2) { // 选项合法性检测
		select();
	}
	input();
	solve();
	output();
}

// Jacobi迭代法
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
	// 计算迭代公式的系数
	for (int i = 0; i < n; i++) {
		double aa =  - A[i][i];
		for (int j = 0; j < n; j++) {
			if (i != j) {
				F[i][j] = A[i][j] / aa;
			}
		}
		F[i][n] = B[i] / aa;
	}
	// 开始迭代计算
	// e是计算过程中的最大误差，和上次迭代值之间的，这里只是写一个很大的数防止一开始就坏掉
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
	cout << "方程的解是：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << X0[i] << endl;
	}
	cout << "迭代次数：" << InteratorNum << endl;
}
