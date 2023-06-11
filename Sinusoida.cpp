#include <numbers>

#include "Sinusoida.h"

void Sinusoida::setAmplituda(double amplituda)
{
	s_amplituda = amplituda;
}

void Sinusoida::setOkres(int okres)
{
	s_okres = okres;
}

double Sinusoida::getAmplituda()
{
	return s_amplituda;
}

int Sinusoida::getOkres()
{
	return s_okres;
}

double Sinusoida::symuluj(int t)
{
	return (czyAktywny(t) ? (s_amplituda * sin((2*std::numbers::pi)/s_okres * t)) : 0.0) + SygnalDekorator::symuluj(t);
}


Sinusoida::Sinusoida(Sygnal* s, double amplituda, int okres, int start, int koniec)
	: SygnalDekorator(s, start, koniec), s_amplituda(amplituda), s_okres(okres)
{
}
