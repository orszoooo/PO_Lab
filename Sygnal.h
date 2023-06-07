#pragma once
class Sygnal
{
private:
	int s_start;
	int s_koniec;
protected:
	bool czyAktywny(int t);
public:
	Sygnal(int start, int koniec);
	virtual ~Sygnal() {} ;
	virtual double symuluj(int t) = 0;
};

