# 数值分析上机实验报告

报告人：介应奇    1120213081  2022/11/11

授课教师：孙新

[TOC]



## 概述

本报告中记录了本人在此次数值分析上机实验中完成的所有数值计算方法，具体包括

1. 每种方法的代码

   相近的方法会结合在一个接口下，不相近的方法分开单独编译执行

2. 实验所用的例题验证环节

3. 还包含了本人对于某些方法的对比

4. 部分计算方法的改进与结合

     *如迭代解方程时采用表格的方式对不同的输入导致的迭代次数变化做了的分析，并在通过实验得到了相应结论后，对方法的改进*

5. 实验感想

    *一些不方便通过实验表格对比的计算方法的优劣，本人根据自己的理解做了些许解说，或者说是自己在做实验时产生的感想也记录下来了*

验证环节将使用课件中的例题，本次实验全部采用C++完成

## 程序说明

所有的程序均可直接使用Visual Studio 2022打开项目编译执行，不同的计算方法在不同的项目下，但总体在solve_equations解决方案下，可以打开后根据需要执行相应的项目即可，项目测试过程中均需手动根据提示输入相应的数据

> 注：线性方程组的数据在input文件夹下有备用的典型例题，可以直接拿来复制使用

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

##### 数据收集

###### 艾特肯法

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解           | 迭代次数 |
| -------- | --------- | ----------------------- | ------------ | -------- |
| 1        | 0.5       | 5                       | 0.56714      | 4        |
| 2        | 0.5       | 7                       | 0.5671433    | 28       |
| 3        | 0.5       | 10                      | 0.5671432927 | 696      |
| 4        | 0         | 5                       | 0.56714      | 4        |
| 5        | 1000      | 5                       | 0.56714      | 6        |
| 6        | 100000000 | 5                       | 0.56714      | 6        |

###### 牛顿切线法

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解           | 迭代次数 |
| -------- | --------- | ----------------------- | ------------ | -------- |
| 1        | 0.5       | 5                       | 0.56714      | 4        |
| 2        | 0.5       | 7                       | 0.5671433    | 4        |
| 3        | 0.5       | 10                      | 0.5671432927 | 6        |
| 4        | 0         | 5                       | 0.56714      | 6        |
| 5        | 1000      | 5                       | 0.56714      | 1012     |
| 6        | 100000000 | 5                       | 0.56714      | 10000020 |

##### 实验结论

经过简单的实验，我发现艾特肯法求解的过程中，初值的设定对于迭代计算次数影响不大；而若要提高计算精度，则需要的迭代次数增长速度会很快，而牛顿切线法则相反，从实验结果来看，艾特肯法是一种==大范围收敛==的迭代公式，他在初值与真解相差很大时，仍能快速收敛至解的附近，但是若想要使用艾特肯法进行高精度计算时，就比较吃力了

而牛顿迭代法则正好相反，在精度要求高的时候，他仍能快速迭代到精度要求范围，但是若是初值选取的不好，则需要经过大量迭代才能达到要求，所以是一种==小范围收敛==的迭代公式，这与课上所学是完全一致的，见下图PPT截图（。

<p  align="center"><img src="image-20221106193326314.png" alt="image-20221106193326314" style="zoom:50%;" /></p>

所以就想老师上课所说的那样，这两种迭代方式没有谁绝对的好谁绝对的坏，重要的是看使用的场景，而在一般情况下，显然我们更希望两种情况都能应对，也就是说只要我们将两者进行结合就好，在离初值比较远的时候，就使用大范围收敛的迭代公式，而在精度达到一定范围了之后，再换用另一种迭代公式就好了，我们可以将两种迭代公式进行对接，实现更加健壮稳定高效求解算法。

#### 改进

根据上面分析得出的结论，牛顿切线法是一个小范围收敛的迭代法，艾特肯法是一个大范围收敛的迭代法，因此，我将上面的程序进行了进一步的封装，并新增了第三个接口”牛顿-艾特肯混合版”这个新的接口支持在迭代过程中自行检测目前的收敛位置，并根据距离真值附近的距离进行选择，当离真值远（>0.1)时选择艾特肯法，而小于0.1后选择牛顿法，这样就可以实现取长补短的适应性更强的迭代计算了

