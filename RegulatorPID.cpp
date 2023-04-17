#include "RegulatorPID.h"

double RegulatorPID::setUnsigned(double wart)
{
	if (wart < 0.0) {
		return 0.0;
	}
	else {
		return wart;
	}
}

double RegulatorPID::symuluj(double e_i)
{
	return s_k * e_i;
}

void RegulatorPID::set_k(double n_K)
{
	s_k = setUnsigned(n_K);
}

void RegulatorPID::set_Ti(double n_Ti) {
	s_Ti = setUnsigned(n_Ti);
}

void RegulatorPID::set_Td(double n_Td) {
	s_Td = setUnsigned(n_Td);
}

RegulatorPID::RegulatorPID(double P)
{
	set_k(P);
}

RegulatorPID::RegulatorPID(double P, double I)
{
	set_k(P);
	set_Ti(I);
}

RegulatorPID::RegulatorPID(double P, double I, double D)
{
	set_k(P);
	set_Ti(I);
	set_Td(D);
}
