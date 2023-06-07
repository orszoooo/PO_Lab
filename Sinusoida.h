#pragma once
#include "SygnalDekorator.h"

class Sinusoida : public SygnalDekorator { //Dekorator konkretny
private:
	double s_amplituda;
	int s_okres;
public:
	double symuluj(int t);
	Sinusoida(Sygnal* s, double amplituda, int okres, int start, int koniec);
};