#### 1.3 魔改混合法

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

| 实验次数 | 初值      | 精度要求（小数点后n位） | 解                | 迭代次数 |
| -------- | --------- | ----------------------- | ----------------- | -------- |
| 1        | 100000000 | 15                      | 0.567143290444445 | 6        |

##### 实验结论

由实验结果可以看到，这种方式确实非常的强大，实现了对初值要求极不严格的情况下，高精度快速迭代到目标精度的解

#### 1.4 弦截法

例题方程同上，下面两段代码封装至上面的主函数框架中，值多加了两个分支，方程推导过程即将牛顿迭代法中的导数用差商来替换，单点弦截法是固定初始值不变的割线斜率，而双点弦就是计算出新的值作为下一个初值$x_0$是不断变化迭代的，公式推导就不再列出

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

调用模块

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

##### 数据收集

###### 单点弦截法

| 实验次数 | 初值 | 精度要求（小数点后n位） | 解                | 迭代次数 |
| -------- | ---- | ----------------------- | ----------------- | -------- |
| 1        | 0.5  | 5                       | 0.56714           | 6        |
| 2        | 0.5  | 15                      | 0.567143290444445 | 14       |
| 3        | 5    | 5                       | 0.56714           | 282      |

###### 双点弦截法

| 实验次数 | 初值 | 精度要求（小数点后n位） | 解                | 迭代次数 |
| -------- | ---- | ----------------------- | ----------------- | -------- |
| 1        | 0.5  | 5                       | 0.56714           | 4        |
| 2        | 0.5  | 15                      | 0.567143290444445 | 6        |
| 3        | 5    | 5                       | 0.56714           | 6        |

##### 实验结论

可以看出二阶的双点弦截法果然比一阶的单点弦截法收敛的要快，在精度和初值范围两方面都有优势是一种较为均衡的迭代解法，都可以快速收敛，而单点弦截法在精度方面比艾特肯法要好，但是没有牛顿斜线法和双点弦截法好。

### 二、线性方程组的直接解法

由于每种方式的计算的基本流程流程的相同的，只是在对UL矩阵的分解过程有所差别，因此先将程序的总体框架放在此处，后续的不同之处纸带$Eliminate$函数，在后面每种具体的方法里在做区分实现就好，程序全部集成在了同一个main函数中，直接执行即可。

具体内容如下

```c++
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
```

#### 2.1 高斯消元法

例题如下：

>$$\begin{cases}
>	-23x_1 + 11x2 + x_3 = 0 \\ 11x_1 - 3 x_2 - 2x_3 = 3 \\ x_1 - 2x_2 + 2x_3 = -1\end{cases}$$

```C++
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
```

运行结果

<img src="image-20221110130620608.png" alt="image-20221110130620608"  />

在取到相应的精度后与课件结果相一致

#### 2.2 克劳特消元法

例题如下：

>$$\begin{cases}
>	3x_1  -x_2 + 4x_3 = 7 \\ -x_1 +2 x_2 - 2x_3 = -1 \\ 2x_1 - 3x_2 + 2x_3 = 0\end{cases}$$

```c++
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
```

运行结果

![image-20221110130904488](image-20221110130904488.png)



#### 对比与总结

##### 对比

在写这两种方式的代码的时候，我发现克劳特消元法是简化了$L[i][j](i > j)$和$U[i][i]$的系数的计算，因为要想消掉下面一行的$x_i$就一定要和乘和下面$x_i$相同的系数，而又因为$L[i][i]=A[i][i]$使得$U[i][i] = 1$，所以$L[i][j] = A[i][j]$，从而达到简化计算$L$矩阵的目的，通用的消元框架，对于克劳特消元法，其中有$n$次不必要的除法运算，对于高斯消元法也同理，只不过一个是在计算U矩阵时简单，另一个是在计算L矩阵时简单，这里的简单的意思是可以优化掉n次除法，减少舍入误差的积累，将这里的发现利用起来，可以进一步的节省运算资源，同时提高运算精度,经过对于这两个方法的编程实现过程进行对比，我了解了克劳特消元法采用这种将$U[i][i]$变为1的计算过程的意义，高斯消元法和克劳特消元法两种方法的不同主要体现在了分解后的LU矩阵上，高斯消元法的$L[i][i]$会全是1，而相应的克劳特消元法的第一列元素值会全是1，计算Z向量的时候，高斯消元法可以不做除法，因为$L[i][i]$是1，而克劳特需要做，因为他的$L[i][i]$不是1，但是这不意味着高斯消元法计算Z向量的数值就更加精确，因为他在对于U矩阵除法的舍入过程中产生的误差会影响到Z，对于Z的除法舍入误差产生的误差事实上还是相同的。

