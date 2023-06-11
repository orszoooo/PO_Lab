#include "SkokJednostkowy.h"

void SkokJednostkowy::setAmplituda(double amplituda)
{
    s_amplituda = amplituda;
}

void SkokJednostkowy::setCzasSkoku(int czasSkoku)
{
    s_czasSkoku = czasSkoku;
}

double SkokJednostkowy::getAmplituda()
{
    return s_amplituda;
}

int SkokJednostkowy::getCzasSkoku()
{
    return s_czasSkoku;
}

double SkokJednostkowy::symuluj(int t)
{
    return czyAktywny(t) ? (t < s_czasSkoku) ? 0.0 : s_amplituda : 0.0;
}

SkokJednostkowy::SkokJednostkowy(double amplituda, int czasSkoku, int start, int koniec)
    : Sygnal(start, koniec), s_amplituda(amplituda), s_czasSkoku(czasSkoku)
{
}
