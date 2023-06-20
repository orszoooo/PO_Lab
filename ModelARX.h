#pragma once
#include "Komponent.h"

#include <vector>
#include <deque>

class ModelARX : public Komponent {
private:
	unsigned int s_dA, s_dB, s_k; //rozmiary buforów k - opóŸnienie transportowe
	double s_odchStd;		//s_ oznacza sk³adow¹ klasy
	std::vector<double> s_wspolWielA, s_wspolWielB;
	std::deque<double> s_sygWe, s_sygWy, s_sygOpK;

	double symZaklocenie(double u);
	double odpModelu(std::vector<double>& wielomian, std::deque<double>& kolejkaSyg); //przekazanie przez referencje w celu unikniêcia kopiowania
	void obslugaWej(double& u);
	void obslugaWyj(double& y_i);
public:
	//Settery wspó³czynników wielomianów A i B
	void setWspolWielA(std::vector<double> noweWspol);
	void setWspolWielB(std::vector<double> noweWspol);
	void setOpoznienieT(unsigned int wartZadana);
	void setOdchStd(double noweOdchStd);

	//Gettery -- zapis do JSON
	std::vector<double> getWspolWielA();
	std::vector<double> getWspolWielB();
	unsigned int getOpoznienieT();
	double getOdchStd();


	double symuluj(double u) override;

	friend class Testy_ModelARX;

	ModelARX(std::vector<double> wielA, std::vector<double> wielB, unsigned int opoznienie = 1, double odchylenie = 0.0);
	~ModelARX();
};


class Testy_ModelARX : public TESTY {
private:
	static void test_ModelARX_brakPobudzenia();
	static void test_ModelARX_skokJednostkowy_1();
	static void test_ModelARX_skokJednostkowy_2();
	static void test_ModelARX_skokJednostkowy_3();
public:
	static void uruchom();
};