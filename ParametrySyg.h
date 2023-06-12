#pragma once

struct ParametrySyg {
	//Generator Wzorzec Dekorator
	//Skok Jednostkowy
	double amplitudaSkokJed = 9.0;
	int czasSkoku = 35;
	int startSkokJed = 30;
	int koniecSkokJed = 40;

	//Sinusoida
	double amplitudaSin = 10.0;
	int okres = 20;
	int startSin = 0;
	int koniecSin = 40;

	//Szum
	int startSzum = 0;
	int koniecSzum = 50;
};