##### 总结

也就是说，对于解的精确度来说，两者的有效程度是相同的，但是对于计算出的UL矩阵两者的精确程度是不同的，一个是可以使分解出的L更精确，一个是可以使分解出的U矩阵更精确，因为各自相比于另一种方法少做一次除法，所以我们对于这两种方法的选择，可以从对于分解后的UL矩阵的需求入手，使用不同的方式，我认为这是两种办法不同的方面，经过这次实验，我更加深刻的体会到了这两种方法的区别与意义，以及可能会有的不同的应用场景，而不只是停留于只是$L[i][i]$的计算方式不同这一层面。

#### 2.3 平方根法

例题如下：

>$$\begin{cases}
>	1x_1  +0.42x_2 + 0.54x_3 = 0.3 \\ 0.42x_1 +x_2 +0.32x_3 = 0.5 \\ 0.54x_1 - 0.32x_2 + x_3 = 0.7\end{cases}$$

平方根法从上到下的消元过程与前两种略有不同，利用了系数矩阵的对称性可以减少一半的计算量，消元过程函数如下$SqEliminate$

```C++
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

```

运行结果如下：

![image-20221110150019793](image-20221110150019793.png)

与课件中结果一致

#### 2.4 列主元素法

例题如下：

>$$\begin{cases}
>	1x_1  +0.42x_2 + 0.54x_3 = 0.3 \\ 0.42x_1 +x_2 +0.32x_3 = 0.5 \\ 0.54x_1 - 0.32x_2 + x_3 = 0.7\end{cases}$$

```C++
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
```

运行结果如下：

![image-20221110182449330](image-20221110182449330.png)

##### 实验结论

在取到相应的精度后与课件结果相一致，在使用了主元素法后分解的UL矩阵并没有因为分子过小而使得误差被放大，是正确的结果，如没有使用主元素法，而是直接使用高斯消元法的话，就会出现如下结果：

![image-20221110183913315](image-20221110183913315.png)

可以看见，ULZ三个分解结果都因为误差被放大而不可靠了，由此可见主元素法的意义。

### 三、线性方程组的迭代解法

使用同一道例题好进行方法的对比

例题如下：

>$$\begin{cases}
>	20x_1  +20x_2 + 3x_3 = 24\\ 1x_1 +8x_2 +x_3 = 12 \\ 2x_1 - 3x_2 + 15x_3 = 30\end{cases}$$

两种方法主题框架相同，值有代入时使用的是已有k+1次的还是过去k次的差别，因此合并为同一个main函数中实现，主函数如下

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXSIZE = 100;
int n = 0;
int InteratorNum = 0;// 记录迭代次数
double eps = 1e-5;// 误差限
double e = 1e2; // 计算过程中不断变化的用于测量误差的数
int t = 0;
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
	cout << "请输入期望的误差限：";
	cin >> t;
	eps = pow(10, -t);
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

