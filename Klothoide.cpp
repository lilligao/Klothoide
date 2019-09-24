#include "Klothoide.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>



Koord2d Klothoide::getPkt_l(double l)
{
	double y, x;
	y = l * (1. - pow(l,4) * ((1. / 40.) - (pow(l,4) / 384.) * ((1. / 9.) - (pow(l,4) / 1560.))));
	x = (pow(l,3) / 6.) * (1. - pow(l,4) * (1. / 56.) - (pow(l,4) / 640.) * ((1. / 11.) - (pow(l,4) / 2520.)));

	Koord2d point(y * fabs(A) , x * A);
	return point;
}

Koord2d Klothoide::getKM_l(double l)
{
	double tau = pow(l, 2) / (2 * pow(A, 2));
	double R = 0.5 * l / tau;
	double t;

	if (A>=0)
		t = 2 * M_PI - tau;
	else 
		t = M_PI + tau;

	Koord2d E = getPkt_l(fabs(l / A));
	Koord2d M = polanh(E, R, t);

	return M;
}

Koord2d Klothoide::getKM_r(double r)
{
	double tau = pow(A, 2) / (2 * pow(r, 2));
	double BL = tau * 2 * r;
	double t;

	if (A >= 0)
		t = 2 * M_PI - tau;
	else
		t = M_PI + tau;

	Koord2d E = getPkt_l(fabs(BL / A));
	Koord2d M = polanh(E, r, t);

	return M;
}