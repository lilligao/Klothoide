#include "Koord2d.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>


void Koord2d::print(ostream& os)
{
	os.flags(ios::right | ios::fixed);
	os.precision(3);
	os << setw(15) << y << " ";
	os << setw(15) << x << " ";
}

bool Koord2d::read(istream& is)
{
	is >> y;
	is >> x;
	if (!(is.good() || is.eof())) return 0;
	return 1;
}

double Koord2d::dist_to(Koord2d k)
{
	double dy = k.y - y;
	double dx = k.x - x;
	return sqrt(dy*dy + dx * dx);
}

double Koord2d::riwi_to(Koord2d k)
{
	double dy = k.y - y;
	double dx = k.x - x;
	return atan2(dy, dx);
}

ostream& operator << (ostream& os, Koord2d  k)
{
	k.print(os);
	return os;
}

istream& operator >> (istream& is, Koord2d& k)
{
	k.read(is);
	return is;
}

Koord2d polanh(Koord2d p, double s, double riwi, double zenit)
{
	double d_h = sin(zenit) * s;
	double y = p.gety() + d_h * sin(riwi);
	double x = p.getx() + d_h * cos(riwi);
	return Koord2d(y, x);
}

Koord2d operator + (Koord2d k1, Koord2d k2)
{
	double y = k1.gety() + k2.gety();
	double x = k1.getx() + k2.getx();
	return Koord2d(y, x);
}

Koord2d operator - (Koord2d k1, Koord2d k2)
{
	double y = k1.gety() - k2.gety();
	double x = k1.getx() - k2.getx();
	return Koord2d(y, x);
}

double riwi(Koord2d k1, Koord2d k2)
{
	Koord2d delta = k2 - k1;
	return atan2(delta.gety(), delta.getx());
}

double rad2gon(double rad)
{
	double gon = rad * RHO;
	while (gon < 0) gon += 400.;
	while (gon >= 400.) gon -= 400.;
	return gon;
}