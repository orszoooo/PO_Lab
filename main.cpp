#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "json.hpp"
using json = nlohmann::json;

#include "RegulatorPID.h"
#include "ModelARX.h"

#include "SkokJednostkowy.h"
#include "Sinusoida.h"
#include "Trojkat.h"
#include "Szum.h"

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

void ZapisDoPliku(std::ofstream& out_file, std::filesystem::path& path, json& j_out);

bool sprawdzCzyIstniejeFolder(std::filesystem::path& path, std::string& response);

double symFeedback(RegulatorPID& reg, ModelARX& arx, double wart_zadana) {
	double uchyb = wart_zadana - lastARX;
	double wyjReg = reg.symuluj(uchyb);
	lastARX = arx.symuluj(wyjReg);
	return lastARX;
}

int main(int p_argc, const char** p_argv)
{

	//Wiersz poleceń ścieżka do pliku konfiguracyjnego
	//Przy kończeniu pracy programu zapytać użytkownika czy zapisać konfigurację do pliku 
	//Elementy manipulacji systemem plików
	//Połączyć z wzorcem dekorator(bazowy + 2 dekoratory)

	//Odczyt z pliku konfiguracyjnego
	std::cout << std::string(30, '=') << "PLIK KONFIGURACYJNY" << std::string(30, '=') << std::endl;

	std::cout << "Odczyt: " << p_argv[1] << std::endl;
	auto input_path = std::filesystem::path(p_argv[1]);
	std::ifstream f(input_path);

	std::cout << std::string(30, '=') << "TESTY JEDNOSTKOWE" << std::string(32, '=') << std::endl;

	//Parametry domyślne
	//PID
	double p = 0.5;
	double i = 0.1;
	double d = 0.0;

	//Model ARX
	unsigned int k = 0;
	double odchStd = 0.0;
	std::vector<double> arxA = { 0.1 };
	std::vector<double> arxB = { 0.1 };

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

	if (f.is_open()) {
		json data = json::parse(f);

		//PID
		p = data.at("PID").at("P");
		i = data.at("PID").at("I");
		d = data.at("PID").at("D");

		//Model ARX
		arxA.clear();
		for (auto& el : data.at("ARX").at("A").items()) {
			arxA.push_back(el.value());
		}

		arxB.clear();
		for (auto& el : data.at("ARX").at("B").items()) {
			arxB.push_back(el.value());
		}

		k = data.at("ARX").at("k");
		odchStd = data.at("ARX").at("OdchStd");

		//Generator Wzorzec Dekorator
		//Skok Jednostkowy
		amplitudaSkokJed = data.at("Skok Jednostkowy").at("Amplituda");
		czasSkoku = data.at("Skok Jednostkowy").at("Czas skoku");
		startSkokJed = data.at("Skok Jednostkowy").at("Start");
		koniecSkokJed = data.at("Skok Jednostkowy").at("Koniec");

		//Sinusoida
		amplitudaSin = data.at("Sinusoida").at("Amplituda");
		okres = data.at("Sinusoida").at("Okres");
		startSin = data.at("Sinusoida").at("Start");
		koniecSin = data.at("Sinusoida").at("Koniec");

		//Szum
		startSzum = data.at("Szum").at("Start");;
		koniecSzum = data.at("Szum").at("Koniec");;
	}

	//TESTY
	RegulatorPID_TESTY::uruchom();

	RegulatorPID reg1(p, i);
	ModelARX arx1(arxA, arxB, k, odchStd);

	std::cerr << "Test petli: ";

	double syg;
	//Generator sygnału
	for (int i = 0; i < 30; i++) {
		if (i == 0) {
			syg = 0.0;
		}
		else {
			syg = 1.0;
		}

		std::cerr << std::setw(2) << std::setprecision(2) << std::showpoint << symFeedback(reg1, arx1, syg) << " ";
	}
	std::cerr << std::endl;

	//Generator sygnału - wzorzec dekorator
	std::cout << std::string(30, '=') << "GENERATOR SYGNALOW" << std::string(30, '=') << std::endl;

	int t_stop = std::max({ koniecSkokJed, koniecSin, koniecSzum });

	std::cout << "Szum aktywny od " << startSzum << " do " << koniecSzum << std::endl;
	std::cout << "+ Sinusoida Amplituda " << amplitudaSin  << ", okres " << okres << ", aktywny od " << startSin << " do " << koniecSin << std::endl;
	std::cout << "+ Skok Jednostkowy Amplituda " << amplitudaSkokJed << ", Czas Skoku " << czasSkoku << ", Aktywny od " << startSkokJed << " do " << koniecSkokJed << std::endl;

	Sygnal* s1 = new Sinusoida(new SkokJednostkowy(amplitudaSkokJed, czasSkoku, startSkokJed, koniecSkokJed), amplitudaSin, okres, startSin, koniecSin);
	Sygnal* s2 = new Szum(s1, startSzum, koniecSzum);

	for (int t = 0; t < t_stop; t++) {
		std::cout << t << ": " << s2->symuluj(t) << std::endl;
	}
	std::cout << std::string(80, '=') << std::endl;
	//Zapis do pliku konfiguracyjnego
	std::string response = "";
	std::cout << "Czy zapisac parametry regulatora i modelu do pliku? (y/N): ";
	std::cin >> response;
	std::cout << std::endl;

	if (response.find("y") != std::string::npos) {
		std::cout << "Podaj sciezke do folderu docelowego: ";
		std::cin >> response;
		std::cout << std::endl;
		auto path = std::filesystem::path(response);

		if (!path.empty()) {
			
			json j_out;
			j_out["PID"] = { {"P",reg1.get_k()},{"I", reg1.get_Ti()}, {"D",reg1.get_Td()} };
			j_out["ARX"] = { {"A", arx1.getWspolWielA() }, {"B", arx1.getWspolWielB() }, {"k", arx1.getOpoznienieT() }, {"OdchStd", arx1.getOdchStd() } };
			j_out["Skok Jednostkowy"] = { {"Amplituda", amplitudaSkokJed}, {"Czas skoku", czasSkoku}, {"Start", startSkokJed}, {"Koniec", koniecSkokJed} };
			j_out["Sinusoida"] = { {"Amplituda", amplitudaSin}, {"Okres", okres}, {"Start", startSin}, {"Koniec", koniecSin} };
			j_out["Szum"] = { {"Start", startSzum}, {"Koniec", koniecSzum} };

			//Sprawdzenie czy folder istnieje
			bool folder_exists = sprawdzCzyIstniejeFolder(path, response);;
			
			//Zapis do pliku
			std::cout << "Podaj nazwe pliku(musi konczyc sie na .json!): ";
			std::cin >> response;
			std::cout << std::endl;

			std::ofstream out_file;
			path += "\\" + response;
			if (std::filesystem::exists(path)) 
			{
				std::cout << "Uwaga! Chcesz nadpisac istniejacy plik! Czy chcesz kontynuowac? (y/N): ";
				std::cin >> response;
				std::cout << std::endl;

				if (response.find("y") != std::string::npos) 
				{
					ZapisDoPliku(out_file, path, j_out);
				}
				else 
				{
					std::cout << "Anulowano zapis do pliku!" << std::endl;
				}
				out_file.close();
			}
			else 
			{
				ZapisDoPliku(out_file, path, j_out);
			}
			
		}
		
	}
}
bool sprawdzCzyIstniejeFolder(std::filesystem::path& path, std::string& response)
{
	if (!std::filesystem::exists(path))
	{
		std::cout << "Uwaga! Podany katalog! Czy chcesz kontynuowac i utworzyć katalog? (y/N): ";
		std::cin >> response;
		std::cout << std::endl;

		if (response.find("y") != std::string::npos)
		{
			std::filesystem::create_directories(path);
			std::cout << "Utworzono katalog!" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Anulowano zapis do pliku!" << std::endl;
			return false;
		}
	}
	else
	{
		return true;
	}
}
void ZapisDoPliku(std::ofstream& out_file, std::filesystem::path& path, json& j_out)
{
	out_file.open(path);

	if (out_file)
	{
		std::cout << "Zapisano! :)" << std::endl;
		out_file << std::setw(4) << j_out << std::endl;
	}
	else
	{
		std::cout << "Zapis zakonczony niepowodzeniem! :(" << std::endl;
	}
}
#endif

