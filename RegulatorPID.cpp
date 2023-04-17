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


double RegulatorPID::symP(double e_i)
{
	return s_k * e_i;
}

double RegulatorPID::symI(double e_i) {
	s_memI += e_i;

	double u_i;
	if (s_Ti > 0.0) {
		u_i = 1 / s_Ti * s_memI;
	}
	else {
		u_i = 0.0;
	}
	return u_i;
}

double RegulatorPID::symD(double e_i) {
	double u_i;
	if (s_Td > 0.0) {
		u_i = s_Td * (e_i - s_memD);
	}
	else {
		u_i = 0.0;
	}
	
	s_memD = e_i;
	return u_i;
}

double RegulatorPID::symuluj(double e_i){
	return symP(e_i) + symI(e_i) + symD(e_i);
}

void RegulatorPID::set_k(double n_K){
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
