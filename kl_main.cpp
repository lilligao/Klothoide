#include <iostream>
#include <fstream>
#include "Klothoide.h"
#include "Koord2d.h"
#include "punkt.h"
 
using namespace std;

typedef struct _data { punkt P1; punkt P2; punkt P3; double one; double n; double m; double R; double dl; } werte;
typedef struct _l_zw { vector <double> l_1_zw; vector <double> l_k_zw; 	vector <double> l_2_zw; } l_zw;

void loadFile(werte* );
void zwischenschritte(l_zw* , vector<double> , werte* );

int main() {
	werte w;

	// Einlesen der Datei
	loadFile(&w);

	try
	{
		//  Winkel gamma und gamma'
		double gamma_strich = riwi(w.P2, w.P3) - riwi(w.P2, w.P1);
		double gamma = Pi - gamma_strich;

		// Berechnung von alpha aus gamma, n und m
		double alpha = gamma * 2. * w.n / (1 + w.m + 2 * w.n);
		double tau_1 = alpha / (2 * w.n);
		double tau_2 = w.m / w.n * alpha / 2.;

		// Berechnung der Bogenlaengen aus R,alpha,n und m
		double BL_K = w.R * alpha;
		double BL_1 = BL_K / w.n;
		double BL_2 = BL_K * w.m / w.n;
		vector<double> BL = { BL_1, BL_K, BL_2 };

		// Spannmasse zwischen den Punkten
		cout << "Bogenlänge Klothoid 1: " << BL_1 << endl;
		cout << "Bogenlänge Kreisstueck: " << BL_K << endl;
		cout << "Bogenlänge Klothoid 2: " << BL_2 << endl;
		cout << "gesamte Bogenlänge: " << BL_1 + BL_K + BL_2 << endl;

		// Bogenzwischenpunkte ueber die gesamte Bogenlaenge
		l_zw l_zwischen;
		zwischenschritte(&l_zwischen, BL, &w);

		// Berechnung der Klothoiden-Parameter A
		double A1 = sqrt(BL_1* w.R);
		double A2 = - sqrt(BL_2* w.R);

		// Bogenlaegen der Einheitsklothoide
		double l_1 = BL_1 / A1;
		double l_2 = BL_2 / A2;

		// Klothoide KI und KII
		Klothoide k1 = Klothoide(A1);
		Klothoide k2 = Klothoide(A2);

		// Klothoideendendpunkte
		Koord2d e1_1 = k1.getPkt_l(l_1);
		Koord2d e2_2 = k2.getPkt_l(fabs(l_2));


		// Klothoideendzwischenpunkte
		// Klothoide I im System I
		vector<punkt> k1_zw;

		for (int i = 0; i < l_zwischen.l_1_zw.size(); i++) {
			k1_zw.push_back(punkt(to_string(100 + i), k1.getPkt_l(l_zwischen.l_1_zw[i] / A1)));
		}

		// Klothoide II im System II
		vector<punkt> k2_zw;

		for (int i = 0; i < l_zwischen.l_2_zw.size(); i++) {
			k2_zw.push_back(punkt(to_string(300 + i), k2.getPkt_l(l_zwischen.l_2_zw[i] / fabs(A2))));
		}

		// Kreis im System I 
		Koord2d Km_1 = k1.getKM_r(w.R);                         // Kreismittelpunkt in System I
		double t_0 = riwi(Km_1, e1_1);                          // Richtungswinkel von Kreismittel M zu E1
		vector<punkt> kreis_zw;

		for (int i = 0; i < l_zwischen.l_k_zw.size(); i++) {
			kreis_zw.push_back(punkt(to_string(200 + i), polanh(Km_1, w.R, t_0 - l_zwischen.l_k_zw[i] / w.R)));
		}

		Koord2d e2_1 = polanh(Km_1, w.R, t_0 - BL_K / w.R);     // Kreisendpunkte E2

		// Kreis in System II
		Koord2d Km_2 = k2.getKM_l(BL_2);                        // Kreismittelpunkt in System II

		// Klothoid II in System I
		vector<punkt> k2_1 = trafo(e2_2, Km_2, e2_1, Km_1, k2_zw);
		
		// Bogenanfangspunkte KA1 und KA2 in System I
		Koord2d KA1_1 = k1_zw[0];
		Koord2d KA2_1 = k2_1[k2_1.size()-1];

		// KA1 und KA2 berechnet im GK-System
		double s = KA2_1.dist_to(KA1_1);
		double beta = Pi / 2 - riwi(KA1_1, KA2_1);

		double K2P2 = s / sin(gamma_strich)*sin(beta);           // Sinus-Satz
		double K1P2 = s / sin(gamma_strich)*sin(beta + gamma_strich);

		Koord2d KA1_GK = polanh(w.P2, K1P2, riwi(w.P2, w.P1));
		Koord2d KA2_GK = polanh(w.P2, K2P2, riwi(w.P2, w.P3));

		punkt KA1 = punkt("KA1", KA1_GK);
		punkt KA2 = punkt("KA2", KA2_GK);

		// Bogenendpunkte in System I in Vektor hinzufuegen
		punkt KE1 = punkt("KE1", e1_1);
		punkt KE2 = punkt("KE2", e2_1);

		k1_zw.push_back(KE1);
		k2_1.push_back(KE2);

		// alle Punkte in System I
		vector<punkt> punkte_I;
		punkte_I.insert(punkte_I.end(), k1_zw.begin(), k1_zw.end());
		punkte_I.insert(punkte_I.end(), kreis_zw.begin(), kreis_zw.end());
		punkte_I.insert(punkte_I.end(), k2_1.begin(), k2_1.end());

		// Transformierung aller Punkte ins GK-System 
		vector<punkt> punkte_gk = trafo(KA1_1, KA2_1, KA1_GK, KA2_GK, punkte_I);
		punkte_gk.push_back(KA1);
		punkte_gk.push_back(KA2);
		
		// Ausgabe der Datei
		ofstream fs_out;
		fs_out.open("Punkteliste.txt");

		if (!fs_out.is_open())
			cout << "Kein Zugriff auf Datei" << endl;

		else {
			for (int i = 0; i < punkte_gk.size(); i++) {
				fs_out << punkte_gk[i];
			}
		}
		fs_out.close();

	}
	catch (const std::exception&)
	{
		// Exception
		cout << "FEHLER!!!" << endl;
	}
	
	system("pause");
	return 0;
}

