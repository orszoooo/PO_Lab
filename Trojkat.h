#pragma once
#include "SygnalDekorator.h"

class Trojkat : public SygnalDekorator
{
private:
	double s_amplituda;
	int s_okres;
	double s_wypelnienie; //0.0 -> 1.0
public:
	double symuluj(int t);
	double obliczTrojkat(int n);
	Trojkat(Sygnal* s, double amplituda, int okres, double wypelnienie, int start, int koniec);
};

