# 数值分析上机实验报告

[TOC]



## 概述

本报告中记录了本人在此次数值分析上机实验中完成的所有数值计算方法，具体包括了每种方法的代码说明，以及实验所用的例题验证环节，验证环节将使用课件中的例题，本次实验采用C++完成。

## 正文

### 一、方程的迭代解法

#### 1.1 艾特肯法 

以习题2.6为例：

> 使用艾特肯法解方程$x = e^{-x}$，要求精度 $\epsilon < 0.5 *10^{-5} $

迭代公式取$x_{n + 1} = e^{-x_n}$
$$
q = {e^{-x}}' = -e^{-x}\\
x \in [0.5, 0.6]
$$
因此易得$|q| < 1$ 次迭代公式收敛

##### 编程实现

```c++
#include <iostream>
#include <cmath>
using namespace std;

const float e = 2.718281828; // 对数常量
double eps = 5e-6;// 默认误差范围
double ans = 0;
int interNum = 0; // 迭代次数

// 迭代函数
double AitkenF(double x) {
	return pow(e, -x);
}

double Aitkeninterator(double xn) {
	interNum++;
	double yn = AitkenF(xn);
	double zn = AitkenF(yn);
	double xn1 = (zn * xn - yn * yn) / (zn + xn - 2 * yn);
	return xn1;
}

int main() {
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
		xn = AitkenInterator(x0);
		x0 = AitkenInterator(xn);
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}
```

运行结果截图如下

![image-20221106164505896](image-20221106164505896.png)

结果正确

#### 1.2牛顿迭代法

以习题例2.10为例

>使用切线法解方程$x = e^{-x}$，要求精度 $\epsilon < 0.5 *10^{-5} $

$$
f(x) = xe^x - 1\\
f'(x) = e^x(1 + x)\\
迭代公式为
x_{x+1} = x_n - \frac{x_ne^{x_n} - 1}{e^{x_n}(1 + x_n)}\\
= x_n - \frac{x_n - e^{-x_n}}{1+x_n}
$$

代码实现

```c++
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

```

![image-20221106181655434](image-20221106181655434.png)

结果正确

#### 对比与总结

下面对这两种迭代方法进行简单的对比，在这个程序中，我将两种方程的解法合并在了同一个接口下面，通过选择不同的编号使用不同的方法进行迭代计算

从精度要求和初值两方面进行了考察，在输入不同的初值和精度要求时记录了迭代次数以及精确解

#### 数据收集

##### 艾特肯法

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解           | 迭代次数 |
| -------- | --------- | ----------------------- | ------------ | -------- |
| 1        | 0.5       | 5                       | 0.56714      | 4        |
| 2        | 0.5       | 7                       | 0.5671433    | 28       |
| 3        | 0.5       | 10                      | 0.5671432927 | 696      |
| 4        | 0         | 5                       | 0.56714      | 4        |
| 5        | 1000      | 5                       | 0.56714      | 6        |
| 6        | 100000000 | 5                       | 0.56714      | 6        |

##### 牛顿切线法

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解           | 迭代次数 |
| -------- | --------- | ----------------------- | ------------ | -------- |
| 1        | 0.5       | 5                       | 0.56714      | 4        |
| 2        | 0.5       | 7                       | 0.5671433    | 4        |
| 3        | 0.5       | 10                      | 0.5671432927 | 6        |
| 4        | 0         | 5                       | 0.56714      | 6        |
| 5        | 1000      | 5                       | 0.56714      | 1012     |
| 6        | 100000000 | 5                       | 0.56714      | 10000020 |

#### 实验结论

经过简单的实验，我们发现艾特肯法求解的过程中，初值的设定对于迭代计算次数影响不大；而若要提高计算精度，则需要的迭代次数增长速度会很快，而牛顿切线法则相反，从实验结果来看，艾特肯法是一种==大范围收敛==的迭代公式，他在初值与真解相差很大时，仍能快速收敛至解的附近，但是若想要使用艾特肯法进行高精度计算时，就比较吃力了

