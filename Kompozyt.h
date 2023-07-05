#pragma once
#include <vector>

#include "Komponent.h"

class Kompozyt : public Komponent {
protected:
	std::vector<Komponent*> pojemnik;
public:
	void dodaj(Komponent* komp) override;
	void usun() override;
	virtual double symuluj(double u);

	virtual ~Kompozyt() { }
};