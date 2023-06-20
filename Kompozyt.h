#pragma once
#include <vector>

#include "Komponent.h"

class Kompozyt : public Komponent {
protected:
	std::vector<Komponent*> pojemnik;
public:
	void dodaj(Komponent* komp) override;
	void usun(Komponent* komp) override;
	virtual double symuluj(double u);

	virtual ~Kompozyt() { }
};