#include <numbers>
#include <cmath>

#include "Trojkat.h"

void Trojkat::setAmplituda(double amplituda)
{
    s_amplituda = amplituda;
}

void Trojkat::setOkres(int okres)
{
    s_okres = okres;
}

void Trojkat::setWypelnienie(double wypelnienie)
{
    s_wypelnienie = wypelnienie;
}

double Trojkat::getAmplituda()
{
    return s_amplituda;
}

int Trojkat::getOkres()
{
    return s_okres;
}

double Trojkat::getWypelnienie()
{
    return s_wypelnienie;
}

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
