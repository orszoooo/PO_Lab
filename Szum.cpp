#include "Szum.h"

double Szum::symuluj(int t)
{
    return (czyAktywny(t) ? s_generatorSzumu(generator) : 0.0) + SygnalDekorator::symuluj(t);
}

Szum::Szum(Sygnal* s, int start, int koniec)
    : SygnalDekorator(s, start, koniec)
{
}
