#include <cmath>
#include "constFeild.h"

// ��������
double AitkenF(double x) {
	return pow(e, -x);
}

double AitkenInterator(double xn, int& interNum) {
	interNum++;
	double yn = AitkenF(xn);
	double zn = AitkenF(yn);
	double xn1 = (zn * xn - yn * yn) / (zn + xn - 2 * yn);
	return xn1;
}
