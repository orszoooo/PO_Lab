#pragma once
#include "ObiektSISO.h"
class RegulatorPID : public ObiektSISO{
private:
	double s_k, s_Ti, s_Td;
	double s_memI = 0.0, s_memD = 0.0;
	double setUnsigned(double wart); //sprawdza czy zmienna przechowuje wartoœæ nieujemn¹, jeœli nie to zwraca 0.0.
	double symP(double e_i);
	double symI(double e_i);
	double symD(double e_i);

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