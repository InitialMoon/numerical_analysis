#include <iostream>
#include "Aitken.h"
#include "Newton.h"

using namespace std;
int main() {
	int type = 0;
	cout << "==迭代法求解方程==" << endl;
	cout << "请根据下面列表选择求解方程使用的方法" << endl;
	cout << "1---艾特肯法" << endl;
	cout << "2---牛顿迭代法" << endl;
	re: // 非法输入后的重新输入读取
	cin >> type;
	switch (type)
	{
	case 1:
		Aitken();
		break;
	case 2:
		Newton();
		break;
	default:
		cout << "你的输入非法，请输入列表中的数组" << endl;
		goto re;
		break;
	}
}