#include <iostream>
#include <cmath>
#include "constFeild.h"

using namespace std;


double eps = 5e-6;// 默认误差范围
double ans = 0;
int interNum = 0; // 迭代次数
// 迭代函数
double NewtonF(double x) {
	double res = 0;
	res = x - (x - pow(e, -x)) / (1 + x);
	return res;
}

double NewtonInterator(double xn) {
	interNum++;
	xn = NewtonF(xn);
	return xn;
}

int Newton() {
	double x0 = 0.5; //初值
	double xn = 0.6; // 范围最末位置
	int n = 0; // 存储用户输入精度

	cout << "你可以尝试输入不同的初值进行计算对比" << endl;
	cout << "请输入初值（提示：解区间为0.5-0.6）：" ;
	cin >> x0;

	cout << "输入您想要的精度（您需要以0.5x10的负n次方的形式输入）：n = ";
	cin >> n;

	eps = 0.5 * pow(10, -n);

	while (abs(xn - x0) > eps) {
		xn = NewtonInterator(x0);
		x0 = NewtonInterator(xn);
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}