而牛顿迭代法则正好相反，在精度要求高的时候，他仍能快速迭代到精度要求范围，但是若是初值选取的不好，则需要经过大量迭代才能达到要求，所以是一种==小范围收敛==的迭代公式，这与课上所学是完全一致的，见下图PPT截图（。

<p  align="center"><img src="image-20221106193326314.png" alt="image-20221106193326314" style="zoom:50%;" /></p>

所以就想老师上课所说的那样，这两种迭代方式没有谁绝对的好谁绝对的坏，重要的是看使用的场景，而在一般情况下，显然我们更希望两种情况都能应对，也就是说只要我们将两者进行结合就好，在离初值比较远的时候，就使用大范围收敛的迭代公式，而在精度达到一定范围了之后，再换用另一种迭代公式就好了，我们可以将两种迭代公式进行对接，实现更加健壮稳定高效求解算法。

#### 改进

根据上面分析得出的结论，牛顿切线法是一个小范围收敛的迭代法，艾特肯法是一个大范围收敛的迭代法，因此，我将上面的程序进行了进一步的封装，并新增了第三个接口”牛顿-艾特肯混合版”这个新的接口支持在迭代过程中自行检测目前的收敛位置，并根据距离真值附近的距离进行选择，当离真值远（>0.1)时选择艾特肯法，而小于0.1后选择牛顿法，这样就可以实现取长补短的适应性更强的迭代计算了

代码实现

这里只列出封装后的主函数，迭代函数在上面两段代码中有罗列，不再重复

```c++
#include <iostream>
#include "Aitken.h"
#include "Newton.h"

int type = 0;
double eps = 5e-6;// 默认误差范围
double ans = 0;
int interNum = 0; // 迭代次数

using namespace std;

int main() {
	double(*interator)(double, int&) = NULL;

	cout << "==迭代法求解方程==" << endl;
	cout << "请根据下面列表选择求解方程使用的方法" << endl;
	cout << "1---艾特肯法" << endl;
	cout << "2---牛顿迭代法" << endl;
	cout << "3---1、2混合健壮版" << endl;

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
	while (abs(xn - x0) > eps) {
		xn = interator(x0, interNum);
		x0 = interator(xn, interNum);
		if (abs(xn - 0.5) < 0.1 && type == 3) {
			// 选择3时才会触发的自动选择功能
			interator = NewtonInterator;
		}
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}
```

#### 1.3 魔改混合法

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解                | 迭代次数 |
| -------- | --------- | ----------------------- | ----------------- | -------- |
| 1        | 100000000 | 15                      | 0.567143290444445 | 6        |

由实验结果可以看到，这种方式确实非常的强大，实现了对初值要求极不严格的情况下，高精度快速迭代到目标精度的解

#### 1.4 弦解法

例题方程同上，下面两段代码封装至上面的主函数框架中，值多加了两个分支

##### 1.4.1 单点弦截法

核心代码如下

```C++
// 迭代函数
double StringF(double x) {
	double res = 0;
	res = x * pow(e, x) - 1;
	return res;
}

// 单点弦解法
double sStringInterator(double xn, double x0, int& interNum) {
	interNum++;
	xn = (x0 * StringF(xn) - xn * StringF(x0)) / (StringF(xn) - StringF(x0));
	return xn;
}
```

##### 1.4.2 双点弦截法

核心代码如下

```c++
// 双点弦解法
double dStringInterator(double xn, double xn_1, int& interNum) {
	interNum++;
	xn = (StringF(xn) * xn_1 - StringF(xn_1) * xn) / (StringF(xn) - StringF(xn_1));
	return xn;
}
```

##### 调用模块

```C++
double x1 = x0;
while (abs(xn - x1) > eps) {
    if (type == 4) {
        x1 = sStringInterator(xn, x0, interNum);
        xn = sStringInterator(x1, x0, interNum);
    }
    if (type == 5) {
        x1 = dStringInterator(xn, x1, interNum);
        xn = dStringInterator(xn, x1, interNum);
    }
}
```



### 二、方程组的迭代解法

#### 2.1 