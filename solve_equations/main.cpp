#include <iostream>
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

void input();
void select();
void back();

int main() {
	input();
	select();
}

void input() {
	cout << "其输入方程组的秩";
	cin >> n;
	cout << "请输入方程组的增广矩阵" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
		}
		cin >> B[i];
	}
}

void select() {
	cout << "请选择你想使用的方法" << endl;
	cout << "1.高斯消元法" << endl;
	cout << "2.克劳特消元法" << endl;
	cout << "3.平方根法" << endl;
	cout << "4.列主元素法" << endl;
	cin >> methodType;
}

// 回带上三角矩阵过程
void back() {

}