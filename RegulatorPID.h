#pragma once
#include "ObiektSISO.h"
class RegulatorPID : ObiektSISO{
private:
	double s_k, s_Ti, s_Td;
	double s_lastTi = 0.0, s_lastTd = 0.0;
	double setUnsigned(double wart); //sprawdza czy zmienna przechowuje wartoœæ nieujemn¹, jeœli nie to zwraca 0.0.
public:
	double symuluj(double e_i) override;

	//Settery
	void set_k(double n_K);
	void set_Ti(double n_Ti);
	void set_Td(double n_Td);

	//Konstruktory
	RegulatorPID(double P);
	RegulatorPID(double P, double I);
	RegulatorPID(double P, double I, double D);
};