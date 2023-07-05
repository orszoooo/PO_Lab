#pragma once
#include "ObiektSISO.h"

class Komponent : public ObiektSISO {
private:
	static int liczba_objektow;
	int id;
public:
	virtual void dodaj(Komponent* komp);
	virtual void usun();
	virtual double symuluj(double u) override;

	int getID() {
		return id;
	}

	Komponent() {
		id = ++liczba_objektow;
	}
	virtual ~Komponent() {};
};

