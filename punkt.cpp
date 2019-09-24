#include "punkt.h"
#include <sstream>
#include <iomanip>
#include <math.h>


void punkt::print(ostream& os)
{
	os.setf(ios::left);
	os  << getpnr() << "  ";
	os.flags(ios::right | ios::fixed);
	os.precision(3);
	os << setw(15) << gety();
	os << setw(15) << getx();
	os << endl;
}

bool punkt::read(istream& is)
{
	double ykoo;
	double xkoo;
	string pnr;
	is >> pnr;
	if (!is.good()) return 0;
	setpnr(pnr);
	is >> ykoo;
	is >> xkoo;
	if (!(is.good() || is.eof())) return 0;
	sety(ykoo);
	setx(xkoo);
	return 1;
}



ostream& operator << (ostream& os, punkt  p)
{
	p.print(os);
	return os;
}

istream& operator >> (istream& is, punkt& p)
{
	p.read(is);
	return is;
}

vector <punkt> trafo(Koord2d q1 , Koord2d q2, Koord2d z1, Koord2d z2, vector <punkt> p_q) {
	double sq = q1.dist_to(q2);
	double sz = z1.dist_to(z2);

	double m = sz / sq;
	double phi = riwi(z1, z2) - riwi(q1, q2);

	double a = m * cos(phi);
	double o = m * sin(phi);

	double y_0 = z1.gety() - o * q1.getx() - a * q1.gety();
	double x_0 = z1.getx() - a * q1.getx() + o * q1.gety();


	vector <punkt> p_z = {};

	for (int i = 0; i < p_q.size(); i++) {
		double y = y_0 + p_q[i].getx() * o + p_q[i].gety() * a;
		double x = x_0 + p_q[i].getx() * a - p_q[i].gety() * o;

		p_z.push_back(punkt(p_q[i].getpnr(), y, x));
	}

	return p_z;
}