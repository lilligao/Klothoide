#ifndef punkt_h_included
#define punkt_h_included

#include <string>
#include "Koord2d.h"
#include <vector>

using namespace std;

const int PNRMAXLEN = 12;

class punkt : public Koord2d
{
private:
	string pktnr;
public:
	punkt(string punktnummer = "noname", double ykoo = 0., double xkoo = 0.) :
		pktnr(punktnummer), Koord2d(ykoo, xkoo) {}
	punkt(string punktnummer, Koord2d k2d) :
		pktnr(punktnummer), Koord2d(k2d) {}

	void setpnr(string pnr) { pktnr = pnr;}
	string getpnr() const { return pktnr; }

	void print(ostream& os = cout);
	bool read(istream& is = cin);

};

istream& operator >> (istream& is, punkt& p);
ostream& operator << (ostream& os, punkt p);

vector <punkt> trafo(Koord2d, Koord2d, Koord2d, Koord2d, vector <punkt>);

#endif // !punkt_h_included
