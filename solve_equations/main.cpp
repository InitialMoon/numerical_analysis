#include <iostream>
#include <cmath>
#include <algorithm>
#define MAXSIZE 100
using namespace std;

double A[MAXSIZE][MAXSIZE]; // 初始的系数矩阵
double U[MAXSIZE][MAXSIZE]; // 化为上三角矩阵过程中产生的U系数矩阵
double L[MAXSIZE][MAXSIZE]; // 同上L矩阵
double B[MAXSIZE]; // 右边的常数项向量
double Z[MAXSIZE]; // 化为上三角矩阵后的系数向量
double X[MAXSIZE]; // 解的存放单元
int mainsqe[MAXSIZE];
int maxElement[MAXSIZE]; // 记录主元素法的顺序
int n = 0;
int methodType = 0;
void(*Eliminate)() = NULL; // 真正调用的消元过程

void input();
void select();
void back();
void solve();
void CEliminate(); // 克劳特共用消元过程
void GEliminate(); // 高斯消元过程
void SqEliminate(); // 平方根法消元过程
void mainEliminate(); // 主元素法
void output();
void init();

int main() {
	init();
	while (methodType <= 0 || methodType > 4) { // 选项合法性检测
		select();
	}
	input();
	solve();
	output();
}

void init() {
	// 初始化循序公用部分
	for (int i = 0; i < MAXSIZE; i++) {
		maxElement[i] = i;
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

void output() {
	cout.precision(4);

	cout << "方程组的解如下：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "x" << maxElement[i] + 1 << " = " << X[maxElement[i]] << endl;
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
		cout << Z[maxElement[i]] << " ";
	}
	cout << endl;
}

void select() {
	cout << "请选择你想使用的方法" << endl;
	cout << "1.高斯消元法" << endl;
	cout << "2.克劳特消元法" << endl;
	cout << "3.平方根法" << endl;
	cout << "4.列主元素法" << endl;

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
void GEliminate() {
	for (int i = 0; i < n; i++) {
		// Lij计算
		L[i][i] = 1;

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

void CEliminate() {
	for (int i = 0; i < n; i++) {
		// Lij计算,直接进行赋值操作就行，不用再除了
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

		// Uij计算
		U[i][i] = 1;
		for (int j = i + 1; j < n; j++) {
			U[i][j] = A[i][j];
			for (int k = 0; k < i; k++) {
				U[i][j] -= L[i][k] * U[k][j];
			}
			U[i][j] /= L[i][i];
		}

		// Zi计算
		Z[i] = B[i];
		for (int k = 0; k < i; k++) {
			Z[i] -= L[i][k] * Z[k];
		}
		Z[i] /= L[i][i];
	}
}

void SqEliminate() {
	for (int i = 0; i < n; i++) {
		// Lii 计算
		L[i][i] = A[i][i];
		for (int k = 0; k < i; k++) {
			L[i][i] -= L[i][k] * L[i][k];
		}
		L[i][i] = sqrt(L[i][i]);
		U[i][i] = L[i][i];

		// Uij计算
		for (int j = i + 1; j < n; j++) {
			U[i][j] = A[i][j];
			for (int k = 0; k < i; k++) {
				U[i][j] -= L[i][k] * U[k][j];
			}
			U[i][j] /= L[i][i];
		}

		// 将计算的U值赋给这一列的所有l
		for (int k = i; k < n; k++) {
			L[k][i] = U[i][k];
		}

		// Zi计算
		Z[i] = B[i];
		for (int k = 0; k < i; k++) {
			Z[i] -= L[i][k] * Z[k];
		}
		Z[i] /= L[i][i];
	}
}

void mainEliminate() {
	// 寻找主元素
	for (int i = 0; i < n; i++) {
		int maxEle = 0;
		for (int j = 1; j < n; j++) {
			if (A[j][i] > A[maxEle][i]) {
				maxEle = j;
			}
		}

		for (int k = 0; k < n; k++) {
			swap(A[i][k], A[maxEle][k]);
		}
		swap(B[i], B[maxEle]);
		swap(maxElement[i], maxElement[maxEle]);
	}

	for (int i = 0; i < n; i++) {
		// Lij计算
		L[i][i] = 1;

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
