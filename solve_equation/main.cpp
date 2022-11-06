#include <iostream>
#include "Aitken.h"
#include "Newton.h"
#include "stringm.h"

int type = 0;
double eps = 5e-6;// 默认误差范围
double ans = 0;
int interNum = 0; // 迭代次数

using namespace std;

int main() {
	double(*interator)(double, int&) = NULL;
	bool isString = false;
	cout << "==迭代法求解方程==" << endl;
	cout << "请根据下面列表选择求解方程使用的方法" << endl;
	cout << "1---艾特肯法" << endl;
	cout << "2---牛顿迭代法" << endl;
	cout << "3---1、2混合健壮版" << endl;
	cout << "4---单点弦截法" << endl;
	cout << "5---双点弦截法" << endl;

	re: // 非法输入后的重新输入读取
	cin >> type;
	switch (type)
	{
	case 1:
		interator = AitkenInterator;
		break;
	case 2:
		interator = NewtonInterator;
		break;
	case 3:
		break;
	case 4:
	case 5:
		isString = true;
		break;
	default:
		cout << "你的输入非法，请输入列表中的数组" << endl;
		goto re;
		break;
	}

	double x0 = 0.5; //初值
	double xn = 0.6; // 范围最末位置
	int n = 0; // 存储用户输入精度

	cout << "你可以尝试输入不同的初值进行计算对比" << endl;
	cout << "请输入初值（提示：解区间为0.5-0.6）：" ;
	cin >> x0;
	
	// 选择3时才会触发的自动选择功能
	if (type == 3) {
		if (abs(x0 - xn) < 0.1) {
			interator = NewtonInterator;
		}
		else {
			interator = AitkenInterator;
		}
	}
	cout << "输入您想要的精度（您需要以0.5x10的负n次方的形式输入）：n = ";
	cin >> n;
	eps = 0.5 * pow(10, -n);
	if (!isString) {
		while (abs(xn - x0) > eps) {
			xn = interator(x0, interNum);
			x0 = interator(xn, interNum);
			if (abs(xn - 0.5) < 0.1 && type == 3) {
				// 选择3时才会触发的自动选择功能
				interator = NewtonInterator;
			}
		}
	}
	else {
		double x1 = x0;
		while (abs(xn - x1) > eps) {
			if (type == 4) {
				x1 = sStringInterator(xn, x0, interNum);
				xn = sStringInterator(x1, x0, interNum);
			}
			if (type == 5) {
				x1 = dStringInterator(xn, x1, interNum);
				xn = dStringInterator(x1, xn, interNum);
			}
		}
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}