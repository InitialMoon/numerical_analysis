# 数值分析上机实验报告

[TOC]



## 概述

本报告中记录了本人在此次数值分析上机实验中完成的所有数值计算方法，具体包括了每种方法的代码说明，以及实验所用的例题验证环节，验证环节将使用课件中的例题，本次实验采用C++完成。

## 正文

### 一、方程组的迭代解法

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
		xn = interator(x0);
		x0 = interator(xn);
	}
	cout.precision(n);
	cout << "该方程的解是：" << xn << endl;
	cout << "迭代次数是：" << interNum << endl;
	return 0;
}
```

##### 验证

运行结果截图如下

![image-20221106164505896](image-20221106164505896.png)

与课件中的结果相一致，艾特肯法验证成功

##### 数据收集

在这个简易的程序中我设置了初值的输入以及计算精度的需求入口，我们也可以通过输入其他的初值以及计算精度进行对比，发现其中规律

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解           | 迭代次数 |
| -------- | --------- | ----------------------- | ------------ | -------- |
| 1        | 0.5       | 5                       | 0.56714      | 4        |
| 2        | 0.5       | 7                       | 0.5671433    | 28       |
| 3        | 0.5       | 10                      | 0.5671432927 | 696      |
| 4        | 0         | 5                       | 0.56714      | 4        |
| 5        | 1000      | 5                       | 0.56714      | 6        |
| 6        | 100000000 | 5                       | 0.56714      | 6        |

##### 实验结论

经过简单的实验，我们发现艾特肯法在这个方程组求解的过程中，初值的设定对于迭代计算次数影响不大；而若要提高计算精度，则需要的迭代次数增长速度会很快，从实验结果来看，艾特肯法是一种大范围收敛的迭代公式，他在初值与真解相差很大时，仍能快速收敛至解的附近，但是若想要使用艾特肯法进行高精度计算时，就比较吃力了。

#### 1.2牛顿迭代法

以习题例2.10为例

>使用牛顿迭代法解方程$x = e^{-x}$，要求精度 $\epsilon < 0.5 *10^{-5} $

$$
f(x) = xe^x - 1\\
f'(x) = e^x(1 + x)\\
迭代公式为
x_{x+1} = x_n - \frac{x_ne^{x_n} - 1}{e^{x_n}(1 + x_n)}\\
= x_n - \frac{x_n - e^{-x_n}}{1+x_n}
$$

代码实现

```c++
```



### 总结

