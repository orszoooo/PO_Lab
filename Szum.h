#pragma once

#include <random>

#include "SygnalDekorator.h"

class Szum : public SygnalDekorator
{
private:
	static std::mt19937 generator; 
	std::normal_distribution<double> s_generatorSzumu;
	int s_wariancjaSzumu = 0;
public:
	void setWariancjaSzumu(int wariancjaSzumu);

	int getWariancjaSzumu();
	
	double symuluj(int t);
	Szum(Sygnal* s, int start, int koniec);
};