// Einlesen der Datei
void loadFile(werte* w)
{
	ifstream rein;

	rein.open("Klothoide_G4.dat");
	if (!rein.is_open())
		cout << "Datei nicht gefunden!" << endl;
	else
	{
		rein >> w->P1;
		rein >> w->P2;
		rein >> w->P3;
		rein >> w->one >> w->n >> w->m;
		rein >> w->R;
		rein >> w->dl;
	}
}

// Bogenlaenge der Zwischenpunkte ueber die gesamte Bogenlaenge im Abstand dl
void zwischenschritte(l_zw* l_zwischen, vector<double> BL, werte* w)
{
	double l_counter = 0;
	
	// Bogenlaenge der Zwischenpunkte der Klot. 1 in System I
	while (l_counter <= BL[0])
	{
		l_zwischen->l_1_zw.push_back(l_counter);
		l_counter += w->dl;
	}

	// Bogenlaenge der Zwischenpunkte der Kreisbogen in Bezug auf KE1
	l_counter -= BL[0];

	while (l_counter <= BL[1])
	{
		l_zwischen->l_k_zw.push_back(l_counter);
		l_counter += w->dl;
	}

	// Bogenlaenge der Zwischenpunkte der Klot. 2 in System II
	l_counter -= BL[1];

	while (l_counter <= BL[2])
	{
		l_zwischen->l_2_zw.push_back(BL[2] - l_counter);
		l_counter += w->dl;
	}
	
	l_zwischen->l_2_zw.push_back(0);    // Anfangspunkt KA2
}