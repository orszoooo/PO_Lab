#include "Prostokat.h"

void Prostokat::setAmplituda(double amplituda)
{
    s_amplituda = amplituda;
}

void Prostokat::setOkres(int okres)
{
    s_okres = okres;
}

void Prostokat::setWypelnienie(double wypelnienie)
{
    s_wypelnienie = wypelnienie;
}

double Prostokat::getAmplituda()
{
    return s_amplituda;
}

int Prostokat::getOkres()
{
    return s_okres;
}

double Prostokat::getWypelnienie()
{
    return s_wypelnienie;
}

double Prostokat::symuluj(int t)
{
    return (czyAktywny(t) ? (((t % s_okres) < (s_wypelnienie * s_okres)) ? s_amplituda : 0.0) : 0.0) + SygnalDekorator::symuluj(t);
}

Prostokat::Prostokat(Sygnal* s, double amplituda, int okres, double wypelnienie, int start, int koniec)
    : SygnalDekorator(s, start, koniec), s_amplituda(amplituda), s_okres(okres), s_wypelnienie(wypelnienie)
{
}
