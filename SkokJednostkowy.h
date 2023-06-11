#pragma once
#include "Sygnal.h"

class SkokJednostkowy : public Sygnal { //Komponent konkretny
private:
	double s_amplituda;
	int s_czasSkoku;
public:
	void setAmplituda(double amplituda);
	void setCzasSkoku(int czasSkoku);
	
	double getAmplituda();
	int getCzasSkoku();

	double symuluj(int t);
	SkokJednostkowy(double amplituda, int czasSkoku, int start, int koniec);
};

