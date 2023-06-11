#include "Sygnal.h"

bool Sygnal::czyAktywny(int t)
{
    return (t >= s_start && t <= s_koniec) ? true : false;
}

void Sygnal::setStart(int start)
{
    s_start = start;
}

void Sygnal::setKoniec(int koniec)
{
    s_koniec = koniec;
}

int Sygnal::getStart()
{
    return s_start;
}

int Sygnal::getKoniec()
{
    return s_koniec;
}

Sygnal::Sygnal(int start, int koniec) : s_start(start), s_koniec(koniec)

{
}
