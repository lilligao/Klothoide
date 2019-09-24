// KOORD2D.H  Headerdatei fuer die 2D-Koordinatenklasse

#ifndef Koord2d_h_included
#define Koord2d_h_included


#include <iostream>
#include <cmath>

using namespace std;

const double Pi = acos(-1.);
const double RHO = 200. / Pi;
const double EPS = 1.e-10;

class Koord2d {
private :
	double y;
	double x;
public:
	Koord2d(double ykoo = 0., double xkoo = 0.) :
		y(ykoo), x(xkoo) {}
	double gety() const { return y; }
	double getx() const { return x; }
	void sety(double ykoo) { y = ykoo; }
	void setx(double xkoo) { x = xkoo; }
	
	double dist_to(Koord2d k);
	double riwi_to(Koord2d k);

	virtual void print(ostream& os = cout);
	virtual bool read(istream& is = cin);

};

Koord2d polanh(Koord2d p, double s, double riwi, double zenit = Pi / 2);

ostream& operator << (ostream& os, Koord2d  k);
istream& operator >> (istream& is, Koord2d& k);
Koord2d  operator + (Koord2d k1, Koord2d k2);
Koord2d  operator - (Koord2d k1, Koord2d k2);
double   riwi(Koord2d k1, Koord2d k2);
double   rad2gon(double rad);


# endif // !Koord2d_h_included
