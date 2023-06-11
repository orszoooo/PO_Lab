#pragma once
#include "SygnalDekorator.h"

class Prostokat : public SygnalDekorator
{
private:
	double s_amplituda;
	int s_okres;
	double s_wypelnienie; //0.0 -> 1.0
public:
	void setAmplituda(double amplituda);
	void setOkres(int okres);
	void setWypelnienie(double wypelnienie); 

	double getAmplituda();
	int getOkres();
	double getWypelnienie();

	double symuluj(int t);
	Prostokat(Sygnal* s, double amplituda, int okres, double wypelnienie, int start, int koniec);
};

