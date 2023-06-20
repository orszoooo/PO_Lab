#pragma once
#include "Kompozyt.h"

class KompozytSzeregowy : public Kompozyt {
public:
	double symuluj(double u) override {
		double y = 0.0;

		for (Komponent* x : pojemnik) {
			y = x->symuluj(u);
			u = y;
		}
		return y;
	}
};