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

	//Settery -- s¹ wolniejsze od listy inicjalizacyjnej ale czyni¹ kod spójniejszym
	void set_k(double n_K);
	void set_Ti(double n_Ti);
	void set_Td(double n_Td);

	//Konstruktory
	RegulatorPID(double P);
	RegulatorPID(double P, double I);
	RegulatorPID(double P, double I, double D);
};

class RegulatorPID_TESTY : public TESTY {
private:
	static void test_RegulatorP_brakPobudzenia();
	static void test_RegulatorP_skokJednostkowy();
	static void test_RegulatorPI_skokJednostkowy_1();
	static void test_RegulatorPI_skokJednostkowy_2();
	static void test_RegulatorPID_skokJednostkowy();

public: 
	static void uruchom();
};