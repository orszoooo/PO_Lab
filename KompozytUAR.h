#pragma once
#include "Kompozyt.h"
class KompozytUAR : public Kompozyt {
private:
	int s_typ; // 0 - pêtla otwarta, 1 - pêtla zamkniêta
	double s_poprzednie_y;
public:
	double symuluj(double u) override {
		double y = 0.0;

		if (!s_typ) { //Pêtla otwarta
			for (Komponent* x : pojemnik) {
				y = x->symuluj(u);
				u = y;
			}
		}
		else { //Pêtla zamkniêta
			double uchyb = u - s_poprzednie_y;

			for (Komponent* x : pojemnik) {
				y = x->symuluj(uchyb);
				uchyb = y;
			}

			s_poprzednie_y = y;
		}
		
		return y;
	}

	void setTyp(int typ) { s_typ = typ; };

	KompozytUAR(int typ = 0) : s_typ(typ), s_poprzednie_y(0.0) { }
};

