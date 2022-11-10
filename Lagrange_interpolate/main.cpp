#include <iostream>
using namespace std;
const int MAXSIZE = 100;
double X[MAXSIZE] = { 0 };
double Y[MAXSIZE] = { 0 };
int N = 0;
double res = 0;
double xn = 0;

void input() {
	cout << "请输入插值节点的个数:";
	cin >> N;
	cout << "请按照x,y一组一组的顺序输入x,y值" << endl;
	for (int i = 0; i < N; i++) {
		cout << "第" << i + 1 << "组" << ":";
		cin >> X[i] >> Y[i];
		cout << "x" << i << "=" << X[i] << endl;
		cout << "y" << i << "=" << Y[i] << endl;
	}
	cout << "插值点：" << endl;
	cin >> xn;
}

void output() {
	cout << "插值结果:" << res << endl;
}

int main() {
	input();
	for (int i = 0; i <= N; i++) {
		double temp1 = 1;
		double temp2 = 1;
		for (int j = 0; j < N; j++) {
			if (i != j) {
				temp1 *= (xn - X[j]);
				temp2 *= (X[i] - X[j]);
			}
		}
		res += temp1 / temp2 * Y[i];
	}
	output();
}