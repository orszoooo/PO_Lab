#pragma once
#include "Sygnal.h"

class SygnalDekorator : public Sygnal {
private:
	Sygnal* s_obiektDekorowany;
public:
	double symuluj(int t) {
		return s_obiektDekorowany->symuluj(t);
	};
	SygnalDekorator(Sygnal* s, int start, int koniec) 
		: s_obiektDekorowany(s), Sygnal(start, koniec) {};
};

