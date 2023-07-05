#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "json.hpp"
using json = nlohmann::json;

#include "RegulatorPID.h"
#include "ModelARX.h"
#include "Utils.h"
#include "SkokJednostkowy.h"
#include "Sinusoida.h"
#include "Trojkat.h"
#include "Szum.h"
#include "ParametrySyg.h"
#include "KompozytUAR.h"

#define MAIN

#ifdef DEBUG

//Funkcje pomocnicze dla testów:

void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr size_t PREC = 3;
	std::cerr << std::fixed << std::setprecision(PREC);
	std::cerr << "  Spodziewany:\t";
	for (auto& el : spodz)
		std::cerr << el << ", ";
	std::cerr << "\n  Faktyczny:\t";
	for (auto& el : fakt)
		std::cerr << el << ", ";
	std::cerr << std::endl << std::endl;
}

bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr double TOL = 1e-3;	// tolerancja dla porównań zmiennoprzecinkowych
	bool result = fakt.size() == spodz.size();
	for (int i = 0; result && i < fakt.size(); i++)
		result = fabs(fakt[i] - spodz[i]) < TOL;
	return result;
}

void test_RegulatorP_brakPobudzenia()
{
	//Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test zerowego pobudzenia: ";
	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja modelu:

		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorP_skokJednostkowy()
{
	//Sygnatura testu:
	std::cerr << "RegP (k = 0.5) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_1()
{
	//Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 1.0) -> test skoku jednostkowego nr 1: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5,1.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPI_skokJednostkowy_2()
{
	//Sygnatura testu:
	std::cerr << "RegPI (k = 0.5, TI = 10.0) -> test skoku jednostkowego nr 2: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

void test_RegulatorPID_skokJednostkowy()
{
	//Sygnatura testu:
	std::cerr << "RegPID (k = 0.5, TI = 10.0, TD = 0.2) -> test skoku jednostkowego: ";

	try
	{
		// Przygotowanie danych:
		RegulatorPID instancjaTestowa(0.5, 10.0, 0.2);
		constexpr size_t LICZ_ITER = 30;
		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
		for (int i = 0; i < LICZ_ITER; i++)
			sygWe[i] = !!i;
		spodzSygWy = { 0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

		// Symulacja modelu:
		for (int i = 0; i < LICZ_ITER; i++)
			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

		// Walidacja poprawności i raport:
		if (porownanieSekwencji(spodzSygWy, faktSygWy))
			std::cerr << "OK!\n";
		else
		{
			std::cerr << "FAIL!\n";
			raportBleduSekwencji(spodzSygWy, faktSygWy);
		}
	}
	catch (...)
	{
		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
	}
}

using namespace std;

int main()
{
	test_RegulatorP_brakPobudzenia();
	test_RegulatorP_skokJednostkowy();
	test_RegulatorPI_skokJednostkowy_1();
	test_RegulatorPI_skokJednostkowy_2();
	test_RegulatorPID_skokJednostkowy();

}

#endif

#ifdef MAIN
static double lastARX = 0.0;
std::mt19937 Szum::generator; //Szum.h
int Komponent::liczba_objektow = 0;

double symFeedback(RegulatorPID& reg, ModelARX& arx, double wart_zadana) {
	double uchyb = wart_zadana - lastARX;
	double wyjReg = reg.symuluj(uchyb);
	lastARX = arx.symuluj(wyjReg);
	return lastARX;
}

int main(int p_argc, const char** p_argv)
{
	//LAB4
	//Wiersz poleceń ścieżka do pliku konfiguracyjnego
	//Przy kończeniu pracy programu zapytać użytkownika czy zapisać konfigurację do pliku 
	//Elementy manipulacji systemem plików
	//Połączyć z wzorcem dekorator(bazowy + 2 dekoratory)

	//LAB5
	//Wzorzec komponent (funkcje dodaj, usuń, symuluj)
	
	//Parametry domyślne
	//PID
	RegulatorPID reg1(1.0, 0.0,0.0);

	//Model ARX
	//ModelARX arx1({ -0.4 }, { 0.6 }, 1, 0.0);
	ModelARX arx1({ 0.1 }, { 0.1 }, 1, 0.0);

	KompozytUAR petlaRegulacji(1); //zamknięta pętla regulacji

	//Generator Wzorzec Dekorator
	ParametrySyg params_generator;

	//Konfiguracja z pliku
	json data;

	if (p_argv[1]) 
	{
		//Odczyt z pliku konfiguracyjnego
		std::cout << std::string(29, '=') << "PLIK KONFIGURACYJNY" << std::string(30, '=') << std::endl;

		std::cout << "Odczyt: " << p_argv[1] << std::endl;
		auto input_path = std::filesystem::path(p_argv[1]);

		if (std::filesystem::exists(input_path)) {
			std::ifstream input_file(input_path);

			if (input_file.is_open()) {
				odczytJSON(data,input_file,petlaRegulacji, params_generator);
			}
			else {
				std::cout << "Nie mozna otworzyc pliku konfiguracyjnego! Program uzywa wartosci domyslnych!" << std::endl;
			}
			
		}
		else {
			std::cout << "Plik konfiguracyjny nie istnieje! Program uzywa wartosci domyslnych!" << std::endl;
		}
		
	}
	else 
	{
		std::cout << "Brak pliku konfiguracyjnego! Program uzywa wartosci domyslnych!" << std::endl;
	}

	//Złożony sygnał
	std::cout << std::string(30, '=') << "GENERATOR SYGNALOW" << std::string(30, '=') << std::endl;
	Sygnal* s1 = new Sinusoida(new SkokJednostkowy(params_generator.amplitudaSkokJed, params_generator.czasSkoku, params_generator.startSkokJed, params_generator.koniecSkokJed), 
		params_generator.amplitudaSin, params_generator.okres, params_generator.startSin, params_generator.koniecSin);
	Sygnal* s2 = new Szum(s1, params_generator.startSzum, params_generator.koniecSzum);
	int t_stop = std::max({ params_generator.koniecSkokJed, params_generator.koniecSin, params_generator.koniecSzum });

	std::cout << "Szum aktywny od " << params_generator.startSzum << " do " << params_generator.koniecSzum << std::endl;
	std::cout << "+ Sinusoida Amplituda " << params_generator.amplitudaSin  << ", okres " << params_generator.okres << ", aktywny od " << params_generator.startSin 
		<< " do " << params_generator.koniecSin << std::endl;
	std::cout << "+ Skok Jednostkowy Amplituda " << params_generator.amplitudaSkokJed << ", Czas Skoku " << params_generator.czasSkoku << ", Aktywny od "
		<< params_generator.startSkokJed << " do " << params_generator.koniecSkokJed << std::endl;
	

	double sig = 0.0;
    //Pętla regulacji
	std::cout << std::string(34, '=') << "SYMULACJA" << std::string(35, '=') << std::endl;
	std::cout << "Czas:  Sygnal wej | Petla UAR | Funkcja symFeedback" << std::endl;
	for (int t = 0; t < t_stop; t++) {
		sig = s2->symuluj(t);
		std::cout << t << ": " << sig << "|" << petlaRegulacji.symuluj(sig) << "|" << symFeedback(reg1, arx1, sig) << std::endl;
	}
	std::cout << std::string(80, '=') << std::endl;
	
	//Zapis do pliku konfiguracyjnego
	ZapisJSON(data);

	petlaRegulacji.usun();
}
#endif

