#include "SkokJednostkowy.h"

double SkokJednostkowy::symuluj(int t)
{
    return czyAktywny(t) ? (t < s_czasSkoku) ? 0.0 : s_amplituda : 0.0;
}

SkokJednostkowy::SkokJednostkowy(double amplituda, int czasSkoku, int start, int koniec)
    : Sygnal(start, koniec), s_amplituda(amplituda), s_czasSkoku(czasSkoku)
{
}
