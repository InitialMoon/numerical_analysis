#include "constFeild.h"
#include <cmath>
#include <iostream>

using namespace std;

double eps = 5e-6;// 默认误差范围
double ans = 0;
int interNum = 0; // 迭代次数

// 迭代函数
double F(double x) {
	return pow(e, -x);
}

double interator(double xn) {
	interNum++;
	double yn = F(xn);
	double zn = F(yn);
	double xn1 = (zn * xn - yn * yn) / (zn + xn - 2 * yn);
	return xn1;
}

int Aitken() {
	double x0 = 0.5; //初值
	double xn = 0.6; // 范围最末位置
	int n = 0; // 存储用户输入精度
	cout << "你可以尝试输入不同的初值进行计算对比" << endl;
	cout << "请输入初值（提示：解区间为0.5-0.6）：" ;
	cin >> x0;
	cout << endl;
	cout << "输入您想要的精度（您需要以0.5x10的负n次方的形式输入）：n = ";
	cin >> n;
	eps = 0.5 * pow(10, -n);
	while (abs(xn - x0) > eps) {
		xn = interator(x0);
		x0 = interator(xn);
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}