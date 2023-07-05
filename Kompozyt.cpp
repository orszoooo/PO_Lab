#include "Kompozyt.h"

void Kompozyt::dodaj(Komponent* komp) {
	pojemnik.push_back(komp);
}
void Kompozyt::usun() {
	while (!pojemnik.empty()) {
		delete pojemnik.back();
		pojemnik.pop_back();
	}
}

double Kompozyt::symuluj(double u) {
	double y = 0.0;

	for (Komponent* x : pojemnik) {
		y += x->symuluj(u);
	}
	return y;
}