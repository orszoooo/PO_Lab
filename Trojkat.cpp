#include <numbers>
#include <cmath>

#include "Trojkat.h"

double Trojkat::symuluj(int t)
{
    return (czyAktywny(t) ? (((t % s_okres) < (s_wypelnienie * s_okres)) ? obliczTrojkat(t) : 0.0) : 0.0) + SygnalDekorator::symuluj(t);;
}

double Trojkat::obliczTrojkat(int t) {
    return ((2 * s_amplituda) / std::numbers::pi * std::asin(std::sin((2 * std::numbers::pi) / s_okres * t)));
}

Trojkat::Trojkat(Sygnal* s, double amplituda, int okres, double wypelnienie, int start, int koniec)
    : SygnalDekorator(s, start, koniec), s_amplituda(amplituda), s_okres(okres), s_wypelnienie(wypelnienie)
{
}
