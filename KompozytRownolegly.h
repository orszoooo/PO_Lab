#pragma once

#include "Kompozyt.h"

class KompozytRownolegly : public Kompozyt {
public:
	double symuluj(double u) {
		double y = 0.0;

		for (Komponent* x : pojemnik) {
			y += x->symuluj(u);
		}
		return y;
	}
};