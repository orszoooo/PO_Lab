#pragma once
#include <vector>

class ObiektSISO {
public:
	virtual double symuluj(double u) = 0;
	virtual ~ObiektSISO() {};//wirtualny destruktor umożliwiający polimorfizm
};

class TESTY {
public:
	static void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt);
	static bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt);
};