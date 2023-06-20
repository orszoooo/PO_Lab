#include "Kompozyt.h"

void Kompozyt::dodaj(Komponent* komp) {
	pojemnik.push_back(komp);
}
void Kompozyt::usun(Komponent* komp) {
	auto it = find_if(pojemnik.begin(), pojemnik.end(),
		[komp](Komponent* obj) {return obj->getID() == komp->getID(); });
	pojemnik.erase(it);
}

double Kompozyt::symuluj(double u) {
	double y = 0.0;

	for (Komponent* x : pojemnik) {
		y += x->symuluj(u);
	}
	return y;
}