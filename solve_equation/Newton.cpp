#include <cmath>
#include "constFeild.h"

// µü´úº¯Êý
double NewtonF(double x) {
	double res = 0;
	res = x - (x - pow(e, -x)) / (1 + x);
	return res;
}

double NewtonInterator(double xn, int& interNum) {
	interNum++;
	xn = NewtonF(xn);
	return xn;
}

