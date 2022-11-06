#include <cmath>
#include "constFeild.h"

// µü´úº¯Êý
double StringF(double x) {
	double res = 0;
	res = x * pow(e, x) - 1;
	return res;
}

double dStringInterator(double xn, double xn_1, int& interNum) {
	interNum++;
	xn = (StringF(xn) * xn_1 - StringF(xn_1) * xn) / (StringF(xn) - StringF(xn_1));
	return xn;
}

double sStringInterator(double xn, double x0, int& interNum) {
	interNum++;
	xn = (x0 * StringF(xn) - xn * StringF(x0)) / (StringF(xn) - StringF(x0));
	return xn;
}
