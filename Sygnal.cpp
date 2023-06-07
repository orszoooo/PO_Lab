#include "Sygnal.h"

bool Sygnal::czyAktywny(int t)
{
    return (t >= s_start && t <= s_koniec) ? true : false;
}

Sygnal::Sygnal(int start, int koniec) : s_start(start), s_koniec(koniec)

{
}