void solve() {
	// 计算迭代公式的系数
	for (int i = 0; i < n; i++) {
		double aa =  - A[i][i];
		for (int j = 0; j < n; j++) {
			if (i != j) {
				F[i][j] = A[i][j] / aa;
			}
		}
		F[i][n] = B[i] / -aa;
	}
	// 开始迭代计算
	// e是计算过程中的最大误差，和上次迭代值之间的，这里只是写一个很大的数防止一开始就坏掉
	while (eps < e) {
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
	cout.precision(t);
	cout << "方程的解是：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << X0[i] << endl;
	}
	cout << "迭代次数：" << InteratorNum << endl;
}
```

#### 3.1 雅克比迭代法

```C++
// Jacobi迭代法
void Jacobi() {
	InteratorNum++;
	for (int i = 0; i < n; i++) {
		a[i] = F[i][n];
		for (int j = 0; j < n; j++) {
			if (i != j) {
				a[i] += F[i][j] * b[j];
			}
		}
		e = abs(a[i] - b[i]);
	}
}
```

输入对应的参数，运行结果如下：

![image-20221110230709367](image-20221110230709367.png)

#### 3.2 高斯—赛德尔迭代法

```C++
void Guess_Seidel() {
	InteratorNum++;
	for (int i = 0; i < n; i++) {
		a[i] = F[i][n];
		for (int j = 0; j < i; j++) {
			if (i != j) {
				a[i] += F[i][j] * a[j];
			}
		}
		for (int j = i; j < n; j++) {
			if (i != j) {
				a[i] += F[i][j] * b[j];
			}
		}
		e = abs(a[i] - b[i]);
	}
}
```

输入对应的参数，运行结果如下：

![image-20221110230754768](image-20221110230754768.png)

#### 实验结论

首先，结果与课件中的结果相同实验结果与理论相符，除此之外，我特意加入了误差限要求入口，以作显著的动态对比，时间原因，我这里就不列表格呈现了（有兴趣读者的话可以直接去运行程序亲自看看结果，相应的程序输入我放在了input文件夹下面，或是直接在项目的资源文件里找到）可以看到，高斯赛德尔迭代法确实比简单的雅克比迭代法的收敛速度要快，与理论相符，但两者都可以较为快速的解出所需的高精度的方程组的解，并且随精度提高的过程，迭代次数增速并不很快。

### 四、插值法

拉格朗日和牛顿差商法的思路差别比较大，因此就分成两个架构来做，不做合并了

#### 4.1 牛顿基本差商公式

例题

> x = 1,4,9的平方根值，求$7^{1/2}$

使用了牛顿前插公式，后插公式也同理，只要使用靠下侧的差商表P的值就好，代码如下

```c++
// 牛顿基本差商公式
#include <iostream>
const int MAXSIZE = 100;
int N = 0;
double xn = 0;
double X[MAXSIZE] = { 0 };
double Y[MAXSIZE] = { 0 };
double P[MAXSIZE][MAXSIZE] = { 0 };
double res = 0;
using namespace std;

void input() {
	cout << "请输入插值节点的个数:";
	cin >> N;
	cout << "请按照x,y一组一组的顺序输入x,y值" << endl;
	for (int i = 0; i < N; i++) {
		cout << "第" << i << "组" << ":";
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

// count代表插值层数
void interpolate(int count) {
	int value = 1;
	for (int i = 0; i < count; i++) {
		for (int j = i; j < count; j++) {
			double Quotient = (P[j + 1][i] - P[j][i]) / (X[j + 1] - X[j + 1 - value]);
			P[j + 1][i + 1] = Quotient;
		}
		value += 1;
	}
}

void front_solve() {
	double calcValue = 0, temp = 1;
	int j = 0;
	for (int i = 0; i < N; i++) {
		temp = 1;
		for (int j = 0; j < i; j++) {
			temp *= (xn - X[j]);
		}
		temp *= P[i][i];
		calcValue += temp;
	}
	res = calcValue;
}

int main() {
	input();
	for (int i = 0; i < N; i++) {
		P[i][0] = Y[i];
	}
	interpolate(N);
	front_solve();
	output();
}
```

运行结果如下，答案正确

![image-20221111011226145](image-20221111011226145.png)



#### 4.2 拉格朗日插值法

例题

> 用拉格朗日插值公式计算x=1.4的函数近似值
>| x    | 1.45 | 1.36 | 1.14 |
>| ---- | ---- | ---- | ---- |
>| y    | 3.14 | 4.15 | 5.56 |

由于拉格朗日插值法代码如下

```c++
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
```

运行结果如下

![image-20221111012631852](image-20221111012631852.png)

与课件中的一致，验证成功

#### 实验结论

这两种插值的方式都可以得到近似解，但是拉格朗日插值公式不需要构建查商表，我个人感觉编程实现更加简单，虽然公式看起来比牛顿基本差商要短，但是编程实现却正好相反，在实际使用过程中，两种插值均需要使用余项估计出误差上界。
