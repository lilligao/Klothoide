// KLOTHOIDE.H  Headerdatei fuer die Klothoide-Klasse

#ifndef Klothoide_h_included
#define Klothoide_h_included

#include <iostream>
#include <string>
#include <iostream>
#include "Koord2d.h"
#include <vector>

using namespace std;

class Klothoide {
private:
	double A;
public:
	Klothoide(double A_0 = 0.): A(A_0){}
	Koord2d getKM_l(double l);
	Koord2d getKM_r(double r);
	Koord2d getPkt_l(double l);


};

#endif // !Klothoide_h_